#include <iostream>
#include <vector>

using namespace std;

/*
    왼쪽 땅과 오른쪽 땅이 갈라져 있다. 강 사이에 다리를 지을 것
    왼쪽 땅 포인트 n개, 오른쪽 땅 포인트 m개 존재한다

    왼쪽에서 오른쪽으로 n개를 놓으려 한다. 포개어지지 않게 건설하려 하는데, 조건에 맞게 다리를 건설할 수 있는 경우의 수가 어떻게 될 것인가?

    그냥 M개의 다리 중 N개를 고르는 것이었다. 어차피 N개를 고르면 그에 맞게 건설하는 방법은 하나밖에 나오지 않음.
    mCn이다.

    이걸 그냥 계산하려고 하니 값이 터진다. DP를 사용하자
    nC0 = 1, nCn = 1이고,
    (n+1)C(r+1) = nCr + nC(r+1)이다.

    따라서 1C0 = 1, 1C1 = 1이고,
    2C1은 위의 둘을 더해서 2, 2C0 = 1, 2C2 = 1이다.
    3C0, 3C3은 모두 1, 3C1은 3, 3C2는 3, 이런 식으로 해나갈 수 있음.
    
*/
int main() {
    int N, M;
    cin >> N >> M;

    // DP[M][N]은 mCn을 의미한다.
    vector<vector<int>> DP(M + 1, vector<int>(M + 1, 1));

    for (int i = 2; i <= M; i++) {
        for (int j = 1; j < i; j++) {
            DP[i][j] = DP[i - 1][j] + DP[i - 1][j - 1];
        }
    }

    // for (int i = 1; i <= M; i++) {
    //     for (int j = 0; j <= i; j++) {
    //         cout << i << "C" << j << " = " << DP[i][j] << "    ";
    //     }
    //     cout << endl;
    // }

    cout << DP[M][N] << endl;
    return 0;
}