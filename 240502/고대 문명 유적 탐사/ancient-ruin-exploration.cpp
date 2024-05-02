#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

/*
    고대 문명 유적 발견하게 되었다! 5x5사이즈이다.

    각 칸에는 1 ~ 7의 유적 조각이 있음.

    1. 탐사는 3x3격자를 골라 맘대로 회전시킬 수 있다. 대신, 선택하면 꼭 돌려야 함(돌리지 않을 수는 없음).
    회전 방법은 유물 1차 획득 가치를 최대화하며, 그런 방법이 여러 가지라면 회전 각도가 가장 작은 방법을 선택해야 함.
    그런 방법도 여러개면, 회전 중심 좌표의 열이 가장 작고, 그 다음으로 행이 가장 작은 구간을 선택해 돌린다.

    2. 1차 획득이란?
    상하좌우로 인접한 같은 종류 유물 조각은 연결되어 있고, 조각이 3개 이상 연결되었다면 모여서 유물이 되어 사라진다.
    가치는 모인 조각의 개수에 비례한다.

    3. 새로 채우기
    유물이 연결되어 사라지면, 벽면에 쓰인 숫자 순서대로 큰 열부터 작은 열로, 작은 행부터 큰 행으로 채워진다.

    이렇게 3가지 행동을 하면, 한 턴이 지나간다. K회의 턴을 진행하고, 턴별로 얻은 점수를 출력하자.


    9개의 3x3사이즈가 있고, 이걸 3개씩 돌릴 수 있으므로 매 턴 27가지의 경우를 체크해야 한다. 27 x 25이므로 복잡도는 문제 없음
    각 90', 180', 270' 돌리는 방법은? 별도 함수를 사용하자.
*/

vector<vector<int>> rotate_90(vector<vector<int>> board, int center_y, int center_x);
vector<vector<int>> rotate_180(vector<vector<int>> board, int center_y, int center_x);
vector<vector<int>> rotate_270(vector<vector<int>> board, int center_y, int center_x);
vector<vector<int>> rotate_tool(vector<vector<int>> board, int center_y, int center_x, int angle);
void print_board(vector<vector<int>> board);
pair<int, vector<vector<int>>> get_score(vector<vector<int>> board);
bool inboard_check(int y, int x);

int main() {
    int K, M;
    cin >> K >> M;
    vector<vector<int>> board(5, vector<int>(5));
    queue<int> new_numbers;

    // 보드 입력받기
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> board[i][j];
        }
    }

    // 새로 넣을 값들 입력받기
    for (int i = 0; i < M; i++) {
        int tmp;
        cin >> tmp;
        new_numbers.push(tmp);
    }

    int turn = 0;
    int total_score = 0;
    vector<vector<int>> board_afterRotation;
    // 매 턴마다 어디를 돌릴지 정하고, 값을 없앤 후에 새 값으로 채워야 한다.
    while (++turn <= K) {
        // 돌릴 수 있는 후보지는 총 9군데이고, 세 번 돌려봐야 한다.
        // 가장 점수가 높은 것이 우선, 모두 같다면 회전 각도가 적은 순으로, 그것도 같다면 열이 가장 작은것, 그것도 같다면 행이 가장 작은 것
        int max_score = 0;
        int min_rotation = -1;
        for (int i = 1; i < 4; i++) {
            for (int j = 1; j < 4; j++) {
                for (int k = 0; k < 3; k++) {
                    vector<vector<int>> tmp = rotate_tool(board, j, i, k);
                    pair<int, vector<vector<int>>> score_board = get_score(tmp);

                    if (max_score < score_board.first) {
                        max_score = score_board.first;
                        min_rotation = k;
                        board_afterRotation = score_board.second;
                        // cout << i << "," << j << "를 중심으로 " << k << "돌리면 " << score_board.first << "점 획득 가능." << endl;
                        // cout << "이 때의 보드판" << endl;
                        // print_board(score_board.second);
                    }

                    else if (max_score == score_board.first && min_rotation > k) {
                        min_rotation = k;
                        board_afterRotation = score_board.second;
                        // cout << i << "," << j << "를 중심으로 " << k << "돌리면 " << score_board.first << "점 획득 가능." << endl;
                        // cout << "이 때의 보드판" << endl;
                        // print_board(score_board.second);
                    }
                }
            }
        }

        if (max_score == 0) break;

        // cout << "이번 턴에 돌리고 삭제한 보드 상태" << endl;
        // print_board(board_afterRotation);

        total_score += max_score;
        pair<int, vector<vector<int>>> score_board;
        do {
            // 보드 다시 채우기
            for (int i = 0; i < 5; i++) {
                for (int j = 4; j >= 0; j--) {
                    if (board_afterRotation[j][i] == 0) {
                        board_afterRotation[j][i] = new_numbers.front();
                        new_numbers.pop();
                    }
                }
            }

            // cout << "다시 채워진 보드 상태" << endl;
            // print_board(board_afterRotation);
            
            // 연쇄 획득하기
            score_board = get_score(board_afterRotation);
            board_afterRotation = score_board.second;
            // cout << "연쇄 획득 점수는 " << score_board.first << endl;
            max_score += score_board.first;

            // cout << "연쇄 획득 후의 보드 상태" << endl;
            // print_board(board_afterRotation);
        } while (score_board.first != 0);
        // 이제 보드 채우고 연쇄 획득하기

        // 보드판 갱신하기
        board = board_afterRotation;
        cout << max_score << " ";
    }
    return 0;
}



