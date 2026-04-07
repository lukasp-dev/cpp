# Function Pointers

### What is Function Pointer and how to use them.

```cpp
int (*f_ptr)(int&, int&) = &func; // 정석
int (*f_ptr)(int&, int&) = func;  // & 생략 가능

std::cout << (*f_ptr)(a, b); // 정석 역참조 호출
std::cout << f_ptr(a, b);    // * 생략하고 일반 함수처럼 호출 가능
```

참조자(`int&`) 주의점

만약에 코드에서 `int& a`를 매개변수로 쓰는데, 함수 포인터 타입 정의에서도 `int&` 를 동일하게 맞춰줘야함. 

만약 `const`를 붙인다면?
`int func(const int& a, const int& b)` 라면 포인터도 `int (*f_ptr)(const int&, const int&)`가 되어야 함.

#### 함수 포인터 use case
단순히 `func(a, b)`라고 안부르고 function ptr 를 쓰는 이유는 상황에 따라 strategy 를 갈아끼우기 위해서.

```cpp
void calculate(int a, int b, int (*operation)(int&, int&)) {
    std::cout << "result: " << operation(a, b) << "\n";
}

calculate(10, 20, add_func);
calculate( 10, 20, multiply_func);
```

#### How to return a function pointer?
`using` 를 통해 함수 포인터에 alias를 부여해서 쓰는게 가장 좋다.
```cpp
#include <iostream>

using CalcPtr =int(*)(int, int);

int add(int a, int b) {return a + b;}
int sub(int a, int b) {return a - b;}

CalcPtr get_operation(char op){
    // 함수 이름은 그 자체로 주소값으로 암시적 변환 (Decay) 되서 그냥 `return add` 해도 된다.
    if(op == '+') return &add;
    if(op == '-') return &sub;
    return nullptr;
}

int main() {
    // 함수 포인터를 받아옴
    CalcPtr myFunc = get_operation('+');

    if (myFunc != nullptr) {
        // 받아온 포인터로 함수 실행
        std::cout << "Result: " << myFunc(10, 5) << std::endl; // 출력: 15
    }
    
    return 0;
}
```
