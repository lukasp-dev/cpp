# `static` deep dive

1) Static Local Variables (Inside a Function)
:A variable declared inside a function with the `static` keyword.  
- Lifetime: Extends from the first time the function is called until the end of the program. 
- Initialization: It is initialized only once. Subsequent calls to the function skip the initialization line and use the previous value.
- Storage: Stored in the Data Segment (if initialized) of BSS(if uninitialized), not on the Stack.

2) Static Member Variables (Inside a Class): A variable shared by all instances of a class.
- Ownership: It does not belong to a specific object; it belongs to the Class itself.
- Memory: Only one copy exists in memory, regardless of how many objects are created `sizeof(Object)` does not include static members.
- Declaration vs. Definition: Must be declared in the .h file and (usually) defined/initialized in the .cpp file.

3) Static Global Variables / Functions (Files scope)

- Visibility (Internal Linkage): It is only visible within the Translation Unit (the .cpp file) where it is defined.
- Encapsulation: It prevents "Symbol Collision." Other files cannot see or use this variable, even with the extern keyword.

4) Static Member Function: A function in a class that can be called without an instance.
- Constraints: It cannot access `this` pointer or non-static member variables/functions.
- Utility: Acts like a regular global function but is scoped within the class namespace.

### 추가 설명
일반 클래스의 `static` 변수는 프로그램 전체에 단 하나만 존재하지만, 템플릿 클래스의 `static` 변수는 인스턴스화된 타입 (Type) 마다 각각 하나씩 생성됨.
- 원리: 컴파일러는 `StaticTest<int>` 와 `StaticTest<double>`을완전히 다른 두개의 클래스로 처리함.
- 결과: 각 타입은 자신만의 전용 `static` 변수 영역을 가짐.

```cpp
template <typename T>
class Tracker {
public:
    static int count;
};

// 정의 및 초기화
template <typename T>
int Tracker<T>::count = 0;

int main() {
    Tracker<int>::count = 10;
    Tracker<double>::count = 50;

    // Tracker<int>::count는 여전히 10임 (서로 간섭 안 함)
}
```

템플릿 클래스와 마찬가지로, 템플릿 인자가 다르면 함수 내의 `static`변수도 별도의 메모리 공간을 가짐.
```cpp
template <typename T>
void count_calls() {
    static int count = 0; // T가 다르면 메모리 주소가 다름
    count++;
    std::cout << typeid(T).name() << " count: " << count << "\n";
}

int main() {
    count_calls<int>();    // int count: 1
    count_calls<int>();    // int count: 2
    count_calls<double>(); // double count: 1 (int와 별개임)
}
```