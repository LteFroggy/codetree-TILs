#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool sorting_method(vector<int> a, vector<int> b) {
    int i = 0;
    while (true) {
        if (a[i] == b[i]) {
            i++;
        }
        else {
            return a[i] < b[i];
        }
    }
}

/*
    주사위를 N번 굴려 M이 나오는 모든 경우를 오름차순으로 출력
    1 ~ 6까지의 수가 모두 가능하고, M보다 커지면 그만 굴리면 된다
    가능한 조합을 2차원 벡터로 저장해주면 됨
*/

vector<vector<int>> vec;

void rollDice(int count, vector<int> values, int sum, int target) {
    // count가 0이 되면 끝이다.
    if (count == 0) {
        if (sum == target) {
            vec.push_back(values);
        }
        return;
    }

    // 이번에 굴렸을 경우에 1 ~ 6이 나올 모든 상황을 고려해 다음으로 넘긴다.
    for (int i = 1; i < 7; i++) {
        vector<int> values_tmp = values;
        values_tmp.push_back(i);
        if (sum + i <= target) {
            rollDice(count - 1, values_tmp, (sum + i), target);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    
    rollDice(N, vector<int>(), 0, M);
    sort(vec.begin(), vec.end(), sorting_method);
    
    for (auto v : vec) {
        for (auto v_ : v) {
            cout << v_ << " ";
        }
        cout << endl;
    }

    
    return 0;
}