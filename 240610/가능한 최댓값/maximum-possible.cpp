#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/*
    왼쪽, 오른쪽 순서쌍을 모두 저장해둔다,
    DP로 왼쪽에서 n개, 오른쪽에서 n개를 고르는 경우를 찾을 것
    
    DP[i][j][k]를 가진다. 여기서 i, j, k는 각각 확인한 순서쌍 개수, j는 선택한 왼쪽 값 개수, k는 선택한 오른쪽 값 개수이다.

    DP[0][0][0] = 0
    DP[i][j][k]의 기본값은 DP[i - 1][j][k]
    새로운 열에 대해서 왼쪽 값을 선택할 경우,
    DP[i][j][k] = max(DP[i][j][k], DP[i-1][j-1][k] + l_value)
    새로운 열에 대해서 오른쪽 값을 선택할 경우, 
    DP[i][j][k] = max(DP[i][j][k], DP[i-1][j][k-1] + r_value)

    예를 들어
    DP[30][14][15]를 고를 떄,
    기본은 DP[29][14][15]로 출발
    왼쪽 값을 고르는 경우 탐색을 위해 
    DP[30][14][15], DP[29][13][15] + l_value 중 큰 값을  구한다.
*/

int main() {
    int N;
    cin >> N;

    // i번째 값이 사용 가능한지 확인하기 위한 변수
    vector<bool> usable(N, true);
    vector<pair<int, int>> pairs(N + 1);
    vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(16, vector<int>(16)));

    // 입력받기
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 2; j++) {
            if (j == 0) cin >> pairs[i].first;
            else cin >> pairs[i].second;
        }
    }

    // for (int i = 1; i <= N; i++) {
    //     cout << pairs[i].first << " " << pairs[i].second << endl;
    // }

    dp[0][0][0] = 0;

    for (int i = 1; i <= N; i++) {
        int l_value = pairs[i].first;
        int r_value = pairs[i].second;
        for (int j = 0; j <= 15 && j <= i; j++) {
            for (int k = 0; k <= 15 && j + k <= i; k++) {
                // 기본값은 이전 상태 그대로
                dp[i][j][k] = dp[i - 1][j][k];

                // 왼쪽 값을 고르는 경우
                // 0일 때는 고를 수 없으므로 고르지 않고, 나머지 경우에서는 고르는 게 유리한지 본다.
                if (j != 0) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k] + l_value);
                }

                // 오른쪽 값을 고르는 경우
                if (k != 0) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + r_value);
                }

                // 위의 과정을 수행하면, 어떤 열에서 왼쪽 값을 고르는 경우와 오른쪽 값을 고르는 경우 중 더 큰 값을 골라 올 수 있다.
                // if (j + k == 1) {
                // cout << "DP[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << endl; 
                // }
            }
        }
    }

    cout << dp[N][15][15] << endl;
    return 0;
}

    /* 1안
    // 총 15번 고를 것
    for (int i = 0; i < 15; i++) {
        int L_max_idx = -1;
        int L_max_val = 0;
        int L_max_R = 0;
        
        int R_max_idx = -1;
        int R_max_val = 0;
        int R_max_L = 0;

        // cout << i+1 << "번째 루프 ------------ " << endl;

        for (int j = 0; j < N; j++) {
            // 사용 불가능한 값(이미 값이 쓰이고 있는 줄)이면 볼 필요 없음
            if (!usable[j]) continue;
            
            // 왼쪽에서 제일 큰 값 찾기
            if (numbers[j][0] > L_max_val) {
                L_max_val = numbers[j][0];
                L_max_idx = j;
                L_max_R = numbers[j][1];
            }

            // 한 쪽 값은 같은데 반대쪽 값이 다르다면, 반대쪽 값이 최대한 작은 쪽을 골라야 제일 큰 값을 뽑는 데에 문제가 없을 것
            else if (numbers[j][0] == L_max_val && numbers[j][1] < L_max_R) {
                L_max_idx = j;
                L_max_R = numbers[j][1];
            }

            // 오른쪽에서 제일 큰 값 찾기
            if (numbers[j][1] > R_max_val) {
                R_max_val = numbers[j][1];
                R_max_idx = j;
                R_max_L = numbers[j][0];
            }

            // 한 쪽 값은 같은데 반대쪽 값이 다르다면, 반대쪽 값이 최대한 작은 쪽을 골라야 제일 큰 값을 뽑는 데에 문제가 없을 것
            else if (numbers[j][1] == R_max_val && numbers[j][0] < R_max_L) {
                R_max_idx = j;
                R_max_L = numbers[j][0];
            }
        }
        
        // cout << "좌측 최대값 위치 : " << L_max_idx << endl;
        // cout << "좌측 최대값 : " << L_max_val << endl;
        // cout << "우측 최대값 위치 : " << R_max_idx << endl;
        // cout << "우측 최대값 : " << R_max_val << endl;

        // 만약 두 값이 같은 줄에 있다면, 세컨드 값과 비교해야 함
        if (L_max_idx == R_max_idx) {
            cout << "좌측 최대값 위치 : " << L_max_idx << endl;
            cout << "좌측 최대값 : " << L_max_val << endl;
            cout << "우측 최대값 위치 : " << R_max_idx << endl;
            cout << "우측 최대값 : " << R_max_val << endl;

            cout << "두 값이 같은 줄에 있어 차선책 고를 것" << endl;
            int L_sec_val = 0;
            int L_sec_idx = -1;
            int L_sec_R = 0;

            int R_sec_val = 0;
            int R_sec_idx = -1;
            int R_sec_L = 0;

            // 최대값에 해당되는 줄은 보지 않게 usable값 변경
            usable[L_max_idx] = false;

            // 두 번쨰로 큰 값 찾기
            for (int j = 0; j < N; j++) {
                if (!usable[j]) continue;

                // 왼쪽에서 두번째로 큰 값 찾기
                if (numbers[j][0] > L_sec_val) {
                    L_sec_val = numbers[j][0];
                    L_sec_idx = j;
                    L_sec_R = numbers[j][1];
                }

                // 한 쪽 값은 같은데 반대쪽 값이 다르다면, 반대쪽 값이 최대한 작은 쪽을 골라야 제일 큰 값을 뽑는 데에 문제가 없을 것
                else if (numbers[j][0] == L_sec_val && numbers[j][1] < L_sec_R) {
                    L_sec_idx = j;
                    L_sec_R = numbers[j][1];
                }

                // 오른쪽에서 제일 큰 값 찾기
                if (numbers[j][1] > R_sec_val) {
                    R_sec_val = numbers[j][1];
                    R_sec_idx = j;
                    R_sec_L = numbers[j][0];
                }

                // 한 쪽 값은 같은데 반대쪽 값이 다르다면, 반대쪽 값이 최대한 작은 쪽을 골라야 제일 큰 값을 뽑는 데에 문제가 없을 것
                else if (numbers[j][1] == R_sec_val && numbers[j][0] < R_sec_L) {
                    R_sec_idx = j;
                    R_sec_L = numbers[j][0];
                }
            }

            cout << "좌측 세컨값 위치 : " << L_max_idx << endl;
            cout << "좌측 세컨값 : " << L_max_val << endl;
            cout << "우측 세컨값 위치 : " << R_max_idx << endl;
            cout << "우측 세컨값 : " << R_max_val << endl;

            // 두 번째로 큰 값을 찾았다면, 제일 큰 값 - 두번째로 큰 값의 결과(차선책을 선택했을 때의 손해)가 더 큰 쪽을 사용해야 한다.
            // 둘이 손해가 같다면 오른쪽 값 쓸 것
            if (L_max_val - L_sec_val > R_max_val - R_sec_val) {
                usable[L_max_idx] = false;
                usable[R_sec_idx] = false;
                answer += L_max_val;
                answer += R_sec_val;
            }
            
            else {
                usable[L_sec_idx] = false;
                usable[R_max_idx] = false;
                answer += L_sec_val;
                answer += R_max_val;

                choosed[0][i] = L_sec_val;
                choosed[1][i] = R_max_val;
            }
        }

        // 다른 줄에 있다면, 그냥 두 값 다 적용하면 됨
        else {
            // cout << "두 값은 다른 줄에 있으므로 그냥 적용함" << endl;
            usable[L_max_idx] = false;
            usable[R_max_idx] = false;
            answer += L_max_val;
            answer += R_max_val;
            choosed[0][i] = L_max_val;
            choosed[1][i] = R_max_val;
            // cout << "Answer = " << answer << endl;
        }
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0;)
    }

    cout << answer << endl;
    return 0;
}

*/