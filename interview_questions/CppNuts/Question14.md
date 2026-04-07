# Use of friend functions and classes

### Fried function use case 

```cpp
#include <iostream>

class Base {
    int x;
public:
    Base(){}
    Base(int x):x{x}{}
    friend void func(Base& b);
};

void func(Base& obj){
    std::cout << obj.x << "\n";
    obj.x = 20;
    std::cout << obj.x << "\n";
}

int main() {
    Base b(10); // 이렇게 선언하면 스택에 생겼다가 사라짐.(just FYI)
    func(b); //10
             //20
    return 0;
}
```


<img src="/Users/a/Desktop/cpp/pictures/Question14_friend_class.png" width="300">

A friend (whether a function or a class) has the exact same access rights as a member function of the class that granted the friendship.

### friend class use case
```cpp
#include <iostream>
#include <string>
#include <vector>

class MarketData {
private:
    std::string symbol;
    double price;
    u_int64_t sequence_number;
    
    MarketData(std::string s, double p, u_int64_t seq) : symbol{s}, price{p}, sequence_number{seq}{}
    
    void update_price(double new_price){
        price = new_price;
        sequence_number++;
    }
    
    friend class MarketDataManager;
};

class MarketDataManager {
private:
    std::vector<MarketData> data_list;
    
public:
    void add_ticker(std::string s, double p) {
        // can access the private constructor of the MarketData class
        data_list.emplace_back(MarketData(s, p, 0)); 
    }
    
    void handle_update(int index, double new_price){
        // can call the private function of the =MarketData class
        data_list[index].update_price(new_price);
        
        std::cout << "Updated: " << data_list[index].symbol << " to " << data_list[index].price << "\n";
    }
};

int main(){
    MarketDataManager manager;
    manager.add_ticker("AAPL", 150.0);
    manager.handle_update(0, 155.5);
    
    // MarketData d("GOOG", 2000.0, 1); // ERROR: main 에서 private 생성자 접근 불가
    return 0;
}
```
