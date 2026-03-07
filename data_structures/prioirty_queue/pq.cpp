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