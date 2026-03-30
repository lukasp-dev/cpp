### Question 2: Explain OOP in C++

### 1. Encapsulation
Encapsulation is the grouping of data and methods. It is about protecting the **internal state** and optimizing the **Data Member Layout**.
- System Impact: By encapsulating data, we can reorder member variables to minimize Memory Padding and ensure that "hot" data members sit on the same Cache Line.

    ```cpp
    class OrderBook {
    private:
        // Encapsulation allows us to order these to minimize padding
        double last_price;  // 8 bytes
        uint64_t sequence;  // 8 bytes
        int32_t volume;     // 4 byte
        char symbol[4];     // 4 byte (Perfectly aligned to 24 bytes total)

    public:
        void update(double p, int32_t v){
            last_price = p;
            volume = v;
        }
        double get_price() const { return last_price; }
    }
    ```

### 2. Abstraction: Runtime v. Compile Time
Abstraction hides complexity. in systems programming we distinguish between Dynamic Abstraction (expensive) and Static Abstraction (zero-cost).
- Dynamic (Virtual): Flexible but involves a **vtable lookup** (extra indirection)
    - This is flexible because you can swap implementations at runtime (e.g., changing a trading strategy while the app is running).
    - Every call to `trade()`, for example, requires the CPU to look up the function address in the **vtable**. This prevents the compiler from **inlining** the code.
        - Main 2 runtime costs
            - additional memory that is required in order for us to store the `vtable` so that we can dispatch to the correct function that includes a member pointer in the actual base path that points to the `vtable`
            - every time we call a virtual function, we have to go through that table to determine which function to actually map to which is an additional performance penalty.
    - Let's say B is derived from A, meaning the B is a sub class of A. If we create a method in class A and mark it as virtual, we have the option of overriding that method in the B class to make it to do something else.
    ```cpp
    class IStrategy {
    public:
        virtual ~IStrategy() = default;
        virtual void trade() = 0;
    };

    class AggressiveStrategy : public IStrategy{
    public:
        void trade() override { /* Rapid buy/sell logic */ }
    };

    void run_engineer(IStrategy* strategy){
        // RUNTIME POLYMORPHISM
        // The CPU must follow a pointer to the vtable, then a pointer to the function. strategy->trade();
    }  
    ```

- Static (Templates): Zero runtime overhead. The compiler generates specific code for each type, allowing for **inlining**.
    - This uses Templates. The "interface" is implicit. If the class has a `trade()` method, it works. If not, it fails at **compile-**.
    
        ```cpp
        #include <iostream>

        class MarketMakerStrategy {
        public: 
            void trade() {
                std::cout << "some high volume strategy\n";
            }
        };

        template<typename T>
        void run_engine(T& strategy) {
            strategy.trade();
        }

        int main(){
            MarketMakerStrategy ms;
            run_engine(ms); // some high volume strategy
            
            return 0;
        }
        ```

### Polymorphism: The "Virtual Tax" vs. CRTP
If you need the "look and feel" of class hierarchy but cannot afford the `virtual` function performance penalty, you can use the **Curiously Recurring Template Pattern (CRTP)**.

**CRTP Example (Static Polymorphism)**
```cpp
template <typename Derived>
class BaseProcessor {
public:
    void execute() {
        //Static cast 'this' to the Derived type known at compile-time
        static_cast<Derived*>(this)->logic();
    }
};

class orderProcessor : public BaseProcessor<OrderProcessor> {
public:
    void logic() {
        // Specialized logic for handling orders
    }
};

// Usage
OrderProcessor op;
op.execute(); // Calls logic() with ZERO virtual overhead.
```