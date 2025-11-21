#include <iostream>
using namespace std;

class UnionFind{
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind(int n){
        this->parent.resize(n);
        this->rank.resize(n, 1);

        for(int i=0; i<n; i++){
            parent[i] = i;
        }
    }

    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int a, int b){
        int pa = find(a);
        int pb = find(b);

        if(pa == pb) return;

        if(rank[pa] < rank[pb]){
            parent[pa] = pb;
        }else if(rank[pa] > rank[pb]){
            parent[pb] = pa;
        }else{
            parent[pb] = pa;
            rank[pa]++;
        }
    }
};



int main(){
    return 0;
}