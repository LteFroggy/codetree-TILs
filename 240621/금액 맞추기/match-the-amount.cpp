#include <iostream>
#include <vector>

using namespace std;

/*
    n명이 최대 m개의 동전을 가진다.
    1명이라고 생각하면 어떨까? -> 1명이 가진 동전이 k원이 되는 경우의 수를 고려하면 된다.

    2명이면 -> 1명 동전 + 1명 동전이 k원이 되는 경우의 수를 고려하면 된다.
    
    3명이 되면 -> 2명 + 1명 동전이 K원이 되는 경우 구하기

    DP[1][k]는 1명만 고려헀을 때 k원이 되는 경우의 수이다

    DP[0][0] = 0;
    i번째 사람의 동전 중 a값을 만났을 때,
    DP[i][a] = DP[i - 1][0], DP[i][a + 1] = DP[i - 1][1]; 같은 방식으로 갱신해나간다
*/
int main() {
    int N, M, K;
    cin >> N >> M >> K;
    
    vector<vector<int>> DP(N + 1, vector<int>(K + 1, 0));

    // 초기화
    DP[0][0] = 1;

    // DP 해나가기
    for (int i = 1; i <= N; i++) {
        int count;
        cin >> count;

        // i번째 사람이 동전을 내지 않을 수도 있다! 따라서 기본값은 이전 노드 그대로
        for (int j = 0; j <= K; j++) {
            DP[i][j] = DP[i - 1][j];
        }

        for (int j = 0; j < count; j++) {
            int tmp;
            cin >> tmp;
            // cout << tmp << endl;

            for (int k = 0; k + tmp <= K; k++) {
                DP[i][k + tmp] += DP[i - 1][k];
                DP[i][k + tmp] %= 10007;
            }
        }
    }

    // DP 결과 확인
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            // cout << "DP[" << i << "][" << j << "] = " << DP[i][j] << endl;
        }
        // cout << endl;
    }

    cout << DP[N][K] << endl;
    return 0;
}