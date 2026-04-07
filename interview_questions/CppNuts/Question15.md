# How to call same base class function from derived class object

```cpp
#include <iostream>

class Base{
public:
    void fun() { std::cout << "Base" << "\n"; }
};

class Derived : public Base {
public:
    void fun() { std::cout << "Derived" << "\n";}
};

int main() {
    Derived d;
    d.fun(); // Derived
    d.Base::fun(); // Base
    Base b = static_cast<Base>(d); // Object Slicing 위험
    b.fun(); // Base
    Base* b_ptr = static_cast<Base*>(&d);
    b_ptr->fun(); // Base
    return 0;
}
```

### 추가 설명

**object slicing definition:**

object slicing은 Derived 객체를 Base 타입의 갑으로 복사하거나 대입할 떄 발생. 이때 Base class의 메모리 
범위를 벗어나는 Derived Class의 고유한 멤버들과 vptr 정보가 잘려나가고 Base Class 부분만 남게 되는 현상

왜 발생하는가:
- 메모리 크기 차이: `sizeof(Derived)` > `sizeof(Base)`
- 값 복사의 한계: `Base b = d;` 처럼 값으로 대입하면, 컴파일러는 `Base` 크기만큼의 메모리 공간에 `Derived` 객체 중 `Base` 에 해당하는 부분만 복사 

해결 방법:

객체를 **값(Pass-by-value)** 이 아닌 **참조(Pass-by-reference)** 나 **포인터(Pass-by-pointer)** 로 전달하면 됨. 참조나 포인터는 실제 객체의 크기와 상관없이 **주소값(8바이트)** 만 저장하므로, 객체의 메모리 구조를 건드리지 않고 전체 인스턴스에 접근할 수 있게 해줌.