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



    1. 왼쪽에서의 최대값 위치와 오른쪽에서의 최대값 위치를 찾는다
    2. 서로 같다면, second_max과의 차이를 본다
    3. second_max과의 차이가 큰 쪽한테 양보해준다.
*/

int main() {
    int N;
    cin >> N;

    // i번째 값이 사용 가능한지 확인하기 위한 변수
    vector<bool> usable(N, <vector<bool>(2, true));
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
        int L_sec_max_idx = -1;
        int L_sec_max_val = 0;
        
        int R_max_idx = -1;
        int R_max_val = 0;
        int R_sec_max_idx = -1;
        int R_sec_max_val = 0;

        // 왼쪽에서 제일 큰 값 찾기
        for (int j = 0; j < N; j++) {
            // 사용 불가능한 값(반대 값이 쓰이고 있음)이면 볼 필요 없음
            if (!usable[i][0]) continue;
            
            // 현재 맥스값보다 더 큰 값을 만났다면, second_max로 값을 넘겨주고 값을 갱신한다.
            if (numbers[i][0] > L_max_val) {
                L_sec_max_val = L_max_val;
                L_sec_max_idx = L_max_idx;
                L_max_val = numbers[i][0];
                L_max_idx = i;
            }

            // 현재 맥스값보다 작다면, second 값과 비교하고 갱신한다.
            else {
                L_sec_max_idx
            }
        }
    }
    return 0;
}