#include <iostream>
#include <vector>

using namespace std;

/*
    오른쪽이나 아래로만 갈 수 있다.
    장애물에는 지나가기 불가능

    장애물은 가로나 세로이며, 그 방향으로는 이동이 불가능하다.
    장애물은 x1 y1 x2 y2로 주어진다.
    이동이 방해받는 곳을 찾아내려면 x1 + x2와 y1 + y2를 수행한 후, 둘 중 홀수인 값을 찾는다
    두 값을 더해서 홀수라면 짝 + 홀이 더해진 것이므로 그 방향으로 이동 시에 장애물에 막히는 것을 알 수 있다.
    
    (x1 + x2) / 2, (y1 + y2) / 2를 수행하고 홀수인 값은 +1 해서 그 방향으로 오지 못하는 것으로 보며 ㄴ된다
    예를 들어 (0, 0) (1, 0)이라면 x1 + x2 = 1, y1 + y2 = 0이므로 가로 방향 장애물인 것을 알 수 있고,
    그 위치는 1 / 2 = 0, 0 / 2 = 0이므로 0,0에서 가로 방향으로 갈 수 없으므로 1, 0으로 가지 못하는 장애물이라는 것을 알 수 있다.

    그리고 a, b로 오는 방법은 (a-1, b) + (a, b-1)로 정의할 수 있다. 대신 오지 못하는 방향 저장을 위해 추가 배열을 만든다
    이진수 두 자리의 00 으로 첫 자리는 위에서 내려올 수 있는지 여부, 두번째 자리는 왼쪽에서 올 수 있는지 여부를 확인한다.
    00이면 다 갈 수 있는 것, 10이면 아래로 내려가지 못하는 것, 01이면 오른쪽으로 가지 못하는 것, 11이면 양쪽 다 갈 수 없는 것이다.
*/
int main() {
    int N, M, k;
    cin >> N >> M >> k;

    vector<vector<long>> DP(N + 1, vector<long>(M + 1, 0));
    vector<vector<int>> moves(N + 1, vector<int>(M + 1, 0));

    for (int i = 0; i < k; i++) {
        int x1, x2, y1, y2;
        cin >> y1 >> x1 >> y2 >> x2;

        int xSum = x1 + x2;
        int ySum = y1 + y2;

        // 가로 방향인 경우
        if (xSum % 2 != 0) {
            moves[ySum / 2][xSum / 2] |= 0b01;
        }
        // 세로 방향인 경우
        else {
            moves[ySum / 2][xSum / 2] |= 0b10;
        }
    }

    // for (auto v : moves) {
    //     for (auto v_ : v) {
    //         cout << v_ << " ";
    //     }
    //     cout << endl;
    // }

    DP[0][0] = 1;

    // DP 계산하기
    for (int y = 0; y <= N; y++) {
        for (int x = 0; x <= M; x++) {
            // 왼쪽 값 더하기, 왼쪽에서 장애물이 있어 올 수 없다면, 보지 않는다
            if (x - 1 >= 0 && (moves[y][x-1] & 1) == 0) {
                DP[y][x] += DP[y][x-1];
            }

            // 위쪽 값 더하기, 위쪽에서 장애물이 있어 올 수 없다면, 보지 않는다
            if (y - 1 >= 0 && ((moves[y-1][x] >> 1) & 1) == 0) {
                DP[y][x] += DP[y-1][x];
            }
        }
    }

    // for (auto v : DP) {
    //     for (auto v_ : v) {
    //         cout << v_ << " ";
    //     }
    //     cout << endl;
    // }

    cout << DP[N][M] << endl;
    return 0;
}