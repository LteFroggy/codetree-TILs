#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/*
    쿠폰 3장이 하루 이용권과 교환이 가능하다.
    필요한 최소 비용 구하는 프로그램 작성해보자.

    역시 DP로 처리해야 할 듯.
    DP[N] = pair<int, int>로 처리하고, first는 든 돈, second는 쿠폰 개수로 생각하자.

    매일 매일 1일, 3일, 5일권을 살 수 있다. 따라서 1일권을 사서 도착한 경우, 3일권을 사서 도착한 경우, 5일권을 사서 도착한 경우를 모두 고려하자
    그런데 쉬는 날은???? 고려해야 할까? 아니면 그냥 무시할까? -> 그냥 무시해도 괜찮을지도..

    DP[i] = min(DP[i - 1].first + 10000, DP[i - 3].first + 25000, DP[i - 5].first + 37000) 으로 볼 수 있다.
    단, i가 휴일인 경우 DP[i] = DP[i - 1]이고, DP[i - 1].second >= 3인 경우에는 DP[i] = DP[i - 1]을 여기서도 사용 가능하다.

    주어진 경우 베스트는, 1일에 3일권 사기
    1 ~ 5   5일권 -> 37000, 2
    8 ~ 10  3일권 -> 62000, 3
    13      5일권 -> 62000, 0
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
    int impos_index = 0;
    for (int i = 1; i <= N; i++) {
        // 오늘이 딱히 들어갈 필요 없는 날이라면, 어제 값을 그대로 쓴다.
        if (impos_days[impos_index] == i) {
            DP[i] = DP[i - 1];
            impos_index++;
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
                int ticket_expected = DP[i - ticket[1]].second + ticket[2];

                // 돈이 제일 적은 것이 우선이다.
                if (min_money > money_expected || min_money == -1) {
                    min_money = money_expected;
                    min_ticket = ticket_expected;
                }

                // 돈이 같다면, 티켓 갯수로 생각한다.
                else if (money_expected == min_money && min_ticket < ticket_expected) {
                    min_ticket = ticket_expected;
                }
            }
            // 제일 작은 걸 골랐다면, 저장한다
            DP[i].first = min_money;
            DP[i].second = min_ticket;
        }
    }
    
    // 결과 체크하기
    for (int i = 0; i <= N; i++) {
        cout << "DP[" << i << "].money = " << DP[i].first << endl;
        cout << "DP[" << i << "].ticket = " << DP[i].second << endl;
        cout << endl;
    }
    return 0;
}