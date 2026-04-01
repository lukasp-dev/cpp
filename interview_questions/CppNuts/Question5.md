# What is a `friend`?

a `friend` function is a "backdoor" pass. It is a function that is not a member of a class but is granted full access to that class's private and protected members.

1) keyword friend is used to make some [function OR class] as friend of your class.
2) Friend function OR friend class can access private/public/protected Data Member OR Member Functions of another class.
3) Function can not become friend of another function.
4) Calss cannot become friend of function
5) Friendship is not mutual. If a class A is friend of B, then B deosn't become frend of A automatically.
6) Friendship is not inherited.

### Syntax
To make function a friend, declare t inside the class preceded by the `friend` keyword.
```cpp
class Order {
int orderID;
double price;

public:
    Order(int id, double p) : orderId{id}, price{price} {}
    friend void printOrderDetails(const order& o);
};

// This is a regular global function, NOT a member of Order
void printOrderDetails(const Order& o) {
    std::cout << "ID: " << o.orderID << ", Price: " << o.price << std::endl;
}
```

### Friend classes

```cpp
#include <iostream>
using namespace std;

class Base {
    int x;
public:
    Base() {}
    Base(int a) : x{a}{}
    friend class GetSet;
};

class GetSet{
public:
    void set(Base& obj, int x) {obj.x = x;}
    int get(Base& obj) {return obj.x;}
};

int main() {
    Base obj(10);
    GetSet gs;
    cout << gs.get(obj) << "\n";
    gs.set(obj, 20);
    cout << gs.get(obj) << "\n";
    return 0;
}
```