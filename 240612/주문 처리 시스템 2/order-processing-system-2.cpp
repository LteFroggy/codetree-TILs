#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/*
    먼저, 가능 불가능 여부부터 판별해야 한다.
    여러 수를 가지고 가능 여부를 판별하려면, DP를 사용해야 한다
    N까지의 DP를 만든다.

    그리고 더해져서 나올 수 잇는 모든 값을 갱신해야 한다.

    1. 한 번에 2개의 처리기까지 사용 가능한 점을 고려하여 더해질 수 있는 값을 모두 고른다
    2. 모든 값 a에 대해 
        for (int i = a; i <= N; i++) if (dp[i-a]) dp[i] = true를 반복한다.
        i-a가 true라면, i-a라는 값은 만들어질 수 있는 것이므로 거기에 a를 더한 i값도 가능함을 의미하는 것이다.
    3. 여기에, 횟수를 출력해달라고 하였으므로 최소 횟수를 저장하기 위해 dp[i]에는 숫자값을 저장한다. 이는 몇 번 더했는지를 의미하는 것
*/

int main() {
    int N, M;
    cin >> N >> M;

    // 주문기 입력받기
    vector<int> processors(M);
    for (int i = 0; i < M; i++) {
        cin >> processors[i];
    }

    // 가능한 모든 처리 개수 저장하기
    set<int> possible_values;
    for (int i = 0; i < M; i++) {
        // 먼저 i번째 처리기 하나만 사용하는 경우를 입력한다
        possible_values.insert(processors[i]);

        // 이후 두 개의 처리기를 같이 사용하는 경우에 대해 고려할 것
        // 한 처리기를 두 번 사용하면 안되므로 j != i 조건이 있어야 한다.
        for (int j = 0; j < M && j != i; j++) {
            possible_values.insert(processors[i] + processors[j]);
        }
    }

    // for (auto v : possible_values) cout << v << " ";
    // cout << endl;

    // DP를 사용한다. 기본값인 10001은 만들어질 수 없는 상태라는 뜻
    // DP의 값은 몇 번의 처리를 거쳐야 만들어질 수 있는 값인지를 저장하며, 최소 값만 유지할 것
    // 최소 횟수만을 저장하기 위해 possible_values는 역순으로 정렬되어있어야 한다.(나중에 더 최소 횟수를 찾아내는 일을 없애기 위해)
    vector<int> dp(N + 1, 10001);
    dp[0] = 0;

    for (auto val : possible_values) {
        // 값 v부터 N까지 쭉 탐색해가면서 더해져서 만들어질 수 있는 값인지 판별할 것
        // cout << "----- " << val << " 탐색 중 -----" << endl;
        for (int i = val; i <= N; i++) {
            // -1이 아니면(만들어질 수 있으면) 값을 수정해야 할 수도 있다.
            if (dp[i - val] != 10001) {
                // 더 적은 횟수로 도착할 방법을 찾은 경우에만 값을 갱신한다.        
                if (dp[i] > dp[i - val] + 1) {
                    dp[i] = dp[i - val] + 1;    
                    // cout << "dp[" << i << "] 가능. 값은 " << dp[i] << endl;
                }
            }
        }
    }


    cout << dp[N] << endl;
    return 0;
}