# Segmentation Fault

1) What is Segmentation Fault?
A **Segmentation Fault** is a specific kind of error caused by accessing memory that the CPU's Memory Management Unit cannot address or is restricted by the Operating System.
- The ***Segment***: memory is divided into segments (Stack, Heap, Data, Code)
- The ***Fault***: You tried to read, write, or execute a segment incoreectly.

2) Common Causes with Examples

    A) Dereferencing a `NULL` pointer
    ```cpp
    int main(){
        int* ptr = nullptr;
        *ptr = 10; // ❌ SEGFAULT: Accessing address 0x0 is strictly forbidden.
        return 0;
    }
    ```

    B) Accessing Out-of-Bounds (Buffer Overflow)
    ```cpp
    int main(){
        int arr[10];
        // Trying to access an index far outside the allocated stack frame
        std::cout << arr[1000000]; // ❌ SEGFAULT: You've left your process's memory space.
        return 0;
    }
    ```

    C) Writing to Read-Only Memory
    ```cpp
    int main() {
        char* str = "Jewook";
        str[0] = 'B'; // ❌ SEGFAULT: You cannot write to a read-only segment.
    }
    ```

    D) Stack Overflow (Infinite Recursion)
    If a function calls itself forever, the Stack Segment runs out of space and collides with another segment.
    ```cpp
    void infinite() {
    int large_array[1000];
    infinite(); // ❌ SEGFAULT: Stack overflow.
    }
    ```