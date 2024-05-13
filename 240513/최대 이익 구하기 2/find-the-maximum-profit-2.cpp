#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> job;
/*
    매일 매일 일이 생긴다. 이렇게 슬픈 일이....
    하는 데 걸리는 날짜와 받는 보수가 정해져있다

    일은 n일 안에 마무리되어야 한다

    최대의 이익을 얻는 방법을 생각해보자.

    그럼 매일마다 그날 가능한 최선의 선택들만을 나열하고, 선택했을 떄와 선택하지 않았을 때를 구분할까?
    3 2 1이 있을 때, 
    결국 시간 총합이 N 이하인, 값 최대의 조합을 찾는 것이다. 근데 그게 원하는 날짜에 나오지 않았을 수 있음.

    DP로 가자
    n일차까지 얻을 수 있는 최대 이득을 보면 된다.
*/

int main() {
    int N;
    cin >> N;

    vector<job> jobs(N + 1);

    for (int i = 0; i < N; i++) {
        cin >> jobs[i].first;
        cin >> jobs[i].second;
    }

    vector<int> dp(N, 0);

    for (int i = 0; i < N; i++) {
        // 그 날 주어진 일을 할 경우
        if (i + jobs[i].first <= N) {
            int day_next = i + jobs[i].first;
            int income_next = dp[i] + jobs[i].second;

            if (dp[day_next] < income_next) {
                dp[day_next] = income_next;
            }
        }
        
        // 그 다음 날의 최소 수입은 오늘 아무 일도 하지 않고 넘어갔을 때이다
        if (dp[i + 1] == 0) {
            dp[i + 1] = dp[i];
        }
    }
    
    cout << dp[N] << endl;
    return 0;
}