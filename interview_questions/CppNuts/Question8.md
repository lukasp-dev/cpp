# reinterpret_cast

1) It can perform dangerous conversions because it can typecast any pointer to any other pointer.

    ```cpp
    #include <iostream> 
    using namespace std;

    class Mango {
    public:
        void eatMango() {cout << "eating Mango" << "\n";}
    };

    class Banana {
    public:
        void eatBanana() { cout << "eating Banana" << "\n";}
    };

    int main(){
        Banana* b = new Banana();
        Mango* m = new Mango();
        
        Mango* bm = reinterpret_cast<Mango*>(b);
        bm->eatMango();
        
        return 0;
    }`
    ```
2) It is used when you want to work with bits
    ```cpp
    #include <iostream>
    using namespace std;

    struct myStruct {
        int x;
        int y;
        char c;
        bool b;
    };

    int main() {
        myStruct s;
        s.x = 5; s.y = 10; s.c = 'a'; s.b = true;
        int* p = reinterpret_cast<int*>(&s);
        cout << *p << "\n"; //5
        cout << *(++p) << "\n"; //10
        p++;
        char* c = reinterpret_cast<char*>(p); //a
        cout << *c << "\n";
        c++;
        cout << *(reinterpret_cast<bool*>(c)) << "\n"; //1
        
        return 0;
    }   
    ```

### Summary
- The result of a `reinterpret_cast` cannot safely be used for anything other than being cast back to its original type.
- we should be very careful when using this cast.
- If we use this type of casting, it becomes non-portable product.

### 추가 설명
쉬게 비유하자면, 어떤 상자 안에 무엇이 들어있든 상관없이 **내 눈에는 이제부터 이게 사과가 아니라 오렌지로 보여야 한다** 라고 안경을 바꿔 쓰는 것. 데이터의 비트 패턴은 전혀 건드리지 않고, 오직 **컴파일러가 그 데이터를 바라보는 관점**만 바꾼다.