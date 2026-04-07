# Dangling Pointer

```cpp
#include <iostream>

void func(int* ptr){
    std::cout << *ptr <<std::endl;
    delete ptr;
}

int main() {
    int *p1 = new int(100);
    int *p2 = p1;
    func(p2); // 100
    
    std::cout << *p1 << std::endl; // 77090 => garbage value
    
    return 0;
}
```

1) What is a dangling pointer?
- A dangling pointer is a pointer that still stores the memory address of an object after that object has been **deallocated** (deleted). The pointer points to a memory location that is no longer valid or has been reclaimed by the system.
    - **key characteristic:** The pointer is not `NULL`, but the data it points to is "gong" or "corrupted".
    - **The Danger:** Accessing a dangling pointer leads to Undefined Behavior (UB), it might return a garbage value, or it might cause a Segmentation Fault.