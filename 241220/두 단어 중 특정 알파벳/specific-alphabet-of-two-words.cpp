#include <iostream>
#include <vector>
using namespace std;

/*
    단어 2개로 이루어진 묶음이 N번 주어진다
    두 단어들 중 한 단어만 선택해 나오는 경우의 수 중, 각 알파벳별로 최대 몇 번씩 나오는지 보자?

    그냥 각 단어 내에 특정 문자가 몇 번 나오는지 다 체크하면 됨

    총 경우의 수는 2^10
    각 경우의 수 별로 최대 등장 횟수만 꼬시면 되는 것 아닌가?.. 약간 DP느낌

    각 단어를 보고 알파벳별 등장횟수를 a, b별로 구한다.
    그 전 값에 더 큰 값을 더해준다.
*/

int main() {
    int N;
    cin >> N;

    vector<int> count_max(26, 0);
    vector<int> count_forward(26, 0);
    vector<int> count_backward(26, 0);

    for (int i = 0; i < N; i++) {
        // 일단 두 단어 입력받기
        string a, b;
        cin >> a >> b;

        // 두 단어 내에 등장하는 알파벳들을 보고, count_forward와 count_backward 구해주기
        for (auto v : a) {
            count_forward[v - 'a']++;
        }

        for (auto v : b) {
            count_backward[v - 'a']++;
        }

        // 결과가 나왔다면, count_max에 이를 적용해준다
        for (int j = 0; j < 26; j++) {
            count_max[j] += max(count_forward[j], count_backward[j]);
        }
        
        // 초기화하고, 다음 사이클 가기
        count_forward = vector<int>(26, 0);
        count_backward = vector<int>(26, 0);
    }

    // 마지막엔 count_max를 다 출력해주면 된다
    for (auto v : count_max) cout << v << endl;
    return 0;
}