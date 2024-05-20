#include <iostream>
#include <vector>
#include <climits>

using namespace std;

/*
    물건은 같이 포장하냐 새로 포장하냐밖에 없다
    
    매 자리마다 이번에 물건을 새로 포장해서 끝까지 포장하는 경우의 수를 탐색한다.
    비용만 저장하면 된다. 어차피 매번 내가 새로운 포장이 될 것이니까
*/

int main() {
    int N, m, K;
    cin >> N >> m >> K;

    vector<int> objects(N + 1);
    vector<long long> dp(N + 1, LLONG_MAX);
    
    for (int i = 1; i <= N; i++) {
        cin >> objects[i];
    }

    dp[0] = 0;

    for (int std = 1; std <= N; std++) {
        // 매번 i번째 원소부터 가능한 최대 개수까지 포장을 진행하고, 그때그때의 값을 DP에 넣을 것
        // 먼저 새로 포장한다고 가정한다.
        int base_value = dp[std - 1] + K;
        // 이번에 새로 포장한게 가장 작은 값이라면, 이걸로 저장
        if (base_value < dp[std]) {
            dp[std] = base_value;
        }
        
        
        // 앞으로 m개를 이 박스 안에 모두 넣는다고 가정하고, 그때그때의 값을 구할 것
        int value;
        int min_val = objects[std];
        int max_val = objects[std];
        for (int ptr = 1; (ptr < m) && (std + ptr <= N); ptr++) {
            if (min_val > objects[std + ptr]) {
                min_val = objects[std + ptr];
            }
            else if (max_val < objects[std + ptr]) {
                max_val = objects[std + ptr];
            }

            value = base_value;
            value += (ptr + 1) * (max_val - min_val);

            if (value < dp[std + ptr]) {
                dp[std + ptr] = value;
            }
        }
    }

    // for (int i = 1; i <= N; i++) {
    //     cout << dp[i] << endl;
    // }

    cout << dp[N] << endl;
    return 0;
}