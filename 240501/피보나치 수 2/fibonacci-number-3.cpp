#include <iostream>
#include <vector>

/*
    n번째 피보나치 구하기
    재귀로 하자. 아니면 dp
    이번엔 dp 시도해보기
*/

using namespace std;

int main() {
    vector<int> fibonacci;
    fibonacci.push_back(0);
    fibonacci.push_back(1);

    int N;
    cin >> N;

    for (int i = 2; i < N + 1; i++) {
        if (i == N) {
            cout << (fibonacci[i - 1] + fibonacci[i - 2]) % 1000000007;
        }

        else {
            fibonacci.push_back((fibonacci[i-1] + fibonacci[i-2]) % 1000000007);
        }
    }

    return 0;
}