#include <iostream>
#include <vector>

using namespace std;

struct status {
    vector<bool> job_done;
    int income = 0;
};

typedef pair<int, int> job;

void print_trace(vector<status> dp) {
    for (int i = 0; i < dp.size(); i++) {
        if (dp[i].income != 0) {
            cout << i + 1 << "일차 최대 수입 : " << dp[i].income << endl;
            cout << "한 일 목록 : ";
            for (int j = 0; j < dp.size() - 1; j++) {
                if (dp[i].job_done[j]) {
                    cout << j+1 << " ";
                }
            }
            cout << endl;
        }
    }
    cout << endl << endl;
}

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

    vector<job> jobs(N);

    for (int i = 0; i < N; i++) {
        cin >> jobs[i].first;
        cin >> jobs[i].second;
    }

    
    
    vector<status> dp(N + 1);
    // dp 전체 초기화
    for (int i = 0; i < N; i++) {
        dp[i].income = 0;
        dp[i].job_done = vector<bool>(N, false);
    }

    // 0일차부터 DP를 통해 각 날짜별 최대값을 구해간다.
    for (int i = 0; i < N; i++) {
        // 오늘 i번째 날에 받은 일 중 하나를 할 경우
        for (int j = 0; j <= i; j++) {
            // 일단 아직 안 한 일이어야 할 수 있고, 날짜가 넘는 일은 하면 안됨
            if (!dp[i].job_done[j] && i + jobs[j].first <= N) {
                int day_afterWork = i + jobs[j].first;
                int money_afterWork = dp[i].income + jobs[j].second;

                // 만약 이게 그 날의 최대 수입이라면, 이 상태로 dp를 갱신한다.
                if (dp[day_afterWork].income < money_afterWork) {
                    dp[day_afterWork].income = money_afterWork;
                    dp[day_afterWork].job_done = dp[i].job_done;
                    dp[day_afterWork].job_done[j] = true;

                    cout << i+1 << "일차에 " << j + 1  << "일차의 일을 수행하면 " << day_afterWork + 1 << "일에 최대의 수입인 " << money_afterWork << "원을 벌 수 있음" << endl;
                    print_trace(dp);
                }
            }
        }

        // 내일의 최소 수입은 오늘 아무것도 안 하고 넘어갔을 경우임
        if (dp[i + 1].income == 0) {
            dp[i + 1].income = dp[i].income;
            dp[i + 1].job_done = dp[i].job_done;
        }
    }
    
    // 결과 출력하기(마지막날 최대 수입)
    cout << dp[N].income << endl;
    return 0;
}