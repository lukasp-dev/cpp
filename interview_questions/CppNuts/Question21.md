# Printing "hi" without using `for` loop or recursion

```cpp
#include <iostream>
#include <vector>

class Base {
public:
    Base(){ std::cout << "hi" << "\n"; }
};

int main(){
    int N;
    std::cin >> N;
    std::vector<Base> arr(N);
    /*
    hi
    hi
    hi
    hi
    hi
    hi
    hi
    hi
    hi
    hi
    */

    
    return 0;
}
```
C++은 배열을 만들 때 각 칸마다 생성자를 호출해줘야 하기 때문이다.
