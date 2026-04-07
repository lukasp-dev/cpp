# What is the operator?

우리가 흔히 쓰는 +,-,*,/ 같은 것들이 연산자.
하지만 C++ 컴파일러 입장에서 `a+b`는 사실 다음과 같은 함수 호출이다.
-  `operator+(a, b)`를 실행해라.
즉, 연산자는 어떤 기호를 만났을 때 실행되도록 약속된 함수이다.

### operator overloading 을 하는 이유
기본적인 숫자들은 컴파일러가 더하는 방법을 이미 알지만 우리가 작접 만든 struct 나 class는 어떻게 더해야하는지 모른다.

```cpp
struct Vector {
    int x, y;

    Vector operator+(const Vector& other) {
        return { x + other.x, y + other.y}
    }
};

int main() {
    Vector v1 = {1, 2};
    Vector v2 = {3, 4};

    Vector v3 = v1 + v2;
}
```

### important operator to overload

| 연산자 이름 | 실제 동작 | HFT/고성능 프로그래밍에서의 의미 |
| :--- | :--- | :--- |
| **operator()** | 함수 호출 연산자 | 객체를 함수처럼 실행 (`obj()`). **인라인화(Inlining)** 최적화의 핵심이며, 람다나 펑터(Functor) 구현 시 필수적임. |
| **operator[]** | 배열 접근 연산자 | `obj[i]` 형태로 접근. 메모리 주소 계산을 직접 제어하며, **메모리 풀(Memory Pool)** 에서 특정 데이터를 초고속으로 인덱싱할 때 사용. |
| **operator&** | 주소 연산자 | `&obj`로 주소값 반환. 보안 및 안정성을 위해 객체의 메모리 주소 노출을 차단(delete 처리 등)하거나 프록시 객체를 반환할 때 사용. |


1) `operator()` (함수 호출 연산자)
    ***REMINDER:*** A functor is a class/struct that defines `operator()`

    실무 예시: 초고속 정렬 펑터 (Fast Sorting Functor)

    HFT에서 '호가창(Order Book)'은 가격이 변할 때마다 매초 수만 번씩 정렬되어야 한다. 이때 일반 함수 포인터를 쓰면 느려서 펑터를 쓴다. 

    펑터가 더 빠른 이유: 함수 포인터는 실행 시점에 어떤 함수를 가르키고 있는지 주소값을 모르는 반면에, Functor 는 `operator()` 가 정의된 클래스의 인스턴스로써, 컴파일 타임에 호출될 함수가 명확히 결정되므로, 컴파일러가 함수 호출 코드를 해당 함수의 본체 코드로 직접 갈아끼우는 inlining 수행을 할 수가 있다.

    ```cpp
    struct PriceComparator {
        // operator()를 정의해서 객체를 함수처럼 만듦
        bool operator()(const Order& a, const Order& b) const {
            return a.price > b.price; // 내림차순 정렬 (비싼 가격이 우선)
        }
    };
    ```
    ```cpp
    // 사용 예시
    std::priority_queue<Order, std::vector<Order>, PriceComparator> orderBook;
    ```
    왜 좋은가? 컴파일러가 orderBook 내부에 이 비교 로직을 **인라인(Inlining)**으로 박아버립니다. 함수 호출을 위해 메모리 주소를 왔다 갔다 하는 시간조차 아끼는 거죠.

2) `operator[]` (배열 접근 연산자)
    실무 예시: 커스텀 메모리 풀 (Custom Memory Pool)

    HFT에서는 new나 malloc을 쓰면 너무 느려서, 미리 큰 메모리 덩어리를 잡아놓고 인덱스로 관리합니다. 이때 배열처럼 접근하게 해줍니다.

    ```cpp
    class MemoryPool {
    private:
        char* buffer; // 미리 할당된 큰 메모리
    public:
        // operator[]를 오버로딩하여 메모리 조각에 즉시 접근
        char& operator[](int offset) {
            return buffer[offset]; 
        }
    };

    MemoryPool pool;
    pool[1024] = 'A'; // 복잡한 함수 호출 없이 1024번째 바이트에 직접 접근
    ```
    왜 좋은가? 함수 호출 오버헤드 없이 "메모리 주소 + 오프셋" 연산만으로 데이터에 접근하므로, 캐시 효율이 극대화되고 속도가 가장 빠릅니다.

3) `operator&` (주소 연산자)
    실무 예시: 임시 객체 주소 획득 방지 (Safety Guard)

    네트워크에서 잠깐 데이터를 담았다가 사라지는 '임시 패킷 객체'가 있다고 해봅시다. 이 객체의 주소를 따서 저장해두면 나중에 프로그램이 터집니다(Dangling Pointer). 이를 원천 봉쇄합니다.

    ```cpp
   class TempPacket {
    public:
        // 주소를 가져가는 연산 자체를 금지시켜버림
        TempPacket* operator&() = delete; 
    };

    TempPacket pkt;
    // TempPacket* ptr = &pkt; // 에러 발생! 컴파일 단계에서 실수를 막아줌.
    ```
    왜 좋은가? 수백 명의 개발자가 협업하는 큰 프로젝트에서, 누구도 이 객체의 주소를 안전하지 않게 저장할 수 없도록 강제하는 강력한 안전장치입니다.


