# const_cast

The expression `const_cast<T>(v)` can be used to change the `const` or `volatile` qualifiers of pointers or references.

`T` must be a pointer, reference, or pointer-to-member type.

1) MUST KNOW:
***"This is valid only if the actual object being referred to is non-const."***

    ```cpp
    #include <iostream>
    using namespace std;

    int main(){
        const int a1 = 10;
        const int* b1 = &a1;
        int *d1 = const_cast<int*>(b1);
        *d1 = 15;
        /* invalida and undefined behavior */
        cout << a1 << "\n"; //10 <- didn't change to 15
        /*
        THe compiler try to optimize the compilation, so instead of doing
        cout << a1 << "\n"; dynamically, it will do something like
        cout << 10 << "\n"; determined in the compile time already
        */
        cout << *d1 << "\n"; //15 
        
        int a2 = 20;
        const int* b2 = &a2;
        int *d2 = const_cast<int*>(b2);
        *d2 = 30;
        /* valid code */
        cout << a2 << "\n"; //30
        cout << *d2 << "\n"; //30
        
        return 0;
    }
    ```


2) We use `const_cast` when we need to call some 3rd party library where it is taking variable/object as non-const but does not change that.

    Imagine dyou have a `const std::string` and you want to pass it to a legacy function that was written 20 years ago:

    ```cpp
    //3rd party library function (You cannot change this code)
    // It doesn't actually modify 'str', but the author forgot to add 'const'
    void legacyPrint(char* str) {
        printf("%s\n", str);
    }

    void myCode(const std::string& msg) {
        // legacyPrint(msg.c_str()); // Error: cannot convert const char* to char*

        // Safety: You know legacyPrint won't touch the data
        char* nonConstStr = const_cast<char*>(msg.c_str());
        legacyPrint(nonConstStr);
    }
    ```

### 추가 설명
함수 파라미터에 `const`를 쓰는 4가지 이유

1) Error Prevention: 함수 안에서 실수로 값을 수정하려 하면 컴파일러가 즉시 에러를 낸다.
2) API Contract: 함수가 데이터를 읽기만 할것인지(Read-only), 수정할 것인지(Read-write) 호출자에게 명확히 알려준다.
3) Compatibility: `const` 포인터로 선언하면 일반 변수와 상수 변수를 모두 인자로 받을 수 있어서 활용도가 높다. -> 그냥 포인터로 선언하면 상수 변수는 받을 수 없음.
4) Optimization: 컴파일러가 이 값은 안 변하겠구나 라고 판단해서 코드를 더 효율적으로 실행되게 만든다.