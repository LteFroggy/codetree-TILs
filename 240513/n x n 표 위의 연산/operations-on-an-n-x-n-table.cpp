#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    무적 권 n, n까지 가야 한다
    근데 사이즈가 어차피 3 혹은 5라서
    "완 전 탐 색" 해도 될 것 같음
*/

typedef pair<int, int> point;
int N;
int MAX_VAL = 0;
int MIN_VAL = 100000007;

bool inboard_check(int y, int x) {
    return y < N && x < N;
}

void start_search(vector<vector<char>> board, int y, int x, int value, char operation) {
    // operation이 없다면, 이번엔 operation을 받을 차례이므로 operation을 받고 좌, 혹은 아래로 간다.
    if (operation == 'N') {
        // 아래로 가기
        if (inboard_check(y + 1, x)) {
            start_search(board, y + 1, x, value, board[y][x]);
        }
        // 우측으로 가기
        if (inboard_check(y, x + 1)) {
            start_search(board, y, x + 1, value, board[y][x]);
        }
    }

    // 숫자가 나올 차례이다. operation에 따라 value에 값을 추가한다.
    else {
        switch (operation) {
            case '+' :
                value += board[y][x] - '0';
                break;
            case '-' :
                value -= board[y][x] - '0';
                break;
            case 'x' :
                value *= board[y][x] - '0';
                break;
        }

        // 이게 마지막 수였다면, min, max 조건 확인하고 필요시 갱신하기
        if (y == N - 1 && x == N - 1) {
            if (value > MAX_VAL) {
                MAX_VAL = value;
            }
            if (value < MIN_VAL) {
                MIN_VAL = value;
            }
            return;
        }

        // 그게 아니라면, 아래 혹은 우측으로 보내주기
        else {
            // 아래로 가기
            if (inboard_check(y + 1, x)) {
                start_search(board, y + 1, x, value, 'N');
            }
            // 우측으로 가기
            if (inboard_check(y, x + 1)) {
                start_search(board, y, x + 1, value, 'N');
            }
        }
    }
}

int main() {
    cin >> N;

    vector<vector<char>> board(N, vector<char>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    // 탐색 시작 및 출력
    start_search(board, 0, 0, 0, '+');
    
    cout << MAX_VAL << " " << MIN_VAL << endl;
    return 0;
}