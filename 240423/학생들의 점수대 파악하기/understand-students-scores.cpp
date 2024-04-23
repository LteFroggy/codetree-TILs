#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    int bucket[11] = {0};
    
    // 입력받기
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        bucket[tmp / 10]++;
    }

    // 출력하기
    for (int i = 10; i > 0; i--) {
        if (bucket[i] != 0)
            cout << i * 10 << " - " << bucket[i] << endl;
    }
    return 0;
}