#include <iostream>
#include <vector>

using namespace std;

/*
    길이가 n인 수열, 수열에서 원소를 맘대로 뽑아 길이가 가장 긴 오름차순 수열?
    다음 값을 보았을 때 이전 값보다 작으면서 값이 가장 큰 값을 기억하면 된다.

    가장 작은 값을 뽑았을 때 항상 가장 긴 수열이 나올까? 그건 아님.
    시작 위치를 어디로 잡느냐에 따라 다를 수 있다.

    근데 다 해봤자 1 ~ 1000 더하기이므로 그냥 하자.
*/

int main() {
    int N;
    cin >> N;
    vector<int> numbers(N);

    int max_sum = 0;
    int max_length = 0;
    int sum = 0;
    int length = 0;
    int val_before = 0;
    for (int i = 0; i < N; i++) {
        cin >> numbers[i];
    }

    // 시작 위치를 1번부터 1000번으로 하면서 가능한 최대한 긴 오름차순 수열 만들기를 해볼 것
    for (int i = 0; i < N; i++) {
        val_before = numbers[i];
        sum = numbers[i];
        length = 1;
        for (int j = i + 1; j < N; j++) {
            // 이번 숫자가 이전 숫자보다 크거나 같다면, 그대로 적용
            if (numbers[j] >= val_before) {
                val_before = numbers[j];
                sum += numbers[j];
                length++;
            }
        }

        if (max_length < length || (max_length == length && max_sum < sum)) {
            max_length = length;
            max_sum = sum;
        }
    }

     cout << max_sum << endl;
    return 0;
}