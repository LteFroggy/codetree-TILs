#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

/*
    쿠폰 3장이 하루 이용권과 교환이 가능하다.
    필요한 최소 비용 구하는 프로그램 작성해보자.

    역시 DP로 처리해야 할 듯.
    DP = vector<vector<int>>로 처리하고, DP[i][j]는 i일에 j개의 쿠폰을 가진 경우의 최소 금액이라 생각하자.

    i, j별로 1일권, 3일권, 5일권을 구매했을 때 최소금액을 DP[i + a][j + b]에 저장할 것

    매일 매일 1일, 3일, 5일권을 살 수 있다. 따라서 매일 1일권을 사서 도착한 경우, 3일권을 사서 도착한 경우, 5일권을 사서 도착한 경우를 모두 고려하자
    
    주어진 경우 베스트는
    1 ~ 5   5일권 -> 37000, 2
    8 ~ 10  3일권 -> 62000, 3
    13      쿠폰 -> 62000, 0
*/

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> impos_days(M);
    for (int i = 0 ; i < M; i++) cin >> impos_days[i];

    set<int> impos_set(impos_days.begin(), impos_days.end());

    // 쿠폰의 최대는 33개이다. 따라서 (N+1) x (33) 사이즈의 벡터를 만듦.
    vector<vector<int>> DP(N + 1, vector<int>(33, INT_MAX));

    // 0일차 초기화. 0일차에는 쿠폰 0개인 상황만 존재한다.
    DP[0][0] = 0;

    // DP 해나갈 것
    int impos_index = 0;
    for (int day = 0; day <= N; day++) {
        for (int coupon = 0; coupon < 33; coupon++) {
            // INT_MAX인 경우는 이렇게 오는 방법이 없음을 의미한다. 따라서 볼 필요 없음
            if (DP[day][coupon] == INT_MAX) continue;

            // 1일권을 구매하는 경우
            if (day + 1 <= N) 
                DP[day + 1][coupon] = min(DP[day + 1][coupon], DP[day][coupon] + 10000);
            
            // 3일권을 구매하는 경우
            if (day + 3 <= N)
                DP[day + 3][coupon + 1] = min(DP[day + 3][coupon + 1], DP[day][coupon] + 25000);

            // 5일권을 구매하는 경우
            if (day + 5 <= N)
                DP[day + 5][coupon + 2] = min(DP[day + 5][coupon + 2], DP[day][coupon] + 37000);

            // 내일이 쉬는 날이라면 이렇게도 적용 가능하다
            if (day + 1 <= N && impos_set.count(day + 1)) 
                DP[day + 1][coupon] = min(DP[day + 1][coupon], DP[day][coupon]);
            
            // 쿠폰이 사용 가능하면, 사용을 고려한다.
            if (day + 1 <= N && coupon >= 3) 
                DP[day + 1][coupon - 3] = min(DP[day + 1][coupon - 3], DP[day][coupon]);
        }
    }
    
    // // 결과 체크하기
    // for (int i = 0; i <= N; i++) {
    //     for (int j = 0; j < 33; j++) {
    //         if (DP[i][j] == INT_MAX) continue;
    //         cout << "DP[" << i << "][" << j << "] = " << DP[i][j] << endl;
    //     }
    //     cout << endl;
    // }

    // 결과 출력하기
    int min_money = INT_MAX;
    for (int coupon = 0; coupon < 33; coupon++) {
        if (DP[N][coupon] < min_money) {
            min_money = DP[N][coupon];
        }
    }

    cout << min_money << endl;
    return 0;
}