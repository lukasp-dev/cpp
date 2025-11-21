#include <iostream>
#include <list>
using namespace std;

class LRUCache {
private:
    int capacity;
    list<int> order;
    unordered_map<int, pair<list<int>::iterator, int>> lookup;

public:
    LRUCache(int capacity){
        this->capacity = capacity;
    }

    int get(int key){
        auto it = lookup.find(key);
        if(it == lookup.end()) return -1;
        
        auto orderIt = lookup[key].first;
        order.erase(orderIt);

        order.push_front(key);
        lookup[key].first = order.begin();

        return it->second.second;
        
    }

    void put(int key, int val){
        auto it = lookup.find(key);
        if(it != lookup.end()){
            auto orderIt = lookup[key].first;
            order.erase(orderIt);
        }
        order.push_front(key);
        lookup[key] = make_pair(order.begin(), val);
        
        if(order.size() > capacity){
            auto it = order.end(); it--;
            lookup.erase(*it);
            order.erase(it);
        }
    }
};

int main(){
    LRUCache* cache = new LRUCache(2);

    cache->put(1, 1);
    cache->put(2, 2);
    cout << cache->get(1) << "\n";
    cache->put(3, 3);
    cout << cache->get(2) << "\n";
    cache->put(4, 4);
    cout << cache->get(1) << "\n";
    cout << cache->get(3) << "\n";
    cout << cache->get(4) << "\n";

    return 0;
}