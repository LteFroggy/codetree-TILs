#include <iostream>
#include <vector>
#include <set>

using namespace std;

/*
    앞의 원소들을 더해서 만들 수 있는 값의 개수를 센다.

    vector<vector<set<int>>> DP를 만든다.
    DP[1][0] ~ DP[1][4]까지는 0번쨰 원소까지 보았을 때, 값을 0번 사용해 만들어지는 값 ~ 1번 사용해서 만들어지는 값들이 저장될 것이다.

    DP[i][n] = DP[i-1][n] + for (a in DP[i][n-1]) (a + ith_value) 로 이루어진다.

    다 저장하니 메모리가 터진다. 어차피 DP[n]을 완성할 때는 DP[n-1]만 필요하니, 두 개의 DP만 유지하면서 이어나가자
*/

int main() {
    int N;
    cin >> N;
    int answer = 0;

    vector<set<int>> DP_now(5);
    vector<set<int>> DP_past(5);

    DP_now[0].insert(0);

    for (int i = 1; i <= N; i++) {
        int tmp;
        cin >> tmp;

        if (DP_now[4].count(tmp))
            answer++;

        DP_past = DP_now;
        DP_now = vector<set<int>>(5);

        DP_now[0] = DP_past[0];

        for (int j = 1; j <= 4; j++) {
            DP_now[j] = DP_past[j];

            for (auto v : DP_now[j-1]) {
                DP_now[j].insert(v + tmp);
            }
        }

        // for (int j = 1; j <= 4; j++) {
        //     cout << "DP[" << i << "][" << j << "] = ";
        //     for (auto val : DP_now[j]) {
        //         cout << val << " ";
        //     }
        //     cout << endl;
        // }   
    }

    cout << answer << endl;
    return 0;
}