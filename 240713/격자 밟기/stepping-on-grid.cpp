#include <iostream>
#include <vector>

using namespace std;

/*
    5 x 5 사이즈의 정사각형 땅이 있다 (1,1) ~ (5,5)

    A는 1,1에, B는 5,5에 있음
    둘은 한 칸씩 가로 혹은 세로로 이동되며, 둘 중에 한 명이라도 밟았던 땅에는 아무도 가지 않는다.
    이 정사각형 땅에는 K개의 이동 불가능한 공간이 있어, 둘 다 들어갈 수 없다.
    
    A, B가 움직이면서 모든 이동 가능한 칸을 전부 방문하고 최종적으로 같은 칸을 밟게 되는 서로 다른 가지수를 구하자.

    이동 도중에 같은 칸을 밟는 것은 안 된다

    모든 경우를 탐색해보아야 할 듯 하다.
    최대 시간복잡도를 생각해보자
    각자 A 위치가 상하좌우 4가지, B 위치가 상하좌우 4가지로 한 경우당 16개의 경로가 생길 수 있다.
    모두 다른 칸을 밟는다고 했을 때 최대 11번의 이동이 발생할 수 있다.
    따라서 총 경우의 수는 11 x 16가지이다. 문제 없음

    /// 문제 1
    A와 B를 가능한 위치로 계속 이동시켜가며 문제 조건에 부합하는 경우 찾기
*/

// 답안 출력용 전역변수. 함수 내에서 값을 수정할 것이므로 전역변수로 선언하였다.
int sAnswer(0);

// 상하좌우 이동을 담당할 array
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, -1, 0, 1};

// y, x좌표가 보드 안쪽인지 확인한다.
inline bool inboard_check(int y, int x) {
    return (y > 0 && y <= 5 && x > 0 && x <= 5);
}

/*
    상하좌우 이동을 수행하는 함수이다.
    aLoc : A의 현재 위치
    bLoc : B의 현재 위치
    visited : 방문 가능, 불가능한 위치를 표현한 2차원 벡터
    left_
*/
void moveAB(pair<int, int> aLoc, pair<int, int> bLoc, vector<vector<bool>>& visited, int left_squares) {
    // 문제가 말한 조건(남은 칸이 0칸이며 동일한 위치에 도달했을 경우)에 해당하면, sAnswer를 1 더한다
    if (left_squares == 0 && aLoc.first == bLoc.first && aLoc.second == bLoc.second) {
        sAnswer++;
        return;
    }

    // 아직 조건에 도달하지 못했다면, a와 b를 모두 이동시켜야 한다.
    // 이동 방법은, A가 이동 가능한 자리를 모두 찾고, B가 이동 가능한 자리를 모두 찾은 후에 하나씩 보내줄 것이다(재귀)
    vector<pair<int, int>> A_possible_locs;
    vector<pair<int, int>> B_possible_locs;
    int y_a = aLoc.first;
    int x_a = aLoc.second;
    // 먼저 A 이동 가능한 자리 체크하기.
    for (int k = 0; k < 4; k++) {
        int y_a_new = y_a + dy[k];
        int x_a_new = x_a + dx[k];

        // 이동할 자리가 보드 안쪽이며, 가본 적 없는 곳이라면 A가 이동 가능하다.
        // 따라서 possible_locs에 추가한다.
        if (inboard_check(y_a_new, x_a_new) && !visited[y_a_new][x_a_new]) 
            A_possible_locs.push_back({y_a_new, x_a_new});
    }

    int y_b = bLoc.first;
    int x_b = bLoc.second;
    // 다음으로 B 이동 가능한 자리 체크하기
    for (int k = 0; k < 4; k++) {
        int y_b_new = y_b + dy[k];
        int x_b_new = x_b + dx[k];

        // 이동할 자리가 보드 안쪽이며, 가본 적 없는 곳이라면 B가 이동 가능하다.
        // 따라서 possible_locs에 추가한다.
        if (inboard_check(y_b_new, x_b_new) && !visited[y_b_new][x_b_new]) 
            B_possible_locs.push_back({y_b_new, x_b_new});
    }

     // A와 B가 이동 가능한 모든 위치로 보내준다.
    for (const auto& a_next : A_possible_locs) {
        for (const auto& b_next : B_possible_locs) {
            if (a_next == b_next) {
                if (left_squares == 1) {
                    visited[a_next.first][a_next.second] = true;
                    moveAB(a_next, b_next, visited, left_squares - 1);
                    visited[a_next.first][a_next.second] = false;
                }
            } else {
                visited[a_next.first][a_next.second] = true;
                visited[b_next.first][b_next.second] = true;
                moveAB(a_next, b_next, visited, left_squares - 2);
                visited[a_next.first][a_next.second] = false;
                visited[b_next.first][b_next.second] = false;
            }
        }
    }
}  

int main() {
    // visited를 만들고 A, B의 시작 지점을 방문했다고 처리해준다.
    vector<vector<bool>> visited(6, vector<bool>(6, false));
    visited[1][1] = true;
    visited[5][5] = true;

    // 남은 칸 수 저장용 변수
    int left_squares(23);

    int K;
    cin >> K;
    
    // 남은 칸 수 조절하기
    left_squares -= K;

    // 방문 불가능한 칸 체크하기
    for (int i = 0; i < K; i++) {
        int y, x;
        cin >> y >> x;
        visited[y][x] = true;
    }
    
    // 문제 풀이하기
    moveAB({1, 1}, {5, 5}, visited, left_squares);
    
    cout << sAnswer << endl;
    return 0;
}