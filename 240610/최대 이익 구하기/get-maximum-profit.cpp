#include <iostream>
#include <vector>

/*  
    DP로 진행한다.
    n일차에 벌 수 있는 각 최대 수익을 계산한다
*/

using namespace std;
int main() {
    int N;
    cin >> N;

    vector<int> dp(N + 2, 0);

    for (int i = 1; i <= N; i++) {
        int time, money;
        cin >> time >> money;

        // 오늘 수익이 어제 수익보다 적다면, 그냥 어제까지처럼 일 하고 하루 쉬는 게 돈을 더 많이 번다.
        if (dp[i] < dp[i - 1]) {
            dp[i] = dp[i - 1];
        }

        // 시간이 초과되는 일은 할 수 없다. 그냥 넘기기
        if (time + i > N + 1) {
            continue;
        }

        // 오늘 일을 하는 경우
        int time_passed = i + time;
        int money_earned = dp[i] + money;
        if (dp[time_passed] < money_earned) {
            dp[time_passed] = money_earned;
        }
    }

    cout << dp[N + 1] << endl;
    return 0;
}