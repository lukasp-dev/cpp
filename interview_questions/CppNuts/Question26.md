# How to Overload pre and post increment operator in C++?

```cpp
#include <iostream>

class Int{
    int elem;
public:
    Int(){}
    Int(int val): elem{val}{}
    void printValue() {std::cout << elem << std::endl; }
    
    /*
    Int& 으로 반환을 해야 호출한 쪽에서 새로운 메모리 공간을 잡지 않고 원본 i 가 있는 주소를 그대로 보게 됨.
    
    만약 Int 로 반환하면, elem 이 커진 상태의 복사본을 하나 더 찍어내서 던지는 꼴임.
    */
    Int & operator++(){ //pre-increment
        elem++;
        return *this;
    }
    
    Int operator++(int dummy){
        Int tmp = *this;
        ++(*this);
        return tmp;
    }
};

int main(){
    Int i(100);
    i.printValue();     //100
    (i++).printValue(); //100
    i.printValue();     //101
    return 0;
}
```
```cpp
int a = 1;
int &b = a;

```