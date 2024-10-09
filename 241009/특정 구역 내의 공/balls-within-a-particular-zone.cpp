#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
    평면 위에 직선이 주어지고, P개의 공의 위치도 있다.
    같은 영역 안에 있는 공 그룹들을 찾아보자.
    이동은 실수 단위로도 가능하니, 선이 겹친 것만 아니면 영역이 나눠지진 않는다.

    한 선이 다른 선을 두 번 만나면 영역이 생긴다.
    한번 만나는걸로 영역이 나뉘진 않음.

    한 점이 다른 점을 만나러 갈 수 있는지가 같은 영역인지의 여부가 된다.
    1. 일단 좌표를 압축한다. (일종의 보드판을 만든다)
    2. B점으로 가는 것이 가능한지를 찾아본다.(선을 어떤 벽이라고 가정하기)

    좌표압축이란? 좌표의 크고 작음만 중요할 때 사용하는 방법이다.
    예를 들어 1, 500, 1230, 40350가 있으면
    1 = 0, 500 = 1, 1230 = 2, 40350 = 3으로 저장하는 것
    이렇게 하면 장점은? 만약 1과 1230 사이에 값이 있는지 체크하고 싶을 경우, 2 ~ 1229를 하나하나 조회할 필요 없이 1의 값이 있는지만 조사하면 된다.
    그리고 이 문제에서는 어차피 사이에 빈 공간이 있으면 공이 지나갈 수 있는 것이기 때문에, 빈 공간의 체크를 위해 압축을 사용한다.
*/

struct line {
    line(int a, int b, int c, int d) : x_start(a), y_start(b), x_end(c), y_end(d) {};
    int x_start;
    int x_end;
    int y_start;
    int y_end;
};

void print_board(const vector<vector<int>> &board) {
    for (int i = board.size() - 1; i >= 0; i--) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << board[i][j] << " ";
        } cout << endl;
    }
}

inline bool inboard_check(int N, int M, int y, int x) {
    return y >= 0 && y < N && x >= 0 && x < M;
}

int main() {
    int answer = 0;
    // 모든 x, y좌표를 입력받는다. 그리고 이후 좌표압축을 수행할 것
    set<int> x_spots;
    set<int> y_spots;

    // 좌표압축의 결과를 저장할 unordered_map
    // 이 압축 결과를 바탕으로 줄 값들을 수정한다.
    unordered_map<int, int> x_compressed;
    unordered_map<int, int> y_compressed;

    vector<line> lines;
    vector<pair<int, int>> dots;

    int N, P;
    cin >> N >> P;

    // 선을 입력받아서 lines와 x_spots, y_spots 갱신하기
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int x_start, y_start, x_end, y_end;

        x_start = min(x1, x2);
        x_end = max(x1, x2);
        y_start = min(y1, y2);
        y_end = max(y1, y2);

        lines.push_back(line(x_start, y_start, x_end, y_end));

        x_spots.insert(x_start);
        x_spots.insert(x_end);
        y_spots.insert(y_start);
        y_spots.insert(y_end);
    }

    // 점의 좌표를 입력받아 dots와 x_spots, y_spots 갱신하기.
    for (int i = 0; i < P; i++) {
        int x, y;
        cin >> x >> y;
        dots.push_back({x, y});
        x_spots.insert(x);
        y_spots.insert(y);
    }
    /// 확인용 출력 1
    /*
    cout << "X Spots" << endl;
    for (auto v : x_spots) cout << v << " ";
    cout << endl;

    cout << "Y spots" << endl;
    for (auto v : y_spots) cout << v << " ";
    cout << endl;
    */

    // compressed 갱신하기
    int val = 0;
    for (auto v : x_spots) 
        x_compressed.insert({v, val++});
    
    val = 0;
    for (auto v : y_spots)
        y_compressed.insert({v, val++});

    // 갱신된 compressed값을 기반으로 점과 직선 값 갱신
    for (int i = 0; i < lines.size(); i++) {
        lines[i].x_start = x_compressed[lines[i].x_start];
        lines[i].x_end = x_compressed[lines[i].x_end];
        lines[i].y_start = y_compressed[lines[i].y_start];
        lines[i].y_end = y_compressed[lines[i].y_end];
    }
    
    for (int i = 0; i < dots.size(); i++) {
        dots[i].first = x_compressed[dots[i].first];
        dots[i].second = y_compressed[dots[i].second];
    }

    /// 확인용 출력 2
    /* 
    cout << "lines" << endl;
    for (auto v : lines) {
        cout << v.x_start << ", " << v.y_start << ", " << v.x_end << ", " << v.y_end << endl;
    }

    cout << "dots" << endl;
    for (auto v : dots) {
        cout << v.first << ", " << v.second << endl;
    }
    */

    // (x_spots * 2) * (y_spots * 2) 크기의 보드판을 만든다. *2인 이유는 사이사이 빈칸 표현을 위함
    vector<vector<int>> board(y_spots.size() * 2, vector<int>(x_spots.size() * 2, 0));

    // 보드판에 점을 적용한다
    for (int i = 0; i < dots.size(); i++) {
        int x = dots[i].first * 2;
        int y = dots[i].second * 2;
        board[y][x] = 7;
    }

    // 보드판에 직선(벽)을 적용한다.
    for (int i = 0; i < lines.size(); i++) {
        // 먼저 이게 가로선인지 세로선인지 확인해야 함.
        // x의 시작과 끝이 같다면, 가로선이다.
        if (lines[i].x_start == lines[i].x_end) {
            for (int j = lines[i].y_start * 2; j <= lines[i].y_end * 2; j++) {
                board[j][lines[i].x_start * 2] = 1;
            }
        }

        // 아니면 세로선이다.
        else {
            for (int j = lines[i].x_start * 2; j <= lines[i].x_end * 2; j++) {
                board[lines[i].y_start * 2][j] = 1;
            }
        }
    }
    

    // 이제 각 영역을 순회한다.
    // 순회용 que
    queue<pair<int, int>> que;
    // 방문 체크용 visited
    vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
    // 이동용 dx, dy;
    int dy[4] = {-1, 0, 1, 0};
    int dx[4] = {0, -1, 0, 1};

    N = board.size();
    int M = board[0].size();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // 벽이 아닌 칸을 찾으면, 순회를 시작한다.
            if (board[i][j] != 1 && !visited[i][j]) {
                que.push({i, j});
                visited[i][j] = true;

                // 순회마다 그 칸 내부의 점 개수를 저장할 변수
                int dot_count = 0;

                while (!que.empty()) {
                    int y = que.front().first;
                    int x = que.front().second;
                    que.pop();

                    if (board[y][x] == 7) {
                        dot_count++;
                    }

                    for (int k = 0; k < 4; k++) {
                        int y_ = y + dy[k];
                        int x_ = x + dx[k];
                        // 보드판 내부이며, 가본 적이 없고, 벽이 아니면 진행해본다.
                        if (inboard_check(N, M, y_, x_) && !visited[y_][x_] && board[y_][x_] != 1) {
                            que.push({y_, x_});
                            visited[y_][x_] = true;
                        }
                    }
                }

                answer = max(answer, dot_count);
            }
        }
    }

    /// 보드판 확인용 출력
    /// print_board(board);

    cout << answer << endl;

    return 0;
}