#include <iostream>
#include <vector>

/*
    왼쪽 땅과 오른쪽 땅이 갈라져 있다. 강 사이에 다리를 지을 것
    왼쪽 땅 포인트 n개, 오른쪽 땅 포인트 m개 존재한다

    왼쪽에서 오른쪽으로 n개를 놓으려 한다. 포개어지지 않게 건설하려 하는데, 조건에 맞게 다리를 건설할 수 있는 경우의 수가 어떻게 될 것인가?

    그럼 각 자리마다 m - n개만큼 더 나올 듯?
*/


using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    int answer = 1;
    answer += (M - N) * N;

    cout << answer << endl;
    return 0;
}