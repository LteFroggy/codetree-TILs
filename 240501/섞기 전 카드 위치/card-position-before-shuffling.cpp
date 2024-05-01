#include <iostream>
#include <vector>

using namespace std;

/*
    1 ~ N까지의 숫자가 한번씩만 적힌 수열이 주어지고, N개의 카드를 주어진 수열에 따라 섞는것을 3번 반복한 이후의 카드 상태가 주어진다.

    같은 방법으로 3번 섞을 것이니, 푸는 것을 3번 반복하면 된다
    25412이면, 첫 카드가 2번 자리로, 두번째 카드가 5번 자리로, 이런 것
*/
int main() {
    int N;
    cin >> N;

    vector<int> order(N);
    // 순서 받기
    for (int i = 0; i < N; i++) {
        cin >> order[i];
        order[i]--;
    }   


    vector<int> beforeShuffle(N);
    vector<int> afterShuffle(N);

    for (int i = 0; i < N; i++) {
        cin >> afterShuffle[i];
    }

    // 3번 뒤로 돌리기
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            beforeShuffle[j] = afterShuffle[order[j]];
        }
        afterShuffle = beforeShuffle;
    }

    for (auto v : afterShuffle) {
        cout << v << endl;
    }
    return 0;
}