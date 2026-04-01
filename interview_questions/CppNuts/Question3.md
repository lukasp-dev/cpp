# what is `const` function

when you append `const` to a function signature, you are making a formal promise: "Calling this function will not change the observable state of the object."

Inside a `const` function, every member variable of the class becomes read-only.
```cpp
class Tradingaccount {
    double balance;
public:
    double getBalance() const {
        //balance += 10.0; // ERROR: compiler will stop
        return balance; // OK: Reading is allowed.
    }
}
```

### The hardware: Thread Safety and Caching

In HPC, we often process data in parallel (using threads).
- Concurrency: If a function is `const`, it is safe to be called by 100 difference threads at the exact same time on the same object. Since no thread is writing data, there is no "Data Race".
- The Cache: CPUs use a "Consistency Protocol" (like MESI). When a CPU core writes to memory, it must tell all other cores to invalidate their caches. Since `const` functions don't write, the data stays "Shared" and "Clean" in the CPU cache, leadng to much higher execution speeds.

### The Compliler: The "Aliasing" optimization
If a compiler knows a function is `const`, it can sometimes optimize out repreated memory reads.

```cpp
void calculateRisk(const Portfolio& p){
    double v1 = p.getValue();
    do_something_else();
    double v2 = p.getValue();

    // If getValue() is `const`, and the compiler can prove p wasn't modified, if might just reuse v1 instead of reading memory again for v2.
}
```

### The Core Concept: The Implicit `this` Pointer

In C++, member functinos don't just "exist" inside an object. THey are regular functions that receive a hidden argument called `this`.

**Non-const Member Function**
When you define anormal function, the compiler treats it like this:
- Your Code: `void update() {...}`
- Copmiler's view: `void update(Widget* const this) {...}`
- The `this` pointer points to a **mutable** (changeable) object. You can modify any member variable.

**Const Member Function**
When you add `const` at the end, you change the type of that hidden pointer:
- Your Code: `void check() const {...}`
- Compiler's View: `void check(cons Widget* const this) {...}`
- The `this` pointer now points to a `const` object. If you try to write `balance = 100;`, the compiler sees `this->balance = 100;` and throws an error because `this` points to a constant.