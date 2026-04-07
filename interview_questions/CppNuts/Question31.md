# `push_back()` and `emplace_back()`

메모리 구조 관점에서 `push_back()`과 `emplace_back()`을 이해하는 것은 굉장히 중요할 수도 있다. 결론부터 말하면, 둘 다 최종 목적지는 heap 이고, 중간 과정에서 Stack을 거치느냐 안거치느냐의 차이이다.

1) `std::vector` 의 메모리 구조
먼저 명확히 해야하는 점은, `std::vector` 객체 자체는 Stack에 생성될 수 있지만, 그 안에 담기는 실제 데이터(원소들)은 무조건 Heap 에 할당된 연속된 메모리 공간에 저장된다. (`int`, `float`, `double` 같은 primitive types 도 `std::vector` 에 들어가면 무조건 Heap 에 연속된 메모리 공간으로 저장된다.) 

2) `push_back(obj)` 의 메모리 여정.
- `push_back` 은 이미 만들어진 객체를 인자로 받는다.
    
    1) Stack 생성: 함수 호출 전, `Object obj(args...)`를 실행하면 Stack에 임시 객체가 생성됨.
    2) Heap 이동/복사: `push_back`
        - Stack 소멸: 함수 호출 전, `Object obj(args...)`를 실행하면 Stack에 임시 객체가 생성됨.
        - Heap 이동/복사: `push_back(obj)`를 호출하면, Stack에 있는 데이터를 **Heap**에 할당된 벡터의 메모리 공간으로 복사(Copy)하거나 이동(Move)시킨다.
        - Stack 소멸: 함수 범위를 ㅓㅅ어나면 Stack 에 있던 임시 객체는 소멸자(`~Object`)를 호출하며 사라진다.
        - 단점: Heap에 넣기 위해 Stack에서 객체를 한 번 만들었더가 버리는 이중 작업이 발생한다.
3) `emplace_back(Args..)`의 메모리 여정
    `emplace_back`은 객체가 아니라 **생성자에 필요한 재료(인자)** 만 받는다.
    
    1) **Direct heap Construction:** Stack에 임시 객체를 만들지 않음. 대신에 벡터가 미리 Heap에 확보해둔 빈 공간의 주소를 찾아가서, 거기서 바로 생서자를 호출해 객체를 조립함. (Placement New 기법)
    2) 여정 종료: 처음부터 Heap에서 태어났으므로 복사도, 이동도, Stack에서의 소멸 과정도 필요 없음.

4) 추가 팁: `reserve()`의 주요성
    
    아무리 `emplace_back`을 써도, 벡터의 용량(Capacity)이 가득 차면, 전체 데이터를 새로운 Heap 공간으로 이사(Reallocation) 시켜야 한다. HFT 같은 저지연 환경에서는 이 이사 비용을 막기 위해서 `vector.reserve(expected_size)`를 먼저 호출해 Heap 공간을 미리 넉넉히 따놓은 것이 좋다.


    