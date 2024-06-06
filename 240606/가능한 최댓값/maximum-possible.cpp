#include <iostream>
#include <vector>

using namespace std;

/*
    왼쪽, 오른쪽 순서쌍을 모두 저장해둔다,
    DP로 왼쪽에서 n개, 오른쪽에서 n개를 고르는 경우를 찾을 것
    100 100
    90 90
    90 40
    90 50

    77 90
        
    3  
    100 89
    
    100 100
    100 50
    100 40
    100 90

    1. 왼쪽에서의 최대값 위치와 오른쪽에서의 최대값 위치를 찾는다
    2. 서로 같다면, second_max과의 차이를 본다
    3. second_max과의 차이가 큰 쪽한테 양보해준다.
*/

int main() {
    int N;
    cin >> N;

    // i번째 값이 사용 가능한지 확인하기 위한 변수
    vector<bool> usable(N, true);
    vector<vector<int>> numbers(N, vector<int>(2));

    // 입력받기
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> numbers[i][j];
        }
    }

    int answer = 0;

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
                cout << "좌측 손해가 더 크므로 좌측 값 적용" << endl;
            }
            
            else {
                usable[L_sec_idx] = false;
                usable[R_max_idx] = false;
                answer += L_sec_val;
                answer += R_max_val;
                cout << "우측 손해가 더 크므로 우측 값 적용" << endl;
            }
        }

        // 다른 줄에 있다면, 그냥 두 값 다 적용하면 됨
        else {
            // cout << "두 값은 다른 줄에 있으므로 그냥 적용함" << endl;
            usable[L_max_idx] = false;
            usable[R_max_idx] = false;
            answer += L_max_val;
            answer += R_max_val;
            // cout << "Answer = " << answer << endl;
        }
    }

    cout << answer << endl;
    return 0;
}