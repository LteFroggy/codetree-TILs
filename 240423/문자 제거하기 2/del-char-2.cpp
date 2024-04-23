#include <iostream>
#include <string>

using namespace std;

int main() {
    string text;
    int N;

    cin >> text >> N;
    for (int i = 0; i < N; i++) {
        int val;
        cin >> val;

        if (val > text.size()) {
            continue;
        }
        // val - 1번 문자가 사라져야 한다. 1이면 0이 사라져야 함.
        else {
            text = text.substr(0, val - 1) + text.substr(val, text.size() - val);
            cout << text << endl;
        }
    }
    return 0;
}