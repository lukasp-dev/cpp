#include <iostream>
using namespace std; 

template <typename T>
struct Node{
    T data;
    Node<T>* next;

    Node(T data){
        this->data = data;
        this->next = nullptr;
    }
};

template <typename T>
class CircularSinglyLinkedList{
private:
    Node<T>* head;

public:
    CircularSinglyLinkedList(){ head = nullptr; }

    void pushFront(T value){
        Node<T>* node = new Node<T>(value);
        if(head == nullptr){
            head = node;
            head->next = head;
        }else{
            node->next = head->next;
            head->next = node;

            T temp = head->data;
            head->data = node->data;
            node->data = temp;
        }
    }

    void popFront(){
        if(head == nullptr) return;

        if(head->next == head){
            delete head;
            head = nullptr;
            return;
        }

        Node<T>* second = head->next;
        head->data = second->data;
        head->next = second->next;
        delete second;
    }

    void print(){
        if (!head) return;
        Node<T>* cur = head;
        do {
            cout << cur->data << " ";
            cur = cur->next;
        } while(cur != head);
        cout << "\n";
    }
};

int main() {
    CircularSinglyLinkedList<int> cl;
    cl.pushFront(3);
    cl.pushFront(2);
    cl.pushFront(1);
    cl.print(); // 1 2 3

    cl.popFront();
    cl.print(); // 2 3

    return 0;
}