# Struct Padding

CPUs do not access memory byte-by-byte. They fetch data in fxed-sized chunks called **Words** (8 bytes on 64-bit systems).

- The Rule:  A data type of size ***n*** must reside at a memory address that is a multiple of ***n***.
- The Padding: Compilers insert "slack" bytes between members to satisfy alignmentrequirements, preventing CPU execution errors or performance hits.

### The Double Access
A performance penalty occurs when data is misaligned, forcing the hardware to perform **Split Load**. This manifests at two critical levels:

**A Word Level(L1 Cache <-> Register)**
If an 8-byte `double` starts at an unaligned address (e.g., `0x04`), it spans across two 8-byte words.
- Mechanism: The CPU fetches two separate words, then executes bitwise `SHIFT` and `OR` operations to merge the fragments into a single register.
- Penalty: A 1-cycle instruction becomes a multi-step micro-op sequence, reducing instruction throughput.

**Cache Line Level (Memory ↔ L1 Cache)**
If data spans across two 64-byte Cache Lines (e.g., second object starting at byte 62 of a line).

Mechanism: The CPU must wait for two distinct cache line fills.

Penalty: If the second line is not in L1, it triggers a Cache Miss, stalling the CPU for hundreds of nanoseconds. This is the primary source of latency jitter in HFT.


```cpp
// BAD: High padding and potential for split loads
struct Unoptimized {
    char type;      // 1 byte
    // 7 bytes padding inserted here
    double price;   // 8 bytes (Starts at offset 8)
    int id;         // 4 bytes
    // 4 bytes padding at the end to align the struct size to 8
}; // sizeof = 24

// GOOD: Minimal padding and cache-friendly
struct Optimized {
    double price;   // 8 bytes (Starts at offset 0)
    int id;         // 4 bytes
    char type;      // 1 byte
    // 3 bytes padding at the end
}; // sizeof = 16
```