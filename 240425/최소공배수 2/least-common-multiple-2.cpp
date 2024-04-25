#include <iostream>

using namespace std;

/*
    a, b의 최소공배수 구하기

    a, b의 최대공약수를 구한다.
    최대공약수로 둘 중 큰 쪽을 나눈다.
    나눠진 값으로 둘 중 작은 값에 곱한다.
*/

int get_biggest_divisor(int a, int b) {
    int val = a > b ? b : a;

    for (int i = val; i > 0; i--) {
        if (a % i == 0 && b % i == 0) {
            return i;
        }
    }
}

int main() {
    int a, b;
    cin >> a >> b;

    int biggest_common_divisor = get_biggest_divisor(a, b);

    int divided_result = (a > b ? a : b) / biggest_common_divisor;
    int result = (a > b ? b : a) * divided_result;
    
    cout << result << endl;
    return 0;
}