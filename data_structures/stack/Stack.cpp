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
class Stack{
private:
    Node<T>* topPtr;
public:
    Stack(){
        this->topPtr = nullptr;
    }

    bool isEmpty(){
        return topPtr == nullptr;
    }

    void push(T data){
        Node<T>* node = new Node<T>(data);

        if(isEmpty()){
            topPtr = node;
        }else{
            node->next = topPtr;
            topPtr = node;
        }
    }

    void pop(){
        if(isEmpty()){
            return;
        }else{
            Node<T>* curr = topPtr;
            topPtr = curr->next;
            delete curr;
        }
    }

    T top(){
        if(isEmpty()) throw runtime_error("Stack is empty");
        return topPtr->data;
    }

    void print(){
        Node<T>* temp = topPtr;
        while(temp){
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << "\n";
    }
};

int main(){
    Stack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);
    st.print(); // 30 20 10

    st.pop();
    st.print(); // 20 10

    cout << st.top() << "\n"; // 20a
}