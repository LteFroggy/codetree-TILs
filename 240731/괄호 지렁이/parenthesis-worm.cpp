#include <iostream>
#include <vector>
using namespace std;

/*
    귀여운 지렁이가 괄호를 만든다
    커봤자 5x5사이즈라 그냥 다 봐도 된다.

    일단 괄호 있는 방향으로 다 가보고, 완성된 길이를 저장하면 된다.
*/
int answer(0);
int N;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, -1, 0, 1};

void findBrackets(vector<vector<bool>> &visited, const vector<vector<char>> &board, int y, int x, bool increasing, int count, int maxNum);
inline bool inboard_check(int y, int x, int N);

int main() {
    cin >> N;

    vector<vector<char>> board(N, vector<char>(N));
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    
    // 보드판 입력받기
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    // 탐색 시작을 위한 초기값 설정
    int y(0), x(0);
    visited[0][0] = true;

    // 처음부터 닫는 괄호 나오면 뭘 할 수가 없음. 0출력하고 종료
    if (board[0][0] == ')') {
        cout << 0 << endl;
        return 0;
    }

    // 아닌 경우 탐색 수행하기
    else {
        findBrackets(visited, board, 0, 0, true, 1, 1);
    }
    

    cout << answer << endl;
    return 0;
}

// 어떤 값이 보드판 내에 존재하는지 확인하기 위한 함수
inline bool inboard_check(int y, int x, int N) {
    return (y >= 0) && (y < N) && (x >= 0) && (x < N);
}

/*
    실제 탐색을 수행하는 함수
    visited : 방문 여부를 표현하는 2차원 벡터
    board : 보드판
    y, x : 현재 위치
    increasing : 지금 여는 괄호를 찾고 있는지, 닫는 괄호를 찾고 있는지
    count : 몇 개의 닫는 괄호를 더 찾아야 올바른 문자열이 될 수 있는지. 0이면 종료된다.
    maxNum : 이번 루프가 몇 개의 여는 괄호를 찾았는지를 저장한다.
*/
void findBrackets(vector<vector<bool>> &visited, const vector<vector<char>> &board, int y, int x, bool increasing, int count, int maxNum) {
    // 찾아야 할 bracket을 다 찾아서 올바른 문자열이 되었다면, 저장하고 종료한다.
    if (count == 0) {
        if (answer < maxNum * 2) {
            answer = maxNum * 2;
        }
        return;
    }

    // 아직 끝나지 않았다면, 가능한 모든 방향으로 지렁이를 보내본다.
    else {
        for (int k = 0; k < 4; k++) {
            int y_ = y + dy[k];
            int x_ = x + dx[k];
            
            // 보드판 내에 존재하며 방문해보지 않은 칸인 경우
            if (inboard_check(y_, x_, N) && !visited[y_][x_]) {
                // 여는 괄호를 봤다면, 여는 괄호를 더 찾는 상태인 경우에만 다음으로 보내준다
                if (board[y_][x_] == '(' && increasing) {
                    visited[y_][x_] = true;
                    findBrackets(visited, board, y_, x_, true, count + 1, count + 1);
                    visited[y_][x_] = false;
                }

                // 닫는 괄호라면, 이제 닫는 조건으로 다음으로 보내본다
                else {
                    visited[y_][x_] = true;
                    findBrackets(visited, board, y_, x_, false, count- 1, maxNum);
                    visited[y_][x_] = false;
                }
            }
        }
    }
}