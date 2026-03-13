#include <vector>
using namespace std;

void makeCombination(int n , int r, vector<vector<int>>& ret, vector<int>& vec, int start){
    if(vec.size() == r){
        ret.push_back(vec);
        return;
    }

    for(int i = start; i < n; i++){
        vec.push_back(i);
        makeCombination(n, r, ret, vec, i+1);
        vec.pop_back();
    }
}

int main(){
    int n = 3, r=2;

    vector<vector<int>> ret;
    vector<int> vec;
    makeCombination(n, r, ret, vec, 0);

    return 0;
}