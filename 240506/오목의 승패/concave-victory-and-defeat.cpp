#include <iostream>
#include <array>

using namespace std;

/*
    오목 승패판별하기
    6개 이상의 바둑알은 승리한 것이 아니다. 딱 다섯개가 있어야 함

    좌상단부터 볼 것이니, 방향은 아래, 우하, 우측만 보면 된다.
    대신, 그 역방향에 같은 값이 있었다면 볼 필요 없는 것이니 그것은 체크해야 한다.
*/

bool inboard_check(int y, int x) {
    return y >= 0 && y < 19 && x >= 0 && x < 19;
}

int main() {
    array<array<int, 19>, 19> board;

    // 보드 입력받기
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            cin >> board[i][j];
        }
    }

    // 보는 방향 순서는 하, 우하대각, 우, 우상대각 순으로 볼 것
    int dy[] = {1, 1, 0, -1};
    int dx[] = {0, 1, 1, 1};

    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            // 빈칸이 아닌 값을 찾았다면, 3각 보면서 빙고인지 확인하자
            if (board[i][j] != 0) {
                int checking_val = board[i][j];


                for (int k = 0; k < 4; k++) {
                    int y = i;
                    int x = j;

                    // 먼저 역방향에 같은 값이 있었는지 확인할 것. 있다면 그 친구가 먼저 이 방향 빙고를 확인해보았을 것이기 때문
                    int counter_y = y - dy[k];
                    int counter_x = x - dx[k];
                    if (inboard_check(counter_y, counter_x) && board[counter_y][counter_x] == checking_val) {
                        continue;
                    }

                    // 역방향에 같은 값이 없었다면, 딱 4개가 이어져있는지 확인할 것
                    int count = 0;
                    while (true) {
                        y += dy[k];
                        x += dx[k];
                        if (!inboard_check(y, x)) break;
                        if (board[y][x] == checking_val) count++;
                        else break;
                    }
                    
                    // 만약 딱 4개만 있었다면, 나를 포함했을 때 승리이므로 출력하고 종료하기
                    if (count == 4) {
                        cout << checking_val << endl;
                        cout << i + 1 << " " << j + 1 << endl;
                        return 0;
                    }       
                }
            }
        }
    }

    // 다 봤는데 승자가 없었다 ? 0 출력
    cout << 0 << endl;
    return 0;
}