# The difference between pointer and reference

reference cannot be initialized with nullptr, pointer can
arithmetic operation difference
re-assignment

```cpp
// Online C++ compiler to run C++ program online
#include <iostream>

int main() {
    int a = 100;
    int &b = a;
    int *c = &a;

    std::cout << "ADDRESSES:\n";
    std::cout << "a: " << &a << "\n"; // a: 0x7ffeb90a2c54
    std::cout << "b: " << &b << "\n"; // b: 0x7ffeb90a2c54
    std::cout << "c: " << &c << "\n"; // c: 0x7ffeb90a2c48

    int var = 200;
    b = var;
    std::cout << a << "\n"; // a의 값도 바뀌어버림=

    return 0;
}

```
