#include <iostream>

using namespace std;

/*
    길이가 n인 수열, 수열에서 원소를 뽑아 길이가 가장 긴 오름차순 수열?
    다음 값을 보았을 때 이전 값보다 작으면서 값이 가장 큰 값을 기억하면 된다.
*/

int main() {
    int N;
    cin >> N;

    int max_sum = 0;
    int max_length = 0;
    int sum = 0;
    int length = 0;
    int val_before = 0;
    for (int i = 0; i < N; i++) {
        int val_now;
        cin >> val_now;
        // 이번 값이 이전 값보다 크거나 같다면 오름차순 맞으므로 length 추가하고, sum 더해주기
        if (val_now >= val_before) {
            length++;
            sum += val_now;
            val_before = val_now;
        }

        // 이번 값이 이전 값보다 작거나, 마지막 원소라면 값 정리해주기
        if (val_now < val_before || i == N-1) {
            // 더 긴 수열을 찾았거나, 길이는 같으나 합이 더 큰 경우 max 갱신
            if (max_length < length || (max_length == length && max_sum < sum)) {
                max_length = length;
                max_sum = sum;
            }

            // 변수 초기화
            val_before = val_now;
            length = 1;
            sum = val_now;
        }
    }

    cout << max_sum << endl;
    return 0;
}