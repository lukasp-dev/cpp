# How to return multiple values from a function

```cpp
#include <iostream>
#include <string>

struct TradeResult {
    double price;
    int quantity;
    char side;
};

TradeResult executeTrade(bool fill){
    if(fill) {
        return {105.25, 100, 'B'}; // Uniform initialization (C++11+)
    }
    return {0.0, 0, 'N'};
}

int main() {
    auto [price, qty, side] = executeTrade(true);
    
    if(side != 'N') {
        std::cout << "Executed " << qty << " units at $" << price << "\n";
    }
    return 0;
}
```

### Why is this best way

**1) Zero Overhead (RVO/NRVO)**

In the old days, people worried that returning a `struct` would copy data. In modern C++, **Return Value Optimization (RVO)** ensures that the `TradeResult` is constructed directly in the memory of the `main` function. There is **zero copying** involved.

```cpp
TradeResult fun() {
    return {100.0, 10, 'B'}; 
}

int main() {
    // 컴파일러는 내부적으로 'res'의 메모리 주소를 fun()에게 전달함. 그러면 fun 함수는 자기 stack에 struct을 만드는게 아니라, main 이 알려준 그 빈자리에 가서 직접 데이터를 써넣는다.
    TradeResult res = fun(); 
}
```

**why it is better to use `struct` over `tuple`**

With `st::tuple`, you don't control the order of data in memory. With a `struct`, you do. By placing the `double` first, you ensure the struct is aligned to 8 bytes, which makes CPU memory fetches faster.

