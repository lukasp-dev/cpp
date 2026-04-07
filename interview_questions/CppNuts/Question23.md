# How to call a function before `main()`

### use global variable
```cpp
#include <iostream>

void func(){
    std::cout << "a function is called!\n";
}

class Base {
public:
    Base(){
        func();
    }
};

Base b; // global variable

int main(){
    std::cout << "inside main!" << "\n";
    return 0;
}

/*
a function is called!
inside main!
*/
```

### Use static variable
```cpp
#include <iostream>

int func(){
    std::cout << "a function is called!\n";
    return 10;
}

class Base {
public:
    static int var;
};

int Base::var = func(); // use static variable.

int main(){
    std::cout << "inside main!" << "\n";
    std::cout << Base::var << "\n";
    return 0;
}

/*
a function is called!
inside main!
*/
```

이를 통해 알 수 있는 점:
- 전약/정적 변수는 `main()` 함수가 실행되기 직전에 메모리에 올라가고 초기화 된다.