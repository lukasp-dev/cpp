# Const-Correctness
### 1) Hidden Argument
우리가 클래스 맴버 함수를 호출할 때, 겉으로는 인자가 없어 보여도 컴파일러는 몰래 **객체의 주소(this)** 를 첫 번째 인자로 전달한다.

C++ 클래스 안에는 함수가 100개 있어도, 메모리에는 그 함수들의 복사본이 딱 하나씩만 존재함. (안 그러면 객체를 1,000개 만들 때마다 함수 메모리도 1,000배로 늘어나서 망함)
- 함수는 하나인데, 어떤 객체의 데이터를 수정해야 할지 어떻게 알지? -> 컴파일러가 모든 멤버 함수의 첫 번째 인자로 호출한 객체의 주소를 몰래 찔러 넣어줌.

```cpp
class Trading {
public:
    void placeOrder(int qty) {
        this->quantity = qty;
    }
private:
    int quantity;
};

// 메인 함수에서
Trading myTrade;
myTrade.placeOrder(100);
// 컴파일러는 내부적으로 Trading::placeOrder(&myTrade, 100); 으로 바꿔서 실행함
```
그러니까 `this`는 마법이 아니라, 그저 함수의 0순위 매개변수임.

### 2) `TYPE* const this` (일반 멤버 함수)
여기서 `const` 위치가 `*` 뒤에 붙으므로 포인터 변수 자체가 담고 있는 주소값을 못 바꾼다는 뜻이다.
- 예시: `int* const ptr`과 똑같은. (주소 고장, 값 변경 가능)
    ```cpp
    void updatePrice(int p){
        // 1. 주소 변경 불가능
        // this = &otherObject; // 에러!

        // 2. 값 변경 가능
        this->price = p;
    }
    ```

### `const TYPE* const this` (const 멤버 함수)
함수 뒤에 `const`를 붙이면, 컴파일러는 `this` 포인터가 가리키는 대상(객체)까지 `const`로 취급해버린다.
- 예시: `const int* const ptr`과 똑같음. (주소 고정, 값 변경 불가)
    ```cpp
    void showPrice() const { // 함수 뒤에  const가 붙음!
        // 1. 값 변경 시도 (불가능!)
        // this->price = 500; // 에러! const 함수 안에서는 멤버 변수 수정 불가.
        
        // 2. 값 읽기만 가능
        std::cout << this->price; // ✅ 성공! 읽기 전용 모드임.
    }
    ```