#include <iostream>

using namespace std;

long mul_recur(int a, int b) {
    if (b == 1)
        return a;
    else 
        return a * mul_recur(a, b - 1);
}

int main() {
    int a, b;
    cin >> a >> b;
    
    cout << mul_recur(a, b) << endl;
    return 0;
}