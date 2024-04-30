#include <iostream>
#include <string>

using namespace std;

/*
    모든 문자열을 이어붙이고, 길이를 2등분해서 출력한다.
*/


int main() {
    int N;
    cin >> N;

    string all_str = "";

    for (int i = 0; i < N; i++) {
        string tmp;
        cin >> tmp;
        all_str += tmp;
    }

    // 나눠서 출력하기
    string str_a = all_str.substr(0, all_str.size() / 2);
    string str_b = all_str.substr(all_str.size() / 2, all_str.size() / 2);

    cout << str_a << endl;
    cout << str_b << endl;
    return 0;
}