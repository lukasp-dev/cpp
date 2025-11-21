#include <iostream>
using namespace std;

unsigned char a = 17;
short b = -18;
int c = 2;
unsigned int d = 0;

bool isSorted(const vector<int>& seq){ // prone to the promotion errors
    for(int i=0; i<seq.size()-1; i++){
        if(seq[i] > seq[i+1]){
            return false;
        }
    }
    return true;
}

int main(){
    cout << (a + b) * c + d << endl; //4294967294 1st example of promotion

    return 0;
}