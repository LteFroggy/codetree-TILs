#include <iostream>
#include <vector>
using namespace std;

/*
    N, M, K가 주어지면 그것을 가로 세로로 K배 늘려 출력하자.
    예를 들어 0,0값을 받으면
    0 0
    0 1
    1 0
    1 1에 적용해야 한다

    0 1값은
    0 2
    0 3
    1 2
    1 3 에 적용되어야 한다.

    1 0 값은
    2 0
    2 1
    3 0
    3 1에 적용
*/

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    // 원본값 받기
    vector<vector<char>> board(N * K, vector<char>(M * K));

    // 원본 값을 받으면서 가로, 세로로 K배 한다.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // 일단 값을 받는다
            char input;
            cin >> input;

            int y_start = i * K;
            int x_start = j * K;
            for (int y_ = 0; y_ < K; y_++) {
                for (int x_ = 0; x_ < K; x_++) {
                    board[y_start + y_][x_start + x_] = input;
                }
            }
        }
    }

    // 출력한다
    for (auto v_ : board) {
        for (auto v : v_) cout << v;
        cout << endl;
    }
    return 0;
}