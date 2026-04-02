# Dynamic Casting
**Syntax:** `dynamic_cast < new_type > (expression)`
1) `dynamic_cast` is used at run time to find our correct down-cast.
    - need at least 1 `virtual` function in Base class.
    - If the cast is successful, `dynamic_cast` returns a value of `new_type`.
    - if the cast fails and `new_type` is a pointer type, it returns a null pointer of that type.
    - If the cast fails and `new_type` is a reference type, it throws an exception that matches a handler of type `std::bad_cast`.

    ```cpp
    #include <iostream>
    #include <exception>
    using namespace std;

    class Base {
        virtual void print() {cout << "Base" << endl;}
    };

    class Derived1: public Base {
        void print() { cout << "Derived 1" << endl;}
    };

    class Derived2: public Base {
        void print() { cout << "Derived 2" << endl;}
    };

    int main() {
        Derived1 d1;
        
        Base *bp = dynamic_cast<Base*>(&d1);
        /*
        Downcasting / Side-casting (The "Heavy" Operation)
        
        MECHANICS:
        Since 1Base1 is polymorphic (has at least one virtual function), the object 'd1'
        contains a hidden pointer called 'vptr' (Virtual Table Pointer).
        This cptr points to the VTable which contains RTTI (Runtime Type Information).

        PROCESS OF dynamic_cast<Derived2*>(bp)
        1. Runtime Check: The CPU follows bp -> vptr -> VTable -> type_info.
        2. Hierarchy  Traversal: The RTTI engine checks if 'Derived1' (the actual type) is a 'Derived2' or inherits it.
        3. Failure Handling: Since Derived1 and Derived2 are distinct branches, the check fails. For pointers, it returns 'nullptr'.
        */
        Derived2 *dp2 = dynamic_cast<Derived2*>(bp);
        if(dp2 == nullptr){
            cout << "null" << "\n"; // null
        }else {
            cout << "not null" << "\n";
        }

        try{
            Derived2 &r2 = dynamic_cast<Derived2&>(d1);
        }catch(std::exception &e){
            cout << e.what() << "\n";
        }
        return 0;
    }
    ```

2) Summary
    - work only on polymorphic base class (at least one virtual function in base class) because it uses this informnation to decide about wrong down-cast.
    - It is used for up-cast (D->B) and down-cast (B->D), but it is mainly used for correct downcast.
    - Using this cast has run time overhead, because it checks object types at run time using RTTI (Run Time Type Information).
    - If we are sure that we will never cast to wrong object then we hould always avoid this cast and use `static_cast`. 