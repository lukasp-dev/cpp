#include <iostream>
using namespace std;

int N, M;
vector<vector<bool>> forbidden;

// 함수 선언만 (구현 없음)
int selectMenu(vector<int>& menu, int food);

// 구현은 네가 직접 할 함수
bool allSatisfied(const vector<int>& menu);

int main() {
    cin >> N >> M;

    forbidden.assign(N, vector<bool>(M, false));

    for (int f = 0; f < N; f++) {
        for (int d = 0; d < M; d++) {
            char c;
            cin >> c;  // 'O' or 'X'
            forbidden[f][d] = (c == 'X');
        }
    }

    vector<int> menu(M, 0);

    int result = selectMenu(menu, 0);

    cout << result << "\n";
    return 0;
}
