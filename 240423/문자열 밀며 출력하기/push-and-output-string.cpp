#include <iostream>
#include <string>

using namespace std;

int main() {
    string val;
    cin >> val;

    for (int i = 0; i <= val.size(); i++) {
        for (int j = 0; j < val.size(); j++) {
            cout << val[(i + j) % val.size()];
        }
        cout << endl;
    }
    return 0;
}