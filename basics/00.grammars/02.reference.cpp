#include <iostream>

int main(){
    /**
    error: non-const lvalue reference to type 'int' 
    cannot bind to a temporary of type 'int'
     */
    // int &ref = 4;
    // std::cout << ref << std::endl;

    const int& ref = 4;
    std::cout << ref << std::endl;
    
    return 0;
}