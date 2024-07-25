#include <iostream>
#include <set>
using namespace std;

/*
    하나의 명령만 잘못되었는데, 그게 무엇인지 하나하나 경우의 수를 모두 탐색하는 것은 불가능하다.
    dy[4], dx[4]에서 값이 0이면 북쪽으로 가는 것, 1이면 왼쪽으로, 2이면 하단으로, 3이면 오른쪽으로 가는 것이다
    L은 k--를, R은 k++을 수행한다.
    
    일단 처음 상태에서 어디로 가나 확인을 한다. FFF를 예시로 하면 0을 바라보는 (0, 0)에서 (3, 0)으로 가게 된다. 
    LFF였다면? 0을 바라보는 (0, 0)에서 (0, -2)로 간다. 
    바라보는 방향 기준으로 dy[L] * n + dx[L+1] * m으로 이동 위치를 정의할 수 있음

    따라서, 먼저 모든 명령을 수행했을 때에 도착하는 위치를 찾는다.
    현재 위치가 0,0일 때, N개의 명령을 모두 수행했다면 도착 위치는 a,b가 되었다고 가정하면
    앞으로 a칸, 오른쪽으로 b칸 간 것이다. 따라서 N개의 명령을 모두 수행한 결과는 dy[L] * a + dx[L+1] * b이다.
    이제 1번째 명령이 잘못되었다고 가정하기 위해 1번째 명령을 그대로 따라한 후 도착 위치를 가늠해본다.

    하면서 나아가기
*/

typedef pair<int, int> point;

// 4방향을 나타낸다.
int dy[4] = {1, 0, -1, 0};
int dx[4] = {0, 1, 0, -1};

// 현재 위치와 a, b에 따른 도착지를 예상해서 리턴해준다.
point Simulate_Destination(const point now_loc, const int now_dir, const int a, const int b) {
    // a는 현재 바라보는 방향 기준 앞으로 얼마나 가야 하는지, b는 오른쪽으로 얼마나 가야 하는지이다. 둘 다 음수값일 수 있음.
    point pt_return;

    pt_return = now_loc;

    // 사실 now_dir이 0, 2라면(위나 아래를 보고 있다면) dy에 a를 곱해서 더해주고, 아니라면 dx에 곱해서 더해줘야 하지만 귀찮아서 그냥 둘 다 처리하게 됨.
    pt_return.first += dy[now_dir] * a;
    pt_return.second += dx[now_dir] * a;

    pt_return.first += dy[(now_dir + 1) % 4] * b;
    pt_return.second += dx[(now_dir + 1) % 4] * b;

    return pt_return;
}

