#include <iostream>
#include <vector>

using namespace std;

/*
    숫자를 네모낳게 찍으면 된다. 사이즈 보고 재귀로 찍어보자
*/

void make_square(vector<vector<int>>& vec, int size, int start_i, int start_j, int start_val) {
    // 왼쪽으로 가기
    for (int j = 0; j < size; j++) {
        vec[start_i][start_j + j] = start_val++;
    }

    // 아래로 내려가기
    for (int i = 1; i < size; i++) {
        vec[i + start_i][size - 1 + start_j] = start_val++;
    }

    // 오른쪽으로 가기
    for (int j = size - 2; j >= 0; j--) {
        vec[size - 1 + start_i][j + start_j] = start_val++;
    }

    // 위로 올라오기
    for (int i = size - 2; i > 0; i--) {
        vec[i + start_i][start_j] = start_val++;
    }

    // 사이즈가 남는다면 재귀로 반복
    if (size > 2) {
        make_square(vec, size - 2, start_i + 1, start_j + 1, start_val);
    }
}


int main() {
    int N;
    cin >> N;
    vector<vector<int>> square(N, vector<int>(N, 0));

    make_square(square, N, 0, 0, 1);

    for (auto v : square) {
        for (auto v_ : v) {
            cout << v_ << " ";
        }
        cout << endl;
    }
    return 0;
}