#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

/*  
    모든 사람의 사용이 가능하도록 거리 최소로 하기
    중요한 것은 N번째 와이파이가 몇 명까지 커버할 것인가?

    모든 사람들의 위치의 차를 구하고, 그 제일 작은 위치의 차를 와이파이의 개수만큼 더해야 한다

    예를 들어, 1 3 5 6 7 9라면, 거리의 차는 
    2 3 1 2 1이 나올 것이다.
    최소 순으로 정렬하면 1 1 2 2 3이고, 와이파이 중계기가 총 2개에 사람이 6명이므로 제일 긴 사이 간격 하나를 제낄 수 있다.
    따라서 1 1 2 2를 모두 더한 6이 될 것

    만약 3개였다면, 큰 것 두 개를 제낄 수 있으므로 1 1 2를 더한 4가 되었을 것이다.
*/

int main() {
    int N, k;
    cin >> N >> k;

    // 사람보다 중계기가 많거나 같으면 이거 할 필요 없음
    if (N <= k) {
        cout << 0 << endl;
        return 0;
    }
    
    priority_queue<int, vector<int>, greater<>> people_list;
    priority_queue<int, vector<int>> distance_diff;

    // 사람 위치 집어넣기
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        people_list.push(tmp);
    }
    
    // 위치 차 구하기
    int front_person_loc = people_list.top();
    people_list.pop();
    while(!people_list.empty()) {
        int diff = people_list.top() - front_person_loc;
        distance_diff.push(diff);
        front_person_loc = people_list.top();
        people_list.pop();
    }
    
    // 중계기 개수 - 1만큼 제일 큰 것 빼기
    for (int i = 1; i < k; i++) {
        distance_diff.pop();
    }

    int answer = 0;
    while (!distance_diff.empty()) {
        answer += distance_diff.top();
        distance_diff.pop();
    }

    cout << answer << endl;
    return 0;
}