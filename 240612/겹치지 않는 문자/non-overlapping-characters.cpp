#include <iostream>
#include <vector>

using namespace std;

/*
    만들고자 하는 문자열의 길이가 있음.
    문자 a, b, c를 삽입하는 데에 드는 비용이 공백을 사이에 두고 주어진다.

    연속해서 같은 문자가 나오지 않으며, 길이가 n인 문자열을 만들기 위한 최소 비용을 구해보자.
*/

int main() {
    int N;
    cin >> N;

    vector<vector<int>> value_loc(N + 1, vector<int>(3));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> value_loc[i][j];
        }
    }

    // DP[n][m]는 n번째 자리에 a, b, c중 m번째 문자를 넣었을 때의 드는 최소비용을 파악한다.
    vector<vector<int>> DP(N + 1, vector<int>(3, -1));
    DP[0][0] = 0;
    DP[0][1] = 0;
    DP[0][2] = 0;

    // i번째 자리에 j번째 문자를 넣을 것이다. 그 과정마다 이전의 a, b, c값을 확인해보아야 함
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 3; j++) {
            // 연속된 문자가 두 번 들어올 수는 없으므로 이전에 들어온 문자(j)에 따라 식이 달라진다.
            switch (j) {
                case 0 :
                    DP[i][j] = min(DP[i-1][1] + value_loc[i][0], DP[i-1][2] + value_loc[i][0]);
                    break;
                case 1 :
                    DP[i][j] = min(DP[i-1][0] + value_loc[i][1], DP[i-1][2] + value_loc[i][1]);
                    break;
                case 2 :
                    DP[i][j] = min(DP[i-1][0] + value_loc[i][2], DP[i-1][1] + value_loc[i][2]);
                    break;
            }
        }
    }

    // 완성되었다면, DP 확인
    // for (int j = 0; j <= N; j++) {
    //     for (int i = 0; i < 3; i++) {
    //         cout << "DP[" << j << "][" << i << "] = " << DP[j][i] << endl;
    //     }
    // }

    // 마지막으로 DP값 순회하고 출력
    int answer = min(min(DP[N][0], DP[N][1]), DP[N][2]);
    cout << answer << endl;
    return 0;
}