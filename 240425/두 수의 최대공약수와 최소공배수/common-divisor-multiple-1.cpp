#include <iostream>

using namespace std;

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
    long result = long(a > b ? b : a) * long(divided_result);
    cout << biggest_common_divisor << " " << result << endl;
    
    return 0;
}