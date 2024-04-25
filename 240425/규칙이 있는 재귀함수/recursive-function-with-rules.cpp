#include <iostream>
#include <vector>

using namespace std;

/*
    첫 수는 2이고, 나머지 수는 t/2번째 수와 t-1번째 수의 합이다.
*/

int main() {
    int N;
    cin >> N;

    vector<int> fun(N + 1, 2);
    cout << 2 << " ";
    for (int i = 2; i <= N; i++) {
        fun[i] = fun[i / 2] + fun[i - 1];
        cout << fun[i] << " ";
    }
    cout << endl;

    return 0;
}