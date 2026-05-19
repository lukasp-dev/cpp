#include <iostream>

using namespace std;

void change(int *x){
    *x = 10;
}

//method overloading
void change(int &x){
    x = 20;
}

int main(){
    int x = 5;
    change(&x);
    
    cout << x << "\n"; //10 

    change(x);

    cout << x << "\n"; //20

    return 0;
}