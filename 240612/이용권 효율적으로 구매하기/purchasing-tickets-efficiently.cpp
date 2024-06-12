#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/*
    쿠폰 3장이 하루 이용권과 교환이 가능하다.
    필요한 최소 비용 구하는 프로그램 작성해보자.

    역시 DP로 처리해야 할 듯.
    DP[N] = pair<int, int>로 처리하고, first는 든 돈, second는 쿠폰 개수로 생각하자.

    DP[i] = min(DP[i - 1].first + 10000, DP[i - 3].first + 25000, DP[i - 5].first + 37000) 으로 볼 수 있다.
    단, i가 휴일인 경우 DP[i] = DP[i - 1]이고, DP[i - 1].second >= 3인 경우에는 DP[i] = DP[i - 1]을 여기서도 사용 가능하다.
*/

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> impos_days(M);

    for (int i = 0 ; i < M; i++) cin >> impos_days[i];

    for (auto v : impos_days) cout << v << " ";
    cout << endl;

    vector<pair<int, int>> DP(N + 1);

    DP[0] = make_pair(0, 0);

    vector<vector<int>> ticket_list {{10000, 1, 0}, {25000, 3, 1}, {37000, 5, 2}};

    // DP 해나갈 것
    int impos_indx = 0;
    for (int i = 1; i <= N; i++) {
        // 오늘이 딱히 들어갈 필요 없는 날이라면, 어제 값을 그대로 쓴다.
        if (impos_days[impos_indx] == i) {
            DP[i] = DP[i - 1];
        }

        // 만약, 이전 날에 쿠폰이 3개가 모였다면 그걸 쓸 수 있다.
        else if (DP[i - 1].second >= 3) {
            DP[i] = DP[i - 1];
            DP[i].second -= 3;
        }

        // 다 아니라면, 1일, 3일, 5일 중 어떤 것을 사용할지 정한다.
        else {
            int min_money = -1;
            int min_ticket = -1;
            for (auto ticket : ticket_list) {
                int money_expected = DP[i - ticket[1]].first + ticket[0];

                // 돈이 제일 적은 것이 우선이다.
                if (min_money > money_expected || min_money == -1) {
                    
                }

                // 돈이 같다면, 티켓 갯수로 생각한다.
                else if (money_expected == min_money && DP[i - ticket.second].second + )
             }
        }

        // 그게 아니라면, 1일, 3일, 5일을 비교해봐야 한다.
    }
    
    return 0;
}