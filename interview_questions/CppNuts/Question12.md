# How to return an array from function in C & C++

이렇게 하면 안됨. `arr`는 여기서 지역 변수고 이렇게 할 사에 `function`의 스코프가 끝나면 스택에서 사라짐.
```cpp
#include <iostream> 
using namespace std;

int* function () {
    int arr[3] = {1, 2, 3};
    return arr;
}

int main() {
    int * arr = function ();
    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;
    return 0;
}
```

이렇게 하면 working. `static` 키워드를 쓰면 전체 프로그램이 끝날 때까지 메모리에서 안 없어짐.
```cpp
#include <iostream> 
using namespace std;

int* function () {
    static int arr[3] = {1, 2, 3};
    return arr;
}

int main() {
    int * arr = function ();
    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;
    return 0;
}
```

이렇게 해도 되는 이유는 `new` 키워드를 쓰면 오브젝트 자체가 heap 메모리에 로드 되고,
function 스코프가 끝나도 object가 있는 heap의 주소를 가지고 있는 포인터를 리턴했기 때문에,
그대로 main 스코프의 `int *` type 의 arr이 받아서 쓰면 됨.
```cpp
#include <iostream> 
using namespace std;

int* function () {
    int* arr = new int[3];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    
    return arr;
}

int main() {
    int * arr = function ();
    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;
    return 0;
}
```