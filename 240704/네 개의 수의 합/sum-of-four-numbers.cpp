#include <iostream>
#include <vector>
#include <set>

using namespace std;

/*
    앞의 원소들을 더해서 만들 수 있는 값의 개수를 센다.

    vector<vector<set<int>>> DP를 만든다.
    DP[1][0] ~ DP[1][4]까지는 0번쨰 원소까지 보았을 때, 값을 0번 사용해 만들어지는 값 ~ 1번 사용해서 만들어지는 값들이 저장될 것이다.

    DP[i][n] = DP[i-1][n] + for (a in DP[i][n-1]) (a + ith_value) 로 이루어진다.
*/

int main() {
    int N;
    cin >> N;
    int answer = 0;

    vector<vector<set<int>>> DP(N + 1, vector<set<int>>(5));

    DP[0][0].insert(0);

    for (int i = 1; i <= N; i++) {
        int tmp;
        cin >> tmp;

        if (DP[i-1][4].count(tmp))
            answer++;

        DP[i][0] = DP[i - 1][0];

        for (int j = 1; j <= 4; j++) {
            DP[i][j] = DP[i-1][j];

            for (auto v : DP[i][j-1]) {
                DP[i][j].insert(v + tmp);
            }
        }
    }

    // for (int i = 1; i <= N; i++) {
    //     for (int j = 1; j <= 4; j++) {
    //         cout << "DP[" << i << "][" << j << "] = ";
    //         for (auto val : DP[i][j]) {
    //             cout << val << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    cout << answer << endl;
    return 0;
}