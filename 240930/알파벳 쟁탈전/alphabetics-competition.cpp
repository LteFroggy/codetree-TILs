#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
    A, B, C중 하나의 문자를 가진다.
    조건을 위해, K번에 걸쳐서 두 학생이 같은 문자를 들고 있는지 다른 문자를 들고 있는지에 대한 정보가 주어짐

    조건을 전부 만족하며 나올 수 있는 서로 다른 가지수를 구하는 프로그램을 작성해보자.

    경로 압축을 수행하며 가능한 모든 경우의 수를 탐색해보자.
*/

int find_parent(vector<int> &parents, int child) {
    // 부모가 나 자신이 아니라면, 경로압축 수행
    if (parents[child] != child) {
        parents[child] = find_parent(parents, parents[child]);
    }

    return parents[child];
}

// 재귀를 통해 가능한 모든 조합을 찾는다.
int find_pair(string state, vector<int> &parents, vector<vector<int>> &diffs, int now) {
    // 만약 N번째 값까지 모두 정하는 데에 성공했다면, 이제 끝낸다
    if (now == parents.size()) {
        /// cout << state << endl;
        return 1;
    }

    // 그게 아니라면, 가능한 값의 경우를 구한다.
    int result = 0;

    // now번째 값을 현재 정하는 중이다!
    // 만약, now번째 값의 parents가 자기 자신이 아니라면 다른 값을 따라가야 하는 것이다!
    int parent_now = find_parent(parents, now);
    char char_now;
    if (parent_now != now) {
          char_now = state[parent_now];

          // 내가 지금 이 값을 사용했을 때, diffs(내가 달라야 하는 값들)을 보면서 문제가 없나 확인한다.
          for (auto otherValue : diffs[now]) {
            // 만약 내가 달라야 하는 값과 내 값이 같다면, 이건 종료한다.
            if (char_now == state[otherValue]) {
                return 0;
            }
          }

          // 다 확인했는데도 문제가 없다면 다음으로 진행!
          return result + find_pair(state + char_now, parents, diffs, now + 1);
    }

    // 나 자신이 parent라면, 정해진 값이 없는 것이므로 A, B, C 아무거나 해봐도 된다.
    else {
        vector<char> char_candidates = {'A', 'B', 'C'};

        // 각각 A, B, C를 하나씩 해본다.
        for (auto value : char_candidates) {
            // 내가 달라야 하는 값 목록을 확인하면서 체크한다.
            bool possible = true;
            for (auto otherValue : diffs[now]) {
                if (value == state[otherValue]) {
                    possible = false;
                    break;
                }
            }

            // 이게 가능한 값이었다면, 다음으로 진행시켜본다.
            if (possible)
                result += find_pair(state + value, parents, diffs, now + 1);
        }
    }

    // 다 진행시켜봤다면, 결과를 돌려준다
    return result;
}

int main() {
    int N, K;
    cin >> N >> K;
    // 부모
    vector<int> parents(N);
    // 각각 달라야 하는 값들 저장
    vector<vector<int>> diffs(N);

    // 부모를 다 자기 자신으로 지정해준다.
    for (int i = 0; i < N; i++) {
        parents[i] = i;
    }

    // 조건들을 받으면서 보기
    for (int i = 0; i < K; i++) {
        char condition;
        int a, b;
        cin >> condition >> a >> b;
        a--;
        b--;

        // S조건이라면, 부모를 수정
        if (condition == 'S') {
            if (a > b) 
                parents[a] = b;
            else 
                parents[b] = a;
        }   

        // D 조건이라면, diffs에 추가
        // 항상 더 뒤에 있는 값이 앞에 있는 값과 다른 조건으로 들어가야 한다. 앞에서부터 글자를 쓰면서 비교할 것이기 때문
        else {
            if (a > b) 
                diffs[a].push_back(b);
            else 
                diffs[b].push_back(a);
        }
    }

    // 확인용 출력
    /*
    for (int i = 0; i < N; i++) {
        cout << i << "번째 값이 달라야 하는 목록 : ";
        for (auto v : diffs[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
    */

    int answer = find_pair("", parents, diffs, 0);

    cout << answer << endl;
    return 0;
}