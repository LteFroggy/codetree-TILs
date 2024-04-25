#include <iostream>
#include <cmath>

using namespace std;

/*
    모든 수는 넷 혹은 그 이하의 제곱수의 합으로 표현 가능하다.
    자연수 n이 주어졌을 때, 최소 개수의 제곱수 합으로 표현하기 위한 최소 제곱수를 구하는 프로그램 작성해보자.

    sqrt(N)을 수행하고, pow(floor(N), 2)을 계속 해서 0이 될때까지 하면 된다.
*/

int main() {
    int N;
    cin >> N;
    int count = 0;
    while (N != 0 && count++) {
        int value = floor(sqrt(N));
        N -= pow(value, 2);
    }
    

    cout << count << endl;
    return 0;
}