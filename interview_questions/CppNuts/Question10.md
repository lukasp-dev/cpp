# Union in C++

Just like a `struct`, a union is a user-defined data type. However, the key difference lies in how they manage memory:

- Shared Memory: In a union, all members share the same memory location. Size: The total size of the union is determined by its largest member.
- One a a time: You can only store a value in one member at any given time. Writing to a new member overwrites the previous one.
- Often used to achieve polymorphism in C.
    ```c
    enum shapeType { CIRCLE, RECTANGLE };

    struct Shape {
        enum ShapeType type;
        union {
            float radius;           // Used if type CIRCLE
            struct { float w, h; }; // Used if type is RECTANGLE
        } data;
    };
    ```

### Potential Ussage?
1) When we need only one value out of many that time we will use it. (Example: Square Class)
    ```cpp
    #include <iostream>
    using namespace std;

    union Square {
        int width;
        int height;
    };

    int getArea(int width, int height) {
        return width*height;
    }

    int main() {
        Square sqr;
        sqr.width = 10;
        cout << getArea(sqr.width, sqr.height) << endl;
    }
    ```

2) Get the actual data in parts (Example: int value, char bytes[4])
    ```cpp
    #include <iostream>
    using namespace std;

    union myUnion {
        char bytes[4];
        unsigned int value;  
    };

    int main() {
        myUnion un;
        un.value = 0;

        un.value = 257;

        cout << (int)un.bytes[0] << endl; //1
        cout << (int)un.bytes[1] << endl; //1
        cout << (int)un.bytes[2] << endl; //0
        cout << (int)un.bytes[3] << endl; //0

        return 0;
    }
    ```