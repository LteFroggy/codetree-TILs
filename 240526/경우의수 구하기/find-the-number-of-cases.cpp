#include <iostream>
#include <vector>

/*
    왼쪽 땅과 오른쪽 땅이 갈라져 있다. 강 사이에 다리를 지을 것
    왼쪽 땅 포인트 n개, 오른쪽 땅 포인트 m개 존재한다

    왼쪽에서 오른쪽으로 n개를 놓으려 한다. 포개어지지 않게 건설하려 하는데, 조건에 맞게 다리를 건설할 수 있는 경우의 수가 어떻게 될 것인가?

    DP느낌으로 가야 할 것 같다.
*/

int answer = 0;

// 다리 개수를 세어주는 재귀함수
void getBridgeCount(int N, int now_idx, int left_spaces) {
    // 마지막 다리라면, 하나의 경우가 완성된 것이므로 1 더해주고 끝내기
    if (N == now_idx) answer++;
    
    // 다리 여분 개수에 따라 함수 재귀로 추가하기
    for (int i = left_spaces; i >= 1; i--) {
        getBridgeCount(N, now_idx + 1, i);
    }

    // 다리 여분이 없는 경우에는 남는 경우의 수가 하나이므로 그냥 answer에 더하기
    answer++;
}

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    getBridgeCount(N, 1, M - N);
    cout << answer << endl;
    return 0;
}