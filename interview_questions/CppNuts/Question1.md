### Question 1: What is void and void pointer (void *) in C/C++?

### void
1) void is used to denote nothing
2) if some function is not returning anything, then we use `void` type to denote that.
    ```cpp
    #include <iostream>

    void fun(){
        std::cout << "hello world\n";
    }
    ```
3) if some function doesn't take any parameter, then we use `void` type to denote that.
    ```cpp
    #include <iostream>

    void fun(void){
        std::cout << "hello world\n";
    }
    ```
4) size of `void` is 1 byte in gcc compilers but in other it is not valid to check sizeof `void`.

### void* 
1) `void*` is universal pointer
2) we can convert any data type pointer to `void*` (except function pointer, pointer to `const` value or `volatile` value)
3) `void*` cannot be dereferenced.

    ```cpp
    #include <iostream>
    using namespace std;

    int main(){
        // executed just fine
        // int* const ptr = reinterpret_cast<int*>(10);
        // void* v = static_cast<void*>(ptr);
        
        // error: invalid ‘static_cast’ from type ‘const int*’ to type ‘void*’
        int const* ptr = reinterpret_cast<const int*>(10);
        void* v = static_cast<void*>(ptr);

        volatile int* v_ptr = reinterpret_cast<volatile int*>(0x4000);
        // ❌ 에러: volatile 성격을 멋대로 버릴 수 없음
        void* p1 = static_cast<void*>(v_ptr); 
        // ✅ 성공: volatile 성격을 그대로 유지하면서 형변환
        volatile void* p2 = static_cast<volatile void*>(v_ptr);

        //dereferencing only works complete(non-void, typed) type of pointer, not the void pointer
        int *j = new int(10);
        void* void_ptr = static_cast<void*>(j);
        cout << *(static_cast<int*>(void_ptr)) << "\n";
                
        return 0;
    }
    ```

### Important to note
Only `void` means nothing and `void *` means pointer to anything (except function pointer, pointer to const value, and the pointer to volatile value)

**Use cases**
1) `malloc` and `calloc` returns `void*` so that we can typecast to our desired data type.
2) `void*` are used to create generic functions in C. (compare function used in qsort function in C).

    ```cpp
    int main(){
        // ❌ C++에서는 컴파일 에러! (void*를 int*에 바로 대입 불가)
        // int* ptr = malloc(sizeof(int) * 10);
        int* ptr = static_cast<int*>(malloc(sizeof(int) * 10));
        // new 쓰는게 정석
        int* ptr = new int[10];

        return 0;
    }
    ```