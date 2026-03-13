#include <iostream>

using namespace std;

void makePermutation(int n, int r, vector<vector<int>>& ret, vector<int>& vec, vector<bool>& visited){
    if(vec.size() == r){
        ret.push_back(vec);
    }

    for(int i=0; i<n; i++){
        if(visited[i]) continue;

        visited[i] = true;
        vec.push_back(i);
        makePermutation(n, r, ret, vec, visited); 
        vec.pop_back();
        visited[i] = false;
    }
}

int main(){
    int n = 3;
    int r = 3;
    vector<vector<int>> ret;
    vector<int> vec;
    vector<bool> visited(n, false);

    makePermutation(n, r, ret, vec, visited);

    return 0;
}