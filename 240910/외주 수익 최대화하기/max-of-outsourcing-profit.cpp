#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int N;
    cin >> N;
    // 각 날짜가 시작한 시점의 돈을 구한다.
    // 0 ~ N + 1까지 있는데, 0일은 사용하지 않고 N+1일은 결과 용도로 사용한다.
    vector<int> profit(N + 2, 0);

    for (int i = 1; i <= N; i++) {
        // 어제 수익이 오늘 수익보다 좋다면 어제 것 그대로 사용
        profit[i] = max(profit[i], profit[i - 1]);

        // 오늘 일 입력받기
        int time, money;
        cin >> time >> money;

        // 시간이 부족하지 않은 일이라면, 해본다
        if (time + i <= N + 1) {
            profit[i + time] = max(profit[i + time], profit[i] + money);
        }
    }

    // 마지막 날에도 전날 수익이 더 좋다면 그냥 전날에서 아무것도 안하고 오는게 나음
    cout << max(profit[N], profit[N+1]) << endl;
    return 0;
}