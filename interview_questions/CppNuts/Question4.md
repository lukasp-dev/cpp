# What is function hiding?
**Function Hiding** occurs when a member function in a derived class has the **same name** as a function in the base class.

In C++, if the derived class declares a functiono named `f`, it hides all functions named `f` in the base class, refarless of whether the signatures (parameters) are different.

```cpp
class BaseStrategy {
public:
    void execute(int quantity) { /* ... */ }
};

class AggressiveStrategy : public BaseStrategy {
    // This hides BaseStrategy::execute(int)
    void execute(double price) {/* ... */}
};

int main(){
    AggressiveStrategy strat;
    strat.execute(100); // ERROR! The compiler onlu sees the (double) version.
}
```
|Term|Scope|Requirement|
|------|---|---|
|Overloading|Same Scope|Same name, different parameters|
|Overriding|Base & Derived|Same signature + `virtual` keyword|
|Hiding|Base & Derived|Same name, regardless of parameters|

### how to fix it
```cpp
class AggressiveStrategy : public BaseStrategy {
public:
    using BaseStrategy::execute;

    void execute(double price) {/*...*/}
};

int main(){
    AgreesiveStrategy strat;
    start.execute(100); // Now it finds BaseStrategy::execute(int)
}
```

**Name lookup happends before overlaod resolution** -> Name hiding is a compile-time mechanism.