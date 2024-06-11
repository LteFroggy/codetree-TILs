#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    1부터 N까지의 정수를 쓸 것. 1부터 N까지의 번호가 붙어있는 n개의 칸에 쓸 것이다.
    정수는 최대 자기 번호와 1 차이 나는 곳에만 쓰일 수 있다.
    m개의 고정칸이 정해져 있고, 고정칸에는 같은 수만 쓰일 수 있다.
    
    정수를 배치하는 경우의 수를 구하는 방법이 어떻게 될까?

    뭐가 하나 추가될 때 마다 경우의 수가 너무 많아지므로, DP로 가자
    i가 고정값이 아닌 경우에, 
    DP[i] = DP[i - 2] * 2이다. 
    2개를 정순으로 배열하거나, 역순으로 배열할 수 있기 때문

    고정값인 경우에, DP[i] = DP[i - 2]이다. 고정값이면 순서가 바뀔 수 없기 때문

    각 행에서는 바로 전열에서 값 그대로 붙이기, 2열 전에 값에 대해 값 뒤집기가 가능하다.
    그런데 고정값이라면, 전열에서 값 그대로 붙이기만 가능하다.

    X
    
    1

    1 2

    1 2 3
    1 3 2

    1 2 3 4
    1 3 2 4

    1 2 3 4 5
    1 3 2 4 5
*/

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> fixed(M);
    vector<int> DP(N + 2, 0);
    for (int i = 0; i < M; i++) {
        cin >> fixed[i];
    }

    // 고정값을 작은 값 순으로 소팅한다
    sort(fixed.begin(), fixed.end());

    // for (auto v : fixed) cout << v << " ";
    // cout << endl;


    // DP 진행
    int fixed_idx = 0;
    DP[0] = 1;
    DP[1] = 1;

    bool flag = false;
    for (int i = 1; i <= N; i++) {
        // 이번 위치가 고정값이라면, 값 뒤집기가 불가능하므로 1열 전의 값을 그대로 쓴다.
        // 이 다음 위치 역시 값 뒤집기가 안되므로, 1열 전의 값을 그대로 써야 한다. 이를 위해 Flag변수를 사용한다.
        // 그리고 고정값 확인용 Index를 늘린다.
        if (i == fixed[fixed_idx]) {
            DP[i] = DP[i - 1];
            flag = true;
            fixed_idx++;
        }

        // 고정값 바로 다음 값도 뒤집기가 안 되므로 이어서 써야 한다.
        else if (flag) {
            DP[i] = DP[i - 1];
            flag = false;
        }

        // 고정값이 아니라면, 2열 전의 값에 뒤집어 붙이기 + 이전 열의 값에 이어붙이기가 가능하다.
        else {
            DP[i] = DP[i - 2] + DP[i - 1];
        }
    }

    cout << DP[N] << endl;

    for (int i = 1; i <= N; i++) {
        cout << "DP[" << i << "] = " << DP[i] << endl;
    }
    return 0;
}