int main() {

    // 가능한 모든 포인트들을 저장하기 위함. 중복 제거를 위해 set으로 하였다.
    set<point> answers;

    string cmd;
    cin >> cmd;

    
    // 일단 모든 명령을 보면서 도착 지점을 한번 가늠해야 한다.
    // 처음 시작 지점은 (0,0), 보는 방향도 0으로 시작한다.
    point dest_loc;
    point now_loc({0, 0});
    int now_dir = 0;
    for (int i = 0; i < cmd.size(); i++) {
        char command = cmd[i];
        // 앞으로 가야 하면 좌표에 값 더하기
        if (command == 'F') {
            now_loc.first += dy[now_dir];
            now_loc.second += dx[now_dir];
        }   

        // L이면 왼쪽으로 돌기
        else if (command == 'L') {
            // -1해야 하는데, 0보다 작은 값이 될 수 있으므로 3 더하고 나머지 해주기.
            now_dir += 3;
            now_dir %= 4;
        }
        // R이면 오른쪽으로 돌기
        else {
            // 3보다 커지면 오류 생기므로, 나머지 해주기
            now_dir++;
            now_dir %= 4;
        }
    }


    // cout << "예상 도착 지점은 " << now_loc.first << ", " << now_loc.second << endl;



    // 이러면 도착 지점이 나온다. 이걸 저장한다.
    dest_loc.first = now_loc.first;
    dest_loc.second = now_loc.second;

    // 이제는 하나씩 틀렸다고 가정해보면서 모든 가능 지점을 찾아낼 것이다.
    // now_loc은 현재 위치, next_loc은 이번 명령이 틀리지 않았다고 가정했을 시 도착하는 위치.
    now_loc = {0, 0};
    now_dir = 0;
    point next_loc = now_loc;
    int next_dir = 0;
    for (int i = 0; i < cmd.size(); i++) {
        
        // cout << i << "번째 명령이 틀렸다고 가정한 경우" << endl;

        // i번째 명령이 틀렸다고 가정해보자. 그럼 일단 i+1 ~ N번째 명령을 다 수행했을 때 어떤 결과가 나오는지를 알아야 한다.
        // 그래야 바른 명령으로 고쳤을 때 도착 지점을 유추할 수 있기 때문. 따라서 먼저 i+1 ~ N번째 명령을 수행한 경우를 보자.
        // 이를 위해서는 i번쨰 명령을 주어진 대로 수행해야 함.
        now_loc = next_loc;
        now_dir = next_dir;

        // i번째 명령 멀쩡히 수행하기
        char command = cmd[i];
        if (command == 'F') {
            next_loc.first += dy[now_dir];
            next_loc.second += dx[now_dir];
        }

        else if (command == 'L') {
            next_dir += 3;
            next_dir %= 4;
        }

        else {
            next_dir++;
            next_dir %= 4;
        }

        // cout << i << "번째 명령을 정상적으로 수행했을 경우의 위치와 방향 : (" << next_loc.first << ", " << next_loc.second << "), " << next_dir << endl;

        // 이러면 i번째 명령을 수행했을 때에 현재 위치와 향하고 있는 방향이 나온다.
        // 이 값을 이용해서 i+1 ~ N번째 명령을 수행했을 떄의 위치의 변화값을 구한다.
        // a는 현재 향하고 있는 방향 기준 앞으로 얼마나 갈지, b는 오른쪽으로 얼마나 갈지이다.
        int a, b;

        // 위나 아래를 향하고 있다면, a가 상하방향값, b가 좌우방향값을 의미하게 된다.
        if (dy[next_dir] != 0) {
            a = (dest_loc.first - next_loc.first) / dy[next_dir];
            b = (dest_loc.second - next_loc.second) / dx[(next_dir + 1) % 4];
        }   

        // 아니라면, a가 좌우, b가 상하이다.
        else {
            a = (dest_loc.second - next_loc.second) / dx[next_dir];
            b = (dest_loc.first - next_loc.first) / dy[(next_dir + 1) % 4];
        }

        // cout << "따라서, a = " << a << ", b = " << b << endl;

        // 이렇게 a와 b를 구했다면, 이제 이번 명령이 틀렸을 경우에 도착하는 모든 경우를 찾아내야 한다.
        point now_loc_tmp;
        int now_dir_tmp;
        
        // 이번 명령이 사실 F였을 경우, 근데 원래 F였으면 이건 하면 안됨
        if (command != 'F') {
            now_loc_tmp = now_loc;
            now_dir_tmp = now_dir;
            // 일단 F를 수행했을 것이다.
            now_loc_tmp.first += dy[now_dir];
            now_loc_tmp.second += dx[now_dir];

            // 함수를 통해 도착 예정지를 받고, 그걸 answer에 넣는다.
            now_loc_tmp = Simulate_Destination(now_loc_tmp, now_dir_tmp, a, b);
            answers.insert(now_loc_tmp);

            // cout << i << "번째 명령이 F였을 경우에는, " << now_loc_tmp.first << ", " << now_loc_tmp.second << "로 가게 된다." << endl;
        }

        // 명령이 사실 L이었을 경우
        if (command != 'L') {
            now_loc_tmp = now_loc;
            now_dir_tmp = now_dir;
            // 일단 L을 수행한다.
            now_dir_tmp += 3;
            now_dir_tmp %= 4;

            // 함수를 사용해 도착지를 받는다.
            now_loc_tmp = Simulate_Destination(now_loc_tmp, now_dir_tmp, a, b);
            answers.insert(now_loc_tmp);

            // cout << i << "번째 명령이 L이었을 경우에는, " << now_loc_tmp.first << ", " << now_loc_tmp.second << "로 가게 된다." << endl;
        }

        // 명령이 R이었을 경우
        if (command != 'R') {
            now_loc_tmp = now_loc;
            now_dir_tmp = now_dir;
            // 일단 R을 수행한다.
            now_dir_tmp++;
            now_dir_tmp %= 4;

            // 함수를 사용해 도착지를 받는다.
            now_loc_tmp = Simulate_Destination(now_loc_tmp, now_dir_tmp, a, b);
            answers.insert(now_loc_tmp);            

            // cout << i << "번째 명령이 R이었을 경우에는, " << now_loc_tmp.first << ", " << now_loc_tmp.second << "로 가게 된다." << endl;
        }

        // cout << endl;
    }   
    
    // 이걸 끝까지 하면 된다. 이제 set의 길이를 출력한다
    cout << answers.size() << endl;
    return 0;
}