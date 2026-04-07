# The difference between pointer and reference

### 1) Nullability & Initialization
A pointer is an **object**, a reference is an **identity**.

**Pointer:The Optional Handle**
A pointer can be uninitialized or set to `nullptr`. This means every time you use it, you incur a "safety tax".
```cpp
void process(int* ptr){
    if(ptr != nullptr){
        *ptr += 10;
    }
}
```
The `if (ptr != nullptr)` check causes a **Branch Instruction**. If the CPU mispredicts whether the pointer is null, the entire instruction pipeline is flushed, costing ~20 nanoseconds.

**Reference: The Guaranteed Alias**
A reference must be initialized immediately and cannot legally be null. You could technicalaly force a null reference (`int &r = *ptr_to_null`), but this is **Undefined Behavior (UB)**. Compilers optimize assuming UB never happens, meanaing they might delete your safety checks entirely.

```cpp
void process(int& ref) {
    ref += 10; // No null check needed. Direct execution.
}
```

### 2) Arithmetic Operations
This is a difference between **navigating memory** and **modifying data**.

**Pointer Arithmetic: Moving the GPS**
Pointers allow you to move through memory addresses.
```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* ptr = arr;

ptr++;
*ptr = 100; // arr[1] is now 100
```

**Reference Arithmetic: changing the house**
You cannot "move" a reference to the next memory address. Any arithmetic is applied to the **value**.
```cpp
int a = 10;
int& ref = a;

ref++; // 'a' becomes 11. The reference still points to 'a'
```
This prevents "Pointer Chasing." Using references ensures that you don't accidentally start reading out-of-bounds memory, which is a common source of cache misses and segmentation faults.

### 3. Reassignment(The "Alias" Trap)
**Pointer Re-assignment: Changing Targets**
A pointer is a variable that holds an address. You can change that address at any time.
```cpp
int a = 10, b = 20;
int* ptr = &a; //ptr -> a
ptr = &b;      //ptr -> b (The pointer itself changed)
```
**Reference Re-assignment: Value Transfer**
Arefernece is permanently bound to the its initial target. You cannot "re-seat" it.
```cpp
int a = 10, b = 20;
int& ref = a; // ref is now another name for 'a'
ref = b;      // This does NOT make ref point to 'b';
              // This COPIES the value of 'b' into 'a';
              // Result: a is 20, b is 20, ref still points to 'a';
```


### Extra code example

```cpp
// Online C++ compiler to run C++ program online
#include <iostream>

int main() {
    int a = 100;
    int &b = a;
    int *c = &a;

    std::cout << "ADDRESSES:\n";
    std::cout << "a: " << &a << "\n"; // a: 0x7ffeb90a2c54
    std::cout << "b: " << &b << "\n"; // b: 0x7ffeb90a2c54
    std::cout << "c: " << &c << "\n"; // c: 0x7ffeb90a2c48

    int var = 200;
    b = var;
    std::cout << a << "\n"; // a의 값도 바뀌어버림

    return 0;
}

```