vector<vector<int>> rotate_90(vector<vector<int>> board, int center_y, int center_x) {
    // 중심지를 기준으로 90' 회전시킬 것.
    vector<vector<int>> new_board = board;
    int y = center_y - 1;
    int x = center_x - 1;

    // 위쪽 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y][x + k] = board[y + 2 - k][x];
    }

    // 오른쪽 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y + k][x + 2] = board[y][x + k];
    }

    // 아래 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y + 2][x + k] = board[y + 2 - k][x + 2];
    }

    // 왼쪽 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y + k][x] = board[y + 2][x + k];
    }
    return new_board;
}


vector<vector<int>> rotate_180(vector<vector<int>> board, int center_y, int center_x) {
    // 중심지를 기준으로 180' 회전시킬 것.
    vector<vector<int>> new_board = board;
    int y = center_y - 1;
    int x = center_x - 1;

    // 위쪽 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y][x + k] = board[y + 2][x + 2 - k];
    }

    // 오른쪽 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y + k][x + 2] = board[y + 2 - k][x];
    }

    // 아래 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y + 2][x + k] = board[y][x + 2 - k];
    }

    // 왼쪽 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y + k][x] = board[y + 2 - k][x + 2];
    }

    return new_board;
}


vector<vector<int>> rotate_270(vector<vector<int>> board, int center_y, int center_x) {
    // 중심지를 기준으로 270' 회전시킬 것.
    vector<vector<int>> new_board = board;
    int y = center_y - 1;
    int x = center_x - 1;

    // 위쪽 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y][x + k] = board[y + k][x + 2];
    }

    // 오른쪽 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y + k][x + 2] = board[y + 2][x + 2 - k];
    }

    // 아래 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y + 2][x + k] = board[y + k][x];
    }

    // 왼쪽 값 수정하기
    for (int k = 0; k < 3; k++) {
        new_board[y + k][x] = board[y][x + 2 - k];
    }
    return new_board;
}

// 로테이션 세 함수를 하나 안에서 처리해주는 함수
vector<vector<int>> rotate_tool(vector<vector<int>> board, int center_y, int center_x, int angle) {
    switch(angle) {
        case 0 :
            return rotate_90(board, center_y, center_x);
            break;
        case 1 :
            return rotate_180(board, center_y, center_x);
            break;
        case 2 :
            return rotate_270(board, center_y, center_x);
            break;
    }
}

// 이번 보드에서 얻어지는 1차 탐사 값을 계산해주는 함수
pair<int, vector<vector<int>>> get_score(vector<vector<int>> board) {
    int dy[] = {-1, 0, 1, 0};
    int dx[] = {0, -1, 0, 1};

    vector<vector<bool>> visited(5, vector<bool>(5, false));

    int score = 0;
    queue<pair<int, int>> search_queue;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // 이미 봤던 칸이면 또 볼 필요 없음
            if (visited[i][j]) continue;
            
            // 보지 않았던 칸이면, 이 칸이 점수를 만들어낼 수 있는 칸인지 탐색 진행한다.
            search_queue.push(make_pair(i, j));
            visited[i][j] = true;

            // 현재 자리의 값(이어져야 하는 값)
            int value = board[i][j];
            // 이어진 갯수
            int connected_count = 1;
            // 이어진 위치들(나중에 0으로 바꾸는 용도)
            vector<pair<int, int>> connected_points;
            connected_points.push_back(make_pair(i, j));
    
            while (!search_queue.empty()) {
                int y = search_queue.front().first;
                int x = search_queue.front().second;
                search_queue.pop();

                for (int k = 0; k < 4; k++) {
                    int y_ = y + dy[k];
                    int x_ = x + dx[k];

                    if (!inboard_check(y_, x_) || visited[y_][x_]) continue;
                    if (board[y_][x_] == value) {
                        connected_count++;
                        search_queue.push(make_pair(y_, x_));
                        visited[y_][x_] = true;
                        connected_points.push_back(make_pair(y_, x_));
                    }
                }
            }

            // 3개 이상이 연결되었다면, 점수에 그 값 더해주고 보드판 상에서 값 0으로 바꿔주기
            if (connected_count >= 3) {
                score += connected_count;
                for (auto v : connected_points) {
                    board[v.first][v.second] = 0;
                }
            }
        }
    }

    return make_pair(score, board);
}

bool inboard_check(int y, int x) {
    return y >= 0 && y < 5 && x >= 0 && x < 5;
}

void print_board(vector<vector<int>> board) {
    for (auto v_ : board) {
        for (auto v : v_) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;
}