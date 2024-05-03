#include <iostream>

using namespace std;

bool isSosu(int num) {
    if (num == 1)
        return false;
    for (int i = 2; i < num - 1; i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int N;
    cin >> N;

    int count = 0;

    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        if (isSosu(tmp)) count++;
    }

    cout << count << endl;
    return 0;
}