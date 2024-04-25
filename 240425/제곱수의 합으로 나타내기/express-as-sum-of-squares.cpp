#include <iostream>
#include <queue>
#include <cmath>
#include <array>

using namespace std;

/*
    모든 수는 넷 혹은 그 이하의 제곱수의 합으로 표현 가능하다.
    자연수 n이 주어졌을 때, 최소 개수의 제곱수 합으로 표현하기 위한 최소 제곱수를 구하는 프로그램 작성해보자.

    sqrt(N)을 수행하고, pow(floor(N), 2)을 계속 해서 0이 될때까지 하면 된다. -> X, 최소를 구하지 못한다

    DP로 접근해보자. 각 수까지 오는 데에 최소 횟수를 저장하면 됨
    queue<pair<int, int>>를 사용할 것.
*/



int main() {
    int N;
    cin >> N;
    int count = 0;
    queue<pair<int, int>> dp;
    dp.push(make_pair(N, 0));
    int answer = 5;

    while (!dp.empty()) {
        int val_now = dp.front().first;
        int count_now = dp.front().second;
        dp.pop();

        int max = floor(sqrt(N));
        // max 이하의 수를 전부 빼보기
        for (int i = max; i > 0; i--) {
            int val_next = val_now - pow(i, 2);
            
            // 값이 0이 되면 저장하고, 그만 보기(이 값에서 이것보다 더 적은 수의 합으로 표현할 수는 없음)
            if (val_next == 0) {
                if (answer > count_now + 1) {
                    answer = count_now + 1;
                }
                break;
            }

            // 이미 4개째 수의 합이라면, 그만 봐도 된다. 모든 수는 4개 이하의 제곱수의 합으로 표현이 가능하다고 했음.
            if (count_now != 3)  {
                dp.push(make_pair(val_next, count_now + 1));
            }
        }
    }
    

    cout << answer << endl;
    return 0;
}