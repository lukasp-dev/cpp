#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(const T& d){
        this->data = d;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

template <typename T>
class DoublyLinkedList{
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublyLinkedList(){
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    bool isEmpty(){
        return this->size == 0;
    }

    int getSize(){
        return this->size;
    }

    void addToFront(const T& data){
        Node<T>* node = new Node<T>(data);

        if(isEmpty()){
            head = node;
            tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        size++;
    }

    void addToBack(const T& data){
        Node<T>* node = new Node<T>(data);

        if(isEmpty()){
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        size++;
    }

    void addAtIndex(int index, const T& data){
        if(index < 0 || index > size) throw runtime_error("bad index");

        if(index == 0) { addToFront(data); return;}
        if(index == size) { addToBack(data); return;}

        Node<T>* curr;
        if(index < size/2){
            curr = head;
            for(int i=0; i<index-1; i++) curr = curr->next;
        } else {
            curr = tail;
            for(int i=size-1; i>index-1; i--) curr = curr->prev;
        }

        Node<T>* node = new Node<T>(data);
        node->next = curr->next;
        node->prev = curr;
        curr->next->prev = node;
        curr->next = node;

        size++;
    }

    T removeFromFront(){
        if(isEmpty()) throw runtime_error("empty.");

        Node<T>* temp = head;
        T res = temp->data;

        if(size == 1){
            head = nullptr; 
            tail = nullptr;
        }else{
            head = temp->next;
            head->prev = nullptr;
        }
        delete temp;
        size--;
        return res;
    }

    T removeFromBack(){
        if(isEmpty()) throw runtime_error("empty.");

        Node<T>* temp = tail;
        T res = temp->data;

        if(size == 1){
            head = nullptr;
            tail = nullptr;
        }else{
            tail = temp->prev;
            tail->next = nullptr;
        }
        delete temp;
        size--;
        return res;
    }
    
    T removeAtIndex(int index){
        if(index < 0 || index >= size) throw runtime_error("bad index.");

        if(index == 0) return removeFromFront();
        if(index == size-1) return removeFromBack();
        
        Node<T>* temp;

        if(index < size/2){
            temp = head;
            for(int i=0; i<index; i++){
                temp = temp->next;
            }
        }else{
            temp = tail;
            for(int i=size-1; i > index; i--){
                temp = temp->prev;
            } 
        }
        T res = temp->data;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        size--;
        return res;
    }

    T get(int index) const {
        if(index < 0 || index >= size) throw runtime_error("bad index.");

        if(index == 0){
            return head->data;
        }
        if(index == size-1){
            return tail->data;
        }

        Node<T>* temp;

        if(index < size/2){
            temp = head;
            for(int i=0; i<index; i++){
                temp = temp->next;
            }
        }else{
            temp = tail;
            for(int i=size-1; i>index; i--){
                temp = temp->prev;
            }
        }

        return temp->data;
    }
};

int main(){
    DoublyLinkedList<string> dll;
    dll.addToBack("B");
    dll.addToFront("A");
    dll.addToBack("C");
    dll.addAtIndex(1, "X");

    cout << dll.get(1) << "\n";
    cout << dll.removeFromBack() << "\n";
    cout << dll.removeFromFront() << "\n";
    cout << dll.get(0) << "\n";

    return 0;
}


