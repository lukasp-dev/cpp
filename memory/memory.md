
## Memory Segment Overview

![memory layout](https://gabrieletolomei.wordpress.com/wp-content/uploads/2013/10/program_in_memory2.png)

1. Text Segment (Code segment)
- Role: Stores the executable machine instructions of the program.
- Characteristics:
    - Read-Only: To prevent accidential or malicious modification of the program logic, any attep to write to this sefment results in a **Segmentation Fault**.
    - Fixed Size: The size is determined at compile time and remains constant throughout execution.

2. Data Segment (Initialized Data)
- Role: COntains global and static variables that have been explicitly initialized with non-zero values.
- Granular Sub-Divisions:
    - Read_Write Area: For variables like `int g_count = 10;` that change during runtime.
    - Read-Only Area (ROData): For consants like `const in MAX_USERS = 10;` and string literals like `"Hello World"`.
- Impact: These values are stored directly in the binary file, increasing hte executable's size.

3. BSS Segment (Uninitialized Data)
- Role: Stands for "Block Started by Symbol." It stores global and static variables that are uninitialized or initialized to zero.
- C++ Example: `int g_buffer[1024];` or `static in s_flag = 0;`.
- Efficiency: Instead of storing 1024 zeros in the binary file, the executable just records th total size required. The OS clears thismemoery to zero when the program loads.

4. Heap (Dynamic Memory)
- Role: Managed by the developer at runtime for dynamic allocations.
- Characteristics:
    - Growth Direction: Grows **upwards** (from lower to higher addresses).
    - In C++, memory is allocated via `new` (or `malloc`) and must be deallocated via `delete` (or `free`).
    - Frequent allocations/deallocations of varying sizes can lead to external fragmentation over time.

5. Memory Mapping Segment (The "Gap")
- Role: A massive area between the Heap and the Stack used for specialized memory tasks.
- Contents:
    - Shared Libaries: Standard libraries (like `libc++`) and external `.so` or `.dll` files are loaded here.
    - If `new` requests an exceptionally large block, the allocator may bypass the Heap and use `mmap` to allocate space here directly.

6. Stack (automatic Memory)
- Role: Stores **Stack Frames** containing local variables, function arguments, and return addresses.
- Characteristics:
    - Growth Direction: Grow **downwards** (from higher to lower addresses).
    - LIFO
    - Limitations: Limited size (typically 1-8MB). Deep recursion or massive local arrays lead to `Stack Overflow`.

7. OS Kernel Space
- Role: Reserved for the operating system's core (the Kernel).
- Characterisics:
    - User-level code is prohibited from accessing these addresses.
    - Interface: Interaction occurs only through **System Calls**. Any direct access attempt triggers an immediate hardware exception (Segfault).

## Memory Segment Reference Table

| Segment | C++ Example | Lifetime | Speed | Storage Location | Key Characteristic |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Stack** | `int x;` (local variable) | Scope-based (Automatic) | **Ultra-Fast** | RAM (Stack Area) | LIFO structure; managed by CPU Stack Pointer. |
| **Heap** | `new int[10];` (dynamic) | `new` until `delete` (Manual) | **Moderate** | RAM (Heap Area) | Dynamic sizing; risk of fragmentation and leaks. |
| **BSS** | `int g_arr[500];` | Program Start to End | N/A | RAM / Executable Info | Uninitialized global/static; zeroed by OS at load. |
| **Data** | `int g_val = 42;` | Program Start to End | N/A | RAM / Binary Image | Initialized global/static; stored in the executable file. |
| **Text** | `void main() { ... }` | Program Start to End | N/A | Flash / Read-Only RAM | Read-only machine instructions (Code). |