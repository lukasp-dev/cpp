The `priority_queue`, by default, it acts a s Max-heap, meaning the largest element is always at the "top."

| Operation | Complexity | Description |
| :--- | :--- | :--- |
| `push()` | $O(\log n)$ | Inserts an element and "bubbles" it to the right spot. |
| `pop()` | $O(\log n)$ | Removes the top element and re-balances the heap. |
| `top()` | $O(1)$ | Returns a reference to the element at the top. |
| `size()` | $O(1)$ | Returns the number of elements. |

#### Max-Heap(Default)
```cpp
priority_queue<int> maxHeap;
```

#### Min-Heap
```cpp
priority_queue<int, vector<int>, greater<int>> minHeap;
```

#### Custom Priority (Structs/Objects)
If you are storing custom objects, you need to tell C++ how to compare them by overloading the `operator<` or providing a custom comparator.

```cpp
struct Task {
    int priority;
    string name;

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

priority_queue<Task> tasks;
```

- `top`, `pop`
```cpp
while(!pq.empty()){
    cout << pq.top << " ";
    pq.pop(); 
}
``` 

#### priority 를 정의
1. 한 문장으로 정리
-  `return (condition);` 이 `true`가 되는 순간, 왼쪽(`a`)은 뒤(바닥)으로 밀려난다.
```cpp
#include <iostream>
#include <queue>
#include <memory>
#include <string>

using namespace std;

struct Person {
    int age;
    string name;
    
    Person(int age, string name) : age(age), name(name) {}
};

struct cmp {
    bool operator()(const Person& a, const Person& b){
        if(a.age != b.age){
            return a.age > b.age; // 나이가 많으면 뒤로 
        }

        return a.name > b.name; // 사전순으로 뒤면 뒤로
    }
};

int main(){
    shared_ptr<Person> p1 = make_shared<Person>(21, "Jewook Park");
    shared_ptr<Person> p2 = make_shared<Person>(21, "Jehoon Park");

    priority_queue<Person, vector<Person>, cmp> pq;
    pq.push(*p1);
    pq.push(*p2);

    cout << pq.top().name << "\n"; // Jehoon Park
}
```


