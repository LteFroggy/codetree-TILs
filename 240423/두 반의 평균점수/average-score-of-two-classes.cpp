#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> score(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> score[i];
    }

    int a, b;
    cin >> a >> b;

    double answer = double(score[a] + score[b]) / 2;
    answer *= 10;
    answer = round(answer);
    answer /= 10;

    cout << fixed;
    cout.precision(1);
    cout << answer << endl;
    return 0;
}