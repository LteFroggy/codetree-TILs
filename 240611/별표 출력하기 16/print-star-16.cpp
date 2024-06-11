#include <iostream>
#include <cmath>

using namespace std;

// 힌트 보고 그대로 진행
int main() {
    int N;
    cin >> N;

    // 출력용 for문
    for (int i = 0; i < N; i++) {
        // 공백 출력
        for (int k = 0; k < pow(N, 2) - pow(N - i, 2); k++) {
            cout << " ";
        } 

        // 별표 출력
        for (int k = 0; k < pow(N - i, 2); k++) {
            cout << "*";
        }
        cout << endl;
    }
    
    return 0;
}