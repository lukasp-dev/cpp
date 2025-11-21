#include <iostream>
#include <numeric>
using namespace std;

int getLCM(int a, int b){
    return (a*b)/gcd(a, b);
}

int main(){
    cout << getLCM(50000, 100000) << "\n";
    
    return 0;
}