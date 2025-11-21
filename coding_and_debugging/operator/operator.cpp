#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class IntegerSet {
public:
    vector<int> data;

    IntegerSet() = default;
    IntegerSet(initializer_list<int> init) : data(init) {
        sort(data.begin(), data.end());
        data.erase(unique(data.begin(), data.end()), data.end());
    }

    size_t size() const { return data.size(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }

    friend ostream& operator<<(ostream& os, const IntegerSet& s) {
        os << "{ ";
        for (int x : s.data) os << x << " ";
        os << "}";
        return os;
    }
};

bool isProperSubset(const IntegerSet& a, const IntegerSet& b);

bool operator<(const IntegerSet& a, const IntegerSet& b){
    if(isProperSubset(a, b)) return true;
    if(isProperSubset(b, a)) return false;
    if(a.size() != b.size()) return a.size() < b.size();
    return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

bool isProperSubset(const IntegerSet& a, const IntegerSet& b){
    if(a.size() >= b.size()) return false;
    return includes(b.begin(), b.end(), a.begin(), a.end());
}

int main() {
    IntegerSet A = {1, 2};
    IntegerSet B = {1, 2, 3};
    IntegerSet C = {2, 3};
    IntegerSet D = {1, 2};

    cout << (A < B) << "\n";
    cout << (B < A) << "\n";
    cout << (A < C) << "\n";
    cout << (A < D) << "\n";
    cout << (D < A) << "\n";

    return 0;
}
