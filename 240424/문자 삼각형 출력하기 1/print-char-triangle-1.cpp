#include <iostream>
#include <vector>

using namespace std;

/*
    문자를 삼각형으로 출력
        1
      2 4
    3 5 6
            1
          2 5 
        3 6 8
      4 7 9 10
    처럼 출력해야 한다.

    일단 j + i >= N - 1부터 출력을 수행해야 한다.
    그리고 i, i + N-1, i + N-2를 출력하면 됨.
*/

int main() {
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int val = i;
        int variable = 1;
        for (int j = 0; j < N; j++) {
            if (i + j >= N - 1) {
                cout << char((val % 26) + 'A') << " ";
                val += (N - variable);
                variable++;
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    return 0;
}