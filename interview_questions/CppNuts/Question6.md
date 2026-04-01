# static_cast in C++

1) It performs implicit conversions between types.
    ```cpp
    #include <iostream>
    using namespace std;

    int main(){
        float f = 3.5;
        int a;

        a = f;
        a = static_cast<int>(f);

        return 0;
    }
    ```

2) Use static_cast when conversion between types is provided through conversion operator or converstion constructor.

    ```cpp
    class Int {
        int x;
    public:
        Int(int x = 0): x{x} {
            cout << "conversion constructor\n";
        }
        explicit operator string() const {
            cout << "conersion operator\n";
            return to_string(x);
        }
    };

    int main() {
        Int obj(3);

        string str1 = obj;
        obj = 20;

        string str2 = static_cast<string>(obj);
        obj = static_cast<Int>(30);
    }
    ```


    ### how compiler execute the conversion
    ```cpp
    #include <iostream>

    class Price{
    double x;
    public:
        explicit Price(double x) : x{x}{}
        double getPrice(){
            return x;
        }
    };

    int main(){
        // error: conversion from 'int' to non-scalar type 'Price' requested
        // Price price = 10;
        
        Price price = Price(10);
        std::cout << price.getPrice() << "\n"; //10
        
        return 0;
    }
    ```
    `Price price = 10;`
    1) 타입 불일치 발견
    2) 해결책 검색: Price class 안에 int 하나만 받는 생성자가 받는 생성자가 있는지 찾음 (or something an int can turn into, like double)
    3) Price(10) 을 호출해서 임시로 객체를 만듦.
    4) 그 임시 객체를 price에 집어넣음.

    **3번 과정이 좀 overhead 임**
    - 성능 저하: 그냥 숫자를 썼을 뿐인데, 내 의도 상관없이 CPU가 객체를 새로 만들고 부수는 연산을 수행
    - 실수 유발: `int`를 받는 생성자가 있으면, 내가 실수로 숫자를 넣어도 컴파일러가 에러를 안 내고 넘어가 버림.
    -> **파라미터가 있는 생성자**에는 `explicit`을 붙여서 자동 변환 통로를 막아버림

    ### Conversion operator
    You might want to go the **other way** (Price back to double) using the operator.
    ```cpp
    explicit operator double() const {
        return x;
    }
    ```
    if you add this, then `double d = static_cast<double>(price);` works. Without it, you have to use your `getPrice()` function. In HPC, `static_cast` is often preferred because it is a standard C++ wat to handle types, making the code more generic.

3) `static_cast` is more restrictive than C-style.
Example:   `char*` to `int*` is allowed in C-style butnot with `static_cast`.

    ```cpp
    int main() {
        char c;             // 1 byte data
        int *p = (int*)&c;  // 4 byte data
        *p = 5;             // PASS at compile-time but FAIL at runtime.

        int* ip = static_cast<int*>(&c); // FAIL // compile-time error, because no compatible pointer types.
        return 0;
    }
    ```

4. `static_cast` avoid cast from derived to private base pointer.
    ```cpp
    class Base {};
    class Derive : private Base {};
    int main() {
        Derived d1;
        Base *bp1 = (Base*)&d1; // allowed at compile time
        Base *bp2 = static_cast<Base*>(&d1); // not allowed at compile time
    }

    // but casting public Base is possible
    #include <iostream>

    class Base{
    public:
        int x = 1;
    };
    class Derived : public Base{
    public:
        void func(){}
    };

    int main(){
        Derived d;
        Base* bp = static_cast<Base*>(&d);
        std::cout << bp->x << "\n"; //1
        return 0;
    }
    ```

5) Use `static_cast` for all upcasts, but never use for confused down cast.
Only use it when you know for sure of a type of derived class.

    ```cpp
    class Base {};
    class Derived1: public Base {};
    class Derived2: public Base {};

    int main() {
        Derived1 d1;
        Derived2 d2;

        Base *bp1 = static_cast<Base*>(&d1);
        Base *bp2 = static_cast<Base*>(&d2);

        /*
        둘이 크로스 되서 undefined behavior 나옴.
        */
        Derived1 *d1p = static_cast<Derived1*>(bp2);
        // 위험: 실제 객체는 Derived2이므로 d1p를 통해 접근 시 메모리 오염 발생.
        // 하지만 성능 최적화를 위해 타입을 확신할 수 있는 경우 dynamic_cast 대신 사용함.
        Derived1 *d2p = static_cast<Derived2*>(bp1);

        return 0;
    }
    ```
