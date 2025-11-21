#include <iostream>
#include <vector>
#define FOR(i, n) for(int i=0;i<(n);i++)
using namespace std;

bool hasDuplicate(const vector<int>& arr){
    FOR(i, arr.size())
        FOR(j, i)
            if(arr[i] == arr[j])
                return true;
    return false;
}

int main(){
    vector<int> arr = {-1, -1, 2, 3, 4, 5};
    cout << hasDuplicate(arr) << "\n";
}