#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
    N명의 개발자에게 번호가 부여된다. 위치는 정해야함
    각 개발자는 친한 개발자를 3명씩 가지고, 진한 개발자끼리는 줄을 쥐고 있는데, 줄 길이는 모든 개발자들이 일렬로 섰을 때의
    나와 친한 개발자와의 거리이다.
    각 개발자에 대해 친한 3명의 번호가 주어졌을 떄, 서있는 순서를 결정해서 줄의 길이의 합이 최소가 되도록 하자.

    그때그때 사람이 추가되면, 추가된 사람이 원래 있는 사람과의 거리를 계산하고, 값이 넘어가면 중단한다.
*/

void backTrack(int index, int length, vector<bool> &inRow, const vector<vector<int>> &friends, unordered_map<int, int> &loc, int &answer);

int main() {    
    int answer(1e9);
    int N;
    cin >> N;

    // 서로 친한 개발자를 입력받는다.
    vector<vector<int>> friends(N, vector<int>(3));

    // 일단, 친한 사람 목록을 받는다.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            int tmp;
            cin >> tmp;
            // 1을 빼고 넣는 이유는, 개발자 idx가 1번부터 시작해서..
            friends[i][j] = tmp - 1;
        }
    }
    // 필요한 변수 만들기
    unordered_map<int, int> loc;
    vector<bool> inRow(N, false);

    // BackTracking 실시
    backTrack(0, 0, inRow, friends, loc, answer);

    cout << answer << endl;
    return 0;
}

/*
    int index                   이번에 넣을자리
    int length                  지금까지의 줄의 길이
    vector<bool> inRow          각 개발자가 이미 줄을 섰나?
    vector<vector<int>> friends 각각의 친한 개발자
    unordered_map<int, int> loc 각 개발자가 서있는 자리
    int answer                  지금까지 제일 짧은 거리
*/
void backTrack(int index, int length, vector<bool> &inRow, const vector<vector<int>> &friends, unordered_map<int, int> &loc, int &answer) {
    // 주어진 개발자들이 모두 줄을 잘 섰다면, 이 값을 기록한다.
    if (index == friends.size()) {
        /*
        for (auto iter = loc.begin(); iter != loc.end(); iter++) {
            cout << iter->first + 1 << " 번은 " << iter->second + 1<< "번째 자리에 서 있음" << endl;
        }

        cout << "이 경우에 길이 " << length << "로 갱신됨" << endl;
        */
        answer = length;
        return;
    }

    // 다 못 섰다면, idx번 자리에 올 개발자를 정한다
    for (int i = 0; i < friends.size(); i++) {
        // 이미 선 개발자면, 얘는 세우지 않는다.
        if (inRow[i]) continue;
        
        // 아직 서지 않은 개발자면, 이 자리에 이 사람을 세워본다.
        inRow[i] = true;
        loc.insert({i, index});
        int length_new = length;

        // 그에 따라 새로 있는 줄의 길이를 구해본다.
        for (auto person : friends[i]) {
            // 이미 서 있는 사람에 대한 길이만 구할 것!
            if (inRow[person]) {
                // "현재 자리 - 그 사람의 자리" 계산해서 answer에 더해주기
                length_new += index - loc[person];
            }
        }

        // 지금의 length가 answer보다 짧다면, 다음 idx로 보내본다
        if (length_new < answer) {
            backTrack(index + 1, length_new, inRow, friends, loc, answer);
        }

        // 보낸 후에는, 다시 inRow와 loc을 초기화해준다
        inRow[i] = false;
        loc.erase(i);
    }
}