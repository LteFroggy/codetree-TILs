#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    N이 주어지면 1번부터 N번까지 번호순 사진 찍을 것
    연달아 있는 번호는 한번에 찍을 수 있지만, 사이가 안 좋은 학생은 같이 찍히면 안된다
    모든 학생을 찍기 위해 몇 번 찍어야 할까?

    학생은 최대 10억명이니, 하나하나 찍기는 좀 그렇다.
    간단하게 생각하면, 먼저 같이 찍기 싫어하는 애들 사이로 다 찍으면 되는게 아닌가? 
    ex ) 7명
    1, 3
    2, 4
    5, 6

    일단 a < b가 되도록 정렬
    그리고 뒷 값이 작은 순으로 정렬

    그리고 나서는 각 a, b를 보면서, a가 이번 사진 찍는 대상인가? 확인
    아니라면, b를 고려할 필요 없음 -> 종료 기준으로 정렬한 회의실 문제 같은 것
*/

bool compare(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<pair<int, int>> hate;

    // 더 작은 값이 앞에 위치하도록 a, b정렬
    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;

        a > b ? hate.push_back({b, a}) : hate.push_back({a, b});
    }

    sort(hate.begin(), hate.end(), compare);

    int answer(0);
    int start = 1;
    for (auto v : hate) {
        // 이제 각각의 값을 체크하며 사진을 찍어야 하는지 확인

        // 지금 서로 싫어하는 애들 중에 한명이 사진에 포함되는가? (더 번호가 작은 친구)
        // 그렇다면, 싫어하는 나머지 한명이 포함되기 직전까지만 해서 사진을 한장 찍어줘야 한다
        if (start <= v.first) {
            start = v.second;
            answer++;
        }

        // 둘중에 한명이 사진에 포함 안되면? 이 그룹(싫어하는 서로)는 고려해 줄 필요 없음
        else {
            continue;
        }
    }
    
    // 서로 사이 안 좋은 애들 다 고려헀으면, 마지막 팀 한장 찍어주고 끝!
    answer++;

    cout << answer << endl;
    return 0;
}