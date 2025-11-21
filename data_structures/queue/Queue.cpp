#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T val){
        this->data = val;
        this->next = nullptr;
    }
};

template <typename T>
class Queue{
private:
    Node<T>* frontPtr;
    Node<T>* endPtr;
    
public:
    Queue(){
        this->frontPtr = nullptr;
        this->endPtr = nullptr;
    }

    bool isEmpty(){
        return frontPtr == nullptr;
    }

    void enqueue(T data){
        Node<T>* node = new Node<T>(data);

        if(isEmpty()){
            frontPtr = node;
            endPtr = node;
        }else{
            endPtr->next = node;
            endPtr = node; 
        }
    }

    void dequeue(){
        if(isEmpty()) return;
        Node<T>* temp = frontPtr;
        frontPtr = frontPtr->next;
        if(frontPtr == nullptr) endPtr = nullptr;
        delete temp;
    }

    T front(){
        if(isEmpty()) throw runtime_error("The queue is empty now.");
        Node<T>* node = frontPtr; 
        return node->data;
    }

    void print(){
        Node<T>* curr = frontPtr;
        while(curr){
            cout << curr->data << " ";
            curr = curr->next;
        }

        cout << "\n";
    }
};

int main(){
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.print(); // 10 20 30

    q.dequeue();
    q.print(); // 20 30

    cout << q.front() << "\n"; // 20
}
