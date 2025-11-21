#include <iostream>
using namespace std;

int main(){
    int b = 0;
    if(b & 1 == 0){
        cout << "Hello World 1" << "\n"; //nothing is printed
    }

    if((b & 1) == 0){ 
        cout << "Hello World 2" << "\n"; //Hello World 2
    }

    return 0;
}