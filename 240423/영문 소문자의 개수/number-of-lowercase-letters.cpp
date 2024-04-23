#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    int small_count[26] = {0};

    for (int i = 0; i < N; i++) {
        char val;
        cin >> val;

        if (val >= 'a' && val <= 'z') {
            small_count[val - 'a']++;
        }
        else {
            for (int j = 0; j < 26; j++) {
                if (!small_count[j] == 0) {
                    cout << char(j + 'a') << " : " << small_count[j] << endl;
                }
            }
            break;
        }
    }

    return 0;
}