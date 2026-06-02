#include <iostream>
#include <string>
int main(){
    int a = 100;
    int b = 5;

    int & reference_a = a;
    reference_a = b;

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "reference_a: " << reference_a << std::endl;
    
    return 0;
}
