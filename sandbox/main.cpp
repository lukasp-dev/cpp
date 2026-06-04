#include <bits/stdc++.h>
using namespace std;



int go(const vector<int>& rods, int depth, int limit){

}

int main(){
    int N; cin >> N;
    vector<int> rods;
    int rod;
    for(int i=0; i<N; ++i){
        cin >> rod;
        rods.push_back(rod);
    }

    return go(rods, 0, rods.size()-1);

    return 0;
}