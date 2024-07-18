#include <iostream>
#include <vector>
using namespace std;

/*
    N개의 점이 주어지면, 원점에서 출발해서 모든 점을 단 한번씩만 방문하고 원점으로 돌아오려 한다.
    이건 턴별로 움직이는 것이 아니다. 어쩐 점에서 상하좌우 중 한쪽으로 쭉 이동만 가능하다는 것 같음.
    
    이동 도중 어떤 점을 만나도 방문하지 않고 스쳐지나갈 수 있음.

    이동 방법을 시뮬레이션해서 재귀로 구성하자
    
    재귀 함수는 아래와 매개변수를 가지게 될 것이다.
        vector<int> visited : 목표 포인트들의 방문 여부 (복사해서 사용하면 시간이 늘어나므로 call by reference)
        int y_loc, x_loc : 현재 점의 위치
        vector<pair<int, int> points : 방문해야 할 포인트들의 좌표, (복사 방지를 위한 call by reference와 수정 방지를 위한 const)
        int left_points : 방문해야 할 포인트의 남은 개수. 종료 조건 체크에 쓰인다.
        char direction : 포인트를 만나면 방향을 바꿔야 하므로, 이전에 왔던 방향을 체크하기 위해 사용함
*/
typedef pair<int, int> point;

// 선언부
void state(vector<bool>& visited, int y_loc, int x_loc, const vector<point> &points, int left_points, char direction);

int sAnswer(0);


int main() {
    int N;
    cin >> N;

    vector<point> points(N);
    vector<bool> visited(N, false);

    // y, x좌표 입력받기
    for (int i = 0; i < N; i++) {
        cin >> points[i].first;
        cin >> points[i].second;
    }

    // 문제 풀이
    // 처음은 방향을 어디로 가든 상관 없으므로, UDLR중에 아무것도 아닌 값으로 보낸다.
    state(visited, 0, 0, points, N, 'x');

    cout << sAnswer << endl;    
    return 0;
}

// 함수 구현부
void state(vector<bool>& visited, int y_loc, int x_loc, const vector<pair<int, int>> &points, int left_points, char direction) {
    // 만약 지금 종료조건에 해당한다면, sAnswer를 1 증가시키고 끝낸다.
    // 종료조건은, 모든 점을 방문했으면서 원점으로 돌아갈 수 있어야 한다
    // 원점으로 돌아갈 수 있다는 것은, x혹은 y좌표가 0이라는 뜻이다.
    if (left_points == 0) {
        if (y_loc == 0 || x_loc == 0) {
            sAnswer++;
            return;
        }
    }

    // 종료조건에 해당하지 않는다면, 현재 위치에서 갈 수 있는 점들을 모두 확인해야 한다
    for (int i = 0; i < points.size(); i++) {

        int target_y = points[i].first;
        int target_x = points[i].second;
        // 이미 가 본 점이라면 갈 필요 없음
        if (visited[i]) {
            continue;
        }

        // 같은 y축 선 상에 있는지 체크
        if (target_x == x_loc) {
            // 위로 가야 하는 경우, 지금까지 온 방향이 U가 아니라면 보낸다.
            if (target_y > y_loc && direction != 'U') {
                visited[i] = true;
                state(visited, target_y, target_x, points, left_points - 1, 'U');
                visited[i] = false;
            }

            // 아래로 가야 하는 경우, 방향이 D가 아니라면 보낸다
            else if (target_y < y_loc && direction != 'D') {
                visited[i] = true;
                state(visited, target_y, target_x, points, left_points - 1, 'D');
                visited[i] = false;
            }
        }
        
        // 같은 x축 선 상에 있는지 체크
        if (target_y == y_loc) {
            // 왼쪽으로 가야 하는 경우, 지금까지 온 방향이 L이 아니라면 보낸다.
            if (target_x < x_loc && direction != 'L') {
                visited[i] = true;
                state(visited, target_y, target_x, points, left_points - 1, 'L');
                visited[i] = false;
            }

            // 오른쪽로 가야 하는 경우, 방향이 R이 아니라면 보낸다
            else if (target_x > x_loc && direction != 'R') {
                visited[i] = true;
                state(visited, target_y, target_x, points, left_points - 1, 'R');
                visited[i] = false;
            }
        }
    }
}