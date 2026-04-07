# Diamond problem in Cpp

```cpp
#include <iostream>
using namespace std;

class A {
public:
    int _a;
};

class B : public A {
public:
    int _b;
};

class C : public A {
public:
    int _c;
};

class D: public B, public C{
public:
    int _d;
};

int main() {
    D b;
    // b._a; // cannot compile this because _a is a duplicate
    b._b;
    b._c;

    return 0;
}

//    A
//   / \
//  B   C
//   \ /
//    D

// A object memory layout
// _a

// B object memory layout
// _a
// _b

// C object memory layout
// _a
// _c

// D object memory layout
// _a
// _b
// _a
// _c
// _d
```

### a way to solve this problem
```cpp
#include <iostream>
using namespace std;

class A {
public:
    int _a;
};

class B : virtual public A {
public:
    int _b;
};

class C : virtual public A {
public:
    int _c;
};

class D: public B, public C{
public:
    int _d;
};

int main() {
    D b;
    b._a;
    b._b;
    b._c;

    return 0;
}
```

- 일반적인 방법으로 상속하면 D 객체 안에 A가 두 개 생겨서, 컴파일러가 어디쪽에서 온 _a인지 헷갈려함
- 가상 상속 시 (`virtual`)
    - B 와 C가 우리는 A를 공유하겠다 라고 선언하는 거임. 이렇게 하면 D 객체 안에 A 는 딱 하나만 존재하게 되고, 컴파일러 입장에서 `_a`를 찾아갈 길이 하나뿐이니 에러가 안남.