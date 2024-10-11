#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
    100 x 100사이즈 격자 위에 N개의 블럭 위치가 주어진다.
    도형의 외곽 둘레 길이를 구해보자.
    인접한 블록은 이어지며, 블럭으로 둘러쌓인 빈 공간은 둘레가 아니다

    그럼 그냥 모든 빈 칸을 탐색하면서, 주변에 블록의 개수만큼이 블럭의 총 둘레가 된다.
    둘레만 탐색해야 하므로, 테두리만 돌면서 파악하자.

    BFS로 탐색할 것.
*/

// 어떤 칸이 보드판 내부인지 체크해준다.
inline bool inboard_check(int y, int x) {
    return y >= 0 && y < 100 && x >= 0 && x < 99;
}

void search(int y, int x, const vector<vector<int>> &board, vector<vector<bool>> &visited, int &answer);

int main() {
    int answer(0);
    int N;
    cin >> N;   

    // 보드에 0은 빈칸, 1은 블록이다.
    vector<vector<int>> board(100, vector<int>(100, 0));

    // 어떤 칸을 방문했는지 체크하기 위한 변수
    vector<vector<bool>> visited(101, vector<bool>(101, false));

    
    // 먼저 블럭 위치들을 입력받는다
    for (int i = 0; i < N; i++) {
        int y, x;
        cin >> y >> x;
        board[y-1][x-1] = 1;
    }

    // 왼쪽 테두리
    for (int y = 0; y < 100; y++) {
        int x = 0;
        search(y, x, board, visited, answer);
    }

    // 위쪽 테두리
    for (int x = 0; x < 100; x++) {
        int y = 0;
        search(y, x, board, visited, answer);
    }

    // 오른쪽 테두리
    for (int y = 0; y < 100; y++) {
        int x = 99;
        search(y, x, board, visited, answer);
    }

    // 아래쪽 테두리
    for (int x = 0; x < 100; x++) {
        int y = 99;
        search(y, x, board, visited, answer);
    }

    cout << answer << endl;
    return 0;
}

// 한 시작점에서부터의 탐색을 수행해주는 함수
void search(int y, int x, const vector<vector<int>> &board, vector<vector<bool>> &visited, int &answer) {
    // 상하좌우 탐색을 위한 값
    int dy[4] = {-1, 0, 1, 0};
    int dx[4] = {0, -1, 0, 1};

    // 만약, 테두리에 블럭이 있다면 그것 자체로 둘레가 된다.
    if (board[y][x] == 1) {
        // answer++;
        return;
    }

    else if (board[y][x] == 0 && !visited[y][x]) {
        // 체크를 위한 큐
        queue<pair<int, int>> que;
        que.push({y, x});
        visited[y][x] = true;

        // 상하좌우 인접한 칸을 모두 탐색한다.
        while (!que.empty()) {
            int y = que.front().first;
            int x = que.front().second;
            que.pop();

            for (int k = 0; k < 4; k++) {
                int y_ = y + dy[k];
                int x_ = x + dx[k];
                // 가보지 않은 빈 칸을 발견하면 이동해서 체크한다.
                if (inboard_check(y_, x_) && board[y_][x_] == 0 && !visited[y_][x_]) {
                    que.push({y_, x_});
                    visited[y_][x_] = true;
                }

                // 상하좌우에 블록이 있다면, 그건 둘레가 된다.
                else if (inboard_check(y_, x_) && board[y_][x_] == 1) {
                    answer++;
                }
            }
        }
        return;
    }
    
}