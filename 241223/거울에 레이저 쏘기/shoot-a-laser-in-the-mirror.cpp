#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    N x M사이즈 크기의 격자 안에 거울이 하나씩 있다.
    거울은 / 혹은 \의 형태를 띄고있다. 격자 밖 2N + 2M개의 위치 중 적절한 위치에서 레이저를 쐈을 때, 거울에 튕기는 횟수가 최대가 되도록 하자

    최대 1000 x 1000칸
    그럼 1,000,000칸
    시도할 수 있는 위치는 총 4000개

    4000 x 1,000,000?????
    
    /면 아래 -> 오른쪽, 위 -> 왼쪽으로 변환된다.
    \면 아래 -> 왼쪽, 위 -> 오른쪽으로 변환된다.

    어차피 거울은 칸마다 있으므로, 칸마다 어떻게 반사되는지 확인하자.
*/

inline bool inboard_check(int y, int x, int N, int M) {
    return y >= 0 && y < N && x >= 0 && x < M;
}

// 거울 튕김을 통해 몇 번 튀겼는지 알려주는 함수
int reflect_result(const vector<vector<char>> &board, int y, int x, int direction) {
    int bound = 0;
    // 각각 상하좌우를 의미한다
    int dy[4] = {-1, 1, 0, 0};
    int dx[4] = {0, 0, -1, 1};
    while (inboard_check(y, x, board.size(), board[0].size())) {
        bound++;

        // 거울이 /모양인 경우,
        if (board[y][x] == '/') {
            // 위와 왼쪽은 서로 교차된다
            if (direction == 0) direction = 2;
            else if (direction == 2) direction = 0;
            // 오른쪽과 아래도 교체된다
            else if (direction == 1) direction = 3;
            else if (direction == 3) direction = 1;
        }

        // 거울이 \모양인 경우
        else {
            // 위와 오른쪽이 교차된다
            if (direction == 0) direction = 3;
            else if (direction == 3) direction = 0;
            // 아래와 왼쪽도 교차된다
            else if (direction == 1) direction = 2;
            else if (direction == 2) direction = 1;
        }

        // 그리고, 그에 맞게 한칸 진행된다
        y += dy[direction];
        x += dx[direction];

        // 그 다음엔, 튀긴 방향과 들어온 방향이 바뀐다.
        if (direction == 0) direction = 1;
        else if (direction == 1) direction = 0;
        else if (direction == 2) direction = 3;
        else if (direction == 3) direction = 2;
    }

    return bound;
}

int main() {
    int N, M;
    cin >> N >> M;
    int answer = 0;

    // 각 칸별로 시작 여부 파악
    vector<vector<bool>> width_start(2, vector<bool>(N, false));
    vector<vector<bool>> height_start(2, vector<bool>(M, false));

    vector<vector<char>> board(N, vector<char>(M));

    // 보드판 입력받기
    for (int i = 0; i < N; i++) {
        string tmp;
        cin >> tmp;
        for(int j = 0; j < M; j++) {
            board[i][j] = tmp[j];
        }
    }

    // 세로 위, 아래에서 쏘기
    for (int i = 0; i < M; i++) {
        answer = max(answer, reflect_result(board, 0, i, 0));
        answer = max(answer, reflect_result(board, N-1, i, 1));
        
        /*
        if (answer < reflect_result(board, 0, i, 0)) {
            answer = reflect_result(board, 0, i, 0);
            cout << i << " 위에서 쐈을 때 " << answer << "로 갱신" << endl;
        }

        if (answer < reflect_result(board, N-1, i, 1)) {
            answer = reflect_result(board, N-1, i, 1);
            cout << i << " 아래에서 쐈을 때 " << answer << "로 갱신" << endl;
        }
        */
    }

    // 좌, 우에서 쏘기
    for (int i = 0; i < N; i++) {
        answer = max(answer, reflect_result(board, i, 0, 2));
        answer = max(answer, reflect_result(board, i, M-1, 3));

        /*
        if (answer < reflect_result(board, i, 0, 2)) {
            answer = reflect_result(board, i, 0, 2);
            cout << i << " 왼쪽에서 쐈을 때 " << answer << "로 갱신" << endl;
        }

        if (answer < reflect_result(board, i, M-1, 3)) {
            answer = reflect_result(board, i, M-1, 3);
            cout << i << " 오른쪽에서 쐈을 때 " << answer << "로 갱신" << endl;
        }
        */
    }

    // 제일 많이 튀긴 결과 출력
    cout << answer << endl;
    return 0;
}