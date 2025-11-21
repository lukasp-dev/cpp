#include <iostream>
using namespace std;

template <typename T>
struct SNode {
    T data;
    SNode<T>* next;
    SNode(T& data){
        this->data = data;
        this->next = nullptr;
    }
};

template <typename T>
class SinglyLinkedList{
private:
    SNode<T>* head;
    SNode<T>* tail;
    int size;

public:
    SinglyLinkedList(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    bool isEmpty() const { return size == 0; }
    int getSize() const { return size; }

    void addToFront(const T& data){
        SNode<T>* node = new SNode<T>(data);
        if(isEmpty()){
            head = tail = node;
        }else{
            node->next = head;
            head = node;
        }
        size++;
    }

    void addToBack(const T& data){
        SNode<T>* node = new SNode<T>(data);
        if(isEmpty()){
            head = tail = node;
        }else{
            
        }
    }

    T removeFromFront() {
        
    }
};