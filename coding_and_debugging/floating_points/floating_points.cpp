#include <iostream>
using namespace std;

bool absoluteEqual(double a, double b){
    return fabs(a-b) < 1e-10;
}

bool relativeEqual(double a, double b){
    return fabs(a - b) <= 1e-8*max(fabs(a), fabs(b));
}

//using both
bool doubleEqual(double a, double b){
    double diff = fabs(a - b);
    if(diff < 1e-10) return true;
    return diff <= 1e-8 * max(fabs(a), fabs(b));
}

int countObvious(int n){
    int same = 0;
    for(int x = 1; x <= n; ++x){
        double y = 1.0 / x;
        if(y * x == 1.0)
            ++same;
    }
    return same;
}


int main(){
    cout << countObvious(1000) << "\n"; // 918 이 나와버린다.
    return 0;
}