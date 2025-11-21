#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class ArrayList {
private:
    T* arr;
    int size;
    int capacity;

    void regrow() {
        int newCap = this->capacity * 2;
        T* newArray = new T[newCap];
        for (int i = 0; i < this->size; i++) {
            newArray[i] = this->arr[i];
        }
        delete[] this->arr;
        this->arr = newArray;
        this->capacity = newCap;
    }

public:
    static const int INITIAL_CAPACITY = 9;

    ArrayList() {
        this->arr = new T[INITIAL_CAPACITY];
        this->size = 0;
        this->capacity = INITIAL_CAPACITY;
    }

    ~ArrayList() {
        delete[] this->arr;
    }

    void addAtIndex(int index, const T& data) {
        if (index < 0 || index > this->size) throw runtime_error("bad index");
        if (this->size == this->capacity) regrow();

        // shift
        for (int i = this->size - 1; i >= index; i--) {
            this->arr[i + 1] = this->arr[i];
        }

        this->arr[index] = data;
        this->size++;
    }

    void addToFront(const T& data) { addAtIndex(0, data); }
    void addToBack(const T& data) { addAtIndex(this->size, data); }

    T removeAtIndex(int index) {
        if (index < 0 || index >= this->size) throw runtime_error("bad index");
        T removed = this->arr[index];

        for (int i = index; i < this->size - 1; i++) {
            this->arr[i] = this->arr[i + 1];
        }

        this->size--;
        return removed;
    }

    T removeFromFront() { return removeAtIndex(0); }
    T removeFromBack() { return removeAtIndex(this->size - 1); }

    T get(int index) {
        if (index < 0 || index >= this->size) throw runtime_error("bad index");
        return this->arr[index];
    }

    int getSize() { return this->size; }
};

int main() {
    ArrayList<string> arr;
    arr.addToBack("hello");
    arr.addToFront("first");
    arr.addToBack("world");

    cout << arr.get(1) << endl; // expect "hello"

    cout << arr.removeFromBack() << endl; // world
    cout << arr.removeFromFront() << endl; // first
    cout << arr.getSize() << endl; // 1

    return 0;
}
