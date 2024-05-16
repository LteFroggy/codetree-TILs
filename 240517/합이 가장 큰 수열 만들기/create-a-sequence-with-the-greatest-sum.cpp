#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/*
    길이가 n인 수열, 수열에서 원소를 맘대로 뽑아 길이가 가장 긴 오름차순 수열?
    
    DP로 각 값마다 자신까지 오는 데에 Best인 수열의 길이와 원소의 합을 기억시키자.
*/

int main() {
    int N;
    cin >> N;
    vector<int> numbers(N);
    vector<pair<int, int>> dp(N);

    for (int i = 0; i < N; i++) {
        cin >> numbers[i];
    }

    // dp[0]값은 직접 주기
    dp[0] = make_pair(1, numbers[0]);

    // i번쨰까지 오는 방법 중 제일 베스트인 방법을 찾을 것
    for (int i = 1; i < N; i++) {
        int best_length = 0;
        int best_sum = 0;
        for (int j = i-1; j >= 0; j--) {
            // 자신보다 작은 값만이 다음으로 자신을 고를 수 있으므로 자기보다 큰 값은 보지 않는다
            if (numbers[j] >= numbers[i]) {
                continue;
            }
            
            // 자기보다 앞에 있고, 자기보다 작은 값 중 최대의 length와 sum을 찾아낸다.
            if (best_length < dp[j].first || (best_length == dp[j].first && best_sum < dp[j].second)) {
                best_length = dp[j].first;
                best_sum = dp[j].second;
            }
        }
        
        // 거기에 자신의 값을 더해서 저장한다.
        dp[i] = make_pair(best_length + 1, best_sum + numbers[i]);
    }

    // for (auto v : dp) {
    //     cout << v.first << ", " << v.second << endl;
    // }

    int total_best_length = 0;
    int total_best_sum = 0;

    for (int i = 0; i < N; i++) {
        if (total_best_length < dp[i].first || (total_best_length == dp[i].first && total_best_sum < dp[i].second)) {
            total_best_length = dp[i].first;
            total_best_sum = dp[i].second;
        }
    }

    cout << total_best_sum << endl;
    return 0;
}