### lvalue and rvalue

**lavalue**: objects(object is a region of storage in the execution environmnet that can store a value. -> any type, including primitive types like `int` and `float`, as well as user-defined types like classes and structs are technically objects.) that have an identifiable, persistent memory location and can appear on both the left and right sides of an assignment.

**rvalue**: temporary values or objects that do not persist beyong the expression that uses them and can only appear on the right side of an assignment.

When C++ gets an parameter, it can specify how to get one.
1. `void func(int& a)` means it will get only **lvalues** as parameters, meaning no rvalue can be passed as the parameter.
2. `void func(int&& a)` means it will get only **rvalues** as parameters, meaning no lvalue can be passed as the parameter.

Most of the times, **number 1** is true, except when `const` keyword is appended at front. so for example, `void func(const int& a)`.

```cpp
#include <iostream>
#include <string>

void func(int& a){
    cout << "this function was fired~!" << "\n";
}

int main(){
    func(10); // error: expects dn lvalue for 1st argument.
    return 0;
}
```

Also, **number 2** is true, except for when we use `std::move()`. 

```cpp
std::vector<double> large_data = loadMarketData();
// Case A: Copy(Slow)
// std::vector<double> target = large_data;
// -> copies the entire data one by one. memory is wasted.

// Case B: Move (Fast)
std::vector<double> target = std::move(large_data);
// now, target is the new owner of this data.
// now target holds the start address of the object in the heap.
// large_data's size is now 0.
```

| 호출 형태 (Argument) | `void f(int&)` | `void f(const int&)` | `void f(int&&)` | **최종 선택 (Best Match)** |
| :--- | :---: | :---: | :---: | :--- |
| **`int x = 10; f(x);`** (Lvalue) | **1순위** | 2순위 | 호출 불가 | **`f(int&)`** |
| **`f(10);`** (Rvalue) | 호출 불가 | 2순위 | **1순위** | **`f(int&&)`** |
| **`const int y = 20; f(y);`** | 호출 불가 | **1순위** | 호출 불가 | **`f(const int&)`** |
| **`f(std::move(x));`** | 호출 불가 | 2순위 | **1순위** | **`f(int&&)`** |

| Feature | `int* ptr = new int[1000];` (Raw Pointer) | `std::vector<int> v(1000);` (Object/RAII) |
| :--- | :--- | :--- |
| **Stack Occupancy** | Exactly **8 bytes** (Stores only the memory address) | Typically **24-32 bytes** (Address + Size + Capacity) |
| **Ownership** | **None.** It is just a signpost pointing to a location. | **Strong.** It acts as the owner/manager of the allocated memory. |
| **Auto Cleanup** | **No.** Manual `delete[]` is required, or it causes a **Memory Leak**. | **Yes.** The **Destructor** automatically frees memory when it goes out of scope. |
| **Copy Behavior** | **Shallow Copy.** Only the address is copied, leading to potential "Double Free" errors. | **Deep Copy.** The entire data is duplicated. Supports **Move Semantics** for efficiency. |
| **Safety** | High risk of memory leaks and dangling pointers. | High safety through automated lifecycle management. |

---

#### move example

```cpp
#include <iostream>
#include <vector>
#include <utility> // need this for std::move

class DataManager{
public:
    void processData(std::vector<double>&& data){
        std::cout << "=== Inside processData (RValue version) ---" << std::endl;

        my_storage = std::move(data);
        std::cout << "Data moved to storage. Size: " << my_storage.size() << std::endl;
    }

private:
    std::vector<double> my_storage;
};

int main(){
    std::vector<double> large_lvalue(100000, 1.23);
    std::cout << "Original lvalue size: " << large_lvalue.size() << std::endl;

    DataManager manager;

    manager.processData(std::move(large_lvalue));

    std::cout << "--- After Move ---" << std::endl;
    std::cout << "Original lvalue size: " << large_lvalue.size() << std::endl;

    return 0;
}

// Original lvalue size: 100000
// === Inside processData (RValue version) ---
// Data moved to storage. Size: 100000
// --- After Move ---
// Original lvalue size: 0
```

### `move` 에 대하여 
물리적으로는 주소가 존재함에도 불구하고, 언어 차원에서 주소 접근을 막아버림으로써 이를 `Rvalue`로 취급하는 것.
(Despite having a persistent memory location in physical terms, the language specification forbids taking its address, effectively categorizing it as an rvalue.)

More specifically, 
"In C++, an **rvalue** is essentially an expression that does not have a persistent **identity** in the eyes of the compiler. When we use `std::move(x)`, we are not physically moving the object in memory; rather, we are **casting** it to an **xvalue** (expiring value).

Even though the object still resides at the same **physical memory address**, the C++ type system treats the result of `std::move` as an anonymous temporary. By **restricting address-of operations** on this result, the language ensures that the object's resources can be safely 'stolen' or moved without the risk of the original identifier being misused."