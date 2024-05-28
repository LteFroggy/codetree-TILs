#include <iostream>
#include <vector>

using namespace std;

/*
    왼쪽 땅과 오른쪽 땅이 갈라져 있다. 강 사이에 다리를 지을 것
    왼쪽 땅 포인트 n개, 오른쪽 땅 포인트 m개 존재한다

    왼쪽에서 오른쪽으로 n개를 놓으려 한다. 포개어지지 않게 건설하려 하는데, 조건에 맞게 다리를 건설할 수 있는 경우의 수가 어떻게 될 것인가?

    그냥 M개의 다리 중 N개를 고르는 것이었다. 어차피 N개를 고르면 그에 맞게 건설하는 방법은 하나밖에 나오지 않음.
    mCn이다.
*/
int main() {
    long long N, M;
    cin >> N >> M;
    long long answer = 1;

    for (int i = M; i > N; i--) {
        // cout << answer << " * " << i << " = ";
        answer *= i;
        // cout << answer << endl;
    }
    for (int i = 2; i <= M - N; i++) {
        // cout << answer << " / " << i << " = ";
        answer /= i;
        // cout << answer << endl;
    }

    cout << answer << endl;
    return 0;
}