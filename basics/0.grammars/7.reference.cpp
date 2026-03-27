#include <iostream>
#include <vector>

using namespace std;

void work(int &x){
    x++;
}

void work(vector<int>& vec){
    vec[0]++;
}

int main(){
    vector<int> data = {10, 10, 30, 50, 40, 20, 430, 40, 2};

    cout << data[0] << "\n"; //10
    work(data);
    cout << data[0] << "\n"; //11
    
    int a = 10;
    int& b = a; // This is how you create the alias
    int c = 100;

    cout << a << " " << b << "\n"; //10 10
    b = c;
    cout << &a << " " << &b << "\n"; //0x16b71e698 0x16b71e698
    work(a); 
    cout << a << " " << b << "\n"; // 101 101

    return 0;
}