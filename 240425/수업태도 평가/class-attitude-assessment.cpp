#include <iostream>
#include <array>
#include <map>
#include <string>
#include <queue>

using namespace std;

/*
    7명의 학생이 고정으로 있다.

    학생에게 점수를 주고, 점수는 합산된다
    밑에서 두 번째 점수를 가진 학생의 이름을 출력하면 되는데, 꼴찌가 여러 명이라면 꼴찌 바로 다음 점수를 가진 학생을 출력하고,
    두 번째로 낮은 점수를 가지는 학생이 여러 명이거나, 같다면 Tie를 출력한다.

    MAP을 이용하여 학생들의 점수를 합산하고, prioirty_queue<pair<string,int>>로 뽑아내서 구하자.
*/

struct cmp {
    bool operator()(pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    }
};

int main() {
    array<string, 7> names = {"Bessie", "Elsie", "Daisy", "Gertie", "Annabelle", "Maggie", "Henrietta"};
    
    map<string, int> class_score;

    for (int i = 0; i < names.size(); i++) {
        class_score.insert({names[i], 0});
    }

    int N;
    cin >> N;

    // 점수 합산하기
    for (int i = 0; i < N; i++) {
        string name;
        int score;
        cin >> name >> score;
        class_score[name] += score;
    }

/*
    for(auto i = class_score.begin(); i != class_score.end(); i++) {
        cout << i->first << " : " << i->second << endl;
    }
*/
    // prioirty queue에 집어넣기
    priority_queue<pair<string, int>, vector<pair<string, int>>, cmp> que;
    for (int i = 0; i < 7; i++) {
        que.push(make_pair(names[i], class_score[names[i]]));
    }

    // 제일 작은 값인 사람 뺴기
    int min_score = que.top().second;
    que.pop();
    // 제일 작은 값이 여러 명일 수 있으므로, 다 빼주기
    while (que.top().second == min_score) {
        que.pop();
    }

    // 두번째로 작은 사람이 누군지 저장하고, 같은 값을 가진 사람이 있다면 Tie출력, 아니라면 그 사람 출력
    int second_min_score = que.top().second;
    string second_min_name = que.top().first;
    que.pop();
    if (que.size() != 0 && que.top().second == second_min_score) {
        cout << "Tie" << endl;
        return 0;
    }
    cout << second_min_name << endl;
    
    return 0;
}