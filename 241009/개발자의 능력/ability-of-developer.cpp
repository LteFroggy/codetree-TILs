#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;

/*
    12명의 알고리즘을 수치화해 3팀씩 4팀으로 배정해준다.
    능력 총합이 가장 클 때와 가장 작을 때를 최소화하기 위한 방법을 생각하고, 그 결과(가장 높은 팀과 가장 적은 팀의 차)를 출력하자.

    차이를 가장 적게 만들기 위한 방법은, 일단 수치를 큰 순으로 나열하고 값이 가장 작은 팀에 넣어줘보기
    혹은 그냥 Backtracking으로 다 해보기
*/

int min_differences = 1e9;

void backTrack(vector<int> &developers, vector<stack<int>> &teams, int index) {
    // 개발자들을 모두 입력했으면, 차이를 계산한다
    if (index == 12) {
        int min_val = 1e9;
        int max_val = 0;

        // cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        // cout << "배정 완료" << endl;


        for (auto team : teams) {
            int sum = 0;
            stack<int> tmp = team;
            while (!tmp.empty()) {
                sum += tmp.top();
                tmp.pop();
            }

            if (sum < min_val) {
                min_val = sum;
            }

            if (sum > max_val) {
                max_val = sum;
            }

            // cout << "팀 점수 합계 : "  << sum << endl;
        }

        min_differences = min(min_differences, max_val - min_val);
        return;
    }

    // 아직 더 입력해야 한다면, backtracking을 진행한다.
    // 이번 개발자를 가능한 모든 팀에 다 넣어본다
    for (int i = 0; i < 4; i++) {
        // 대신, 사이즈는 맞아야 함
        if (teams[i].size() < 3) {
            teams[i].push(developers[index]);
            backTrack(developers, teams, index + 1);
            teams[i].pop();
        }
    }

    return;
}

int main() {
    vector<int> developers(12, 0);

    // 개발자 정보 받기
    for (int i = 0; i < 12; i++) {
        cin >> developers[i];
    }

    vector<stack<int>> teams(4);

    // BackTracking
    backTrack(developers, teams, 0);

    cout << min_differences << endl;
    return 0;
}