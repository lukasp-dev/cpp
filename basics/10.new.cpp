#include <iostream>
using namespace std;

class User{
public:
    string name;
};

int main(){
    int *x = new int(5);
    cout << "The pointer " << x << " points to " << *x << endl; // The pointer 0x100c75d40 points to 5
    delete x;

    User *u = new User();
    u->name = "Jewook Park";
    cout << u->name << "\n"; // Jewook Park
    delete u;

    return 0;
}