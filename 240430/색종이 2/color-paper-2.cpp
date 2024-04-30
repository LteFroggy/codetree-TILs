#include <iostream>
#include <vector>
#include <stack>

/* 
    vector 만들고
    탐색 하기
    bfs로
*/

using namespace std;

bool inboard_check(int y, int x) {
    return y >= 0 && y < 511 && x >= 0 && x < 511;
}

int main() {
    int N;
    cin >> N;

    int dy[] = {-1, 0, 1, 0};
    int dx[] = {0, -1, 0, 1};

    vector<vector<bool>> board(511, vector<bool>(511, false));
    vector<vector<bool>> visited(511, vector<bool>(511, false));
    for (int i = 0; i < N; i++) {
        int y, x;
        cin >> y >> x;

        for (int y_ = 0; y_ < 10; y_++) {
            for (int x_ = 0; x_ < 10; x_++) {
                board[y + y_][x + x_] = true;
            }
        }
    }
    
    
    int answer = 0;
    // 보드 탐색
    // 매 true인 칸마다 false인 옆 칸의 개수를 세어야 한다.
    for (int i = 0; i < 511; i++) {
        for (int j = 0; j < 511; j++) {
            if (board[i][j]) {
                for (int k = 0; k < 4; k++) {
                    int y = i + dy[k];
                    int x = j + dx[k];

                    if (!inboard_check(y, x)) continue;
                    if (!board[y][x]) answer++;
                }
            }
        }
    }

    cout << answer << endl;
    return 0;
}