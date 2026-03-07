#include <iostream>
#include <memory> // need this to implement the smart pointer
using namespace std;

shared_ptr<int> getData(){
    shared_ptr<int> a = make_shared<int>(5);
    return a;
}

int* getDataPtr(){
    int* a = new int(5);
    return a;
}

unique_ptr<int> getDataUnique(){
    unique_ptr<int> a = make_unique<int>(6);
    return a;
}

int main(){ 
    shared_ptr<int> b = getData();
    auto c = b;
    cout << *b << "\n";
    cout << *c << "\n";
    cout << *b << "\n";

    cout << c.use_count() << "\n"; //2 -> how many are referencing

    int* d = getDataPtr();
    cout << *d << "\n";
    delete d;
    /**
     * If 'delete d;' is not called, the memory stays allocated in the Heap 
     * even after 'd' disappears from the Main Stack.
     * * 1. In a 24/7 Trading Engine, this causes a "Memory Leak."
     * 2. The Heap usage grows indefinitely (Memory Footprint increases).
     * 3. Eventually, the OS triggers an OOM (Out-of-Memory) crash, 
     * killing the entire process.
     */

    unique_ptr<int> e = getDataUnique();
    // unique_ptr f = e; can assign only one reference
    cout << *e << "\n";
    // but you can move the ownership to another ptr
    unique_ptr<int> f = move(e);
    // undefined behavior -> cout << *e << "\n";
    cout << *f << "\n";

    //weak ptr
    shared_ptr<int> sptr = make_shared<int>(10);
    weak_ptr<int> wptr = sptr;

    // ✅ The Recommended Approach (Thread-safe & Atomic)
    if(auto shared = wptr.lock()){ 
        // (1) Atomically checks for existence and increments the Reference Count.
        // (2) As long as 'shared' (a strong shared_ptr) exists in this scope, 
        // the memory cannot be deallocated even if other threads reset the original sptr.
        cout << *shared << "\n";
    } else {
        cout << "Object has already been deallocated" << "\n";
    }

    // ❌ The "Check-then-Act" Approach (Risk of Race Condition)
    if(!wptr.expired()){     
        // (1) Check: "Is the object still alive?"
        // <--- [CRITICAL WINDOW: Another thread could call sptr.reset() right here!]
        
        auto shared = wptr.lock(); // (2) Potential failure: object might have vanished by now.
        if(shared) {
            cout << *shared << "\n"; // (3) Risk of dereferencing a nullptr if not checked again.
        }
    } else {
        cout << "Object has already been deallocated" << "\n";
    }
    
    return 0;
}