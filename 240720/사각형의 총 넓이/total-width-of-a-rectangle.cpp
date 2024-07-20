#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

/*
    N개의 직사각형이 만들어내는 총 넓이 구하기
    x, y모두 범위가 20000이므로 총 넓이가 4 x 10^8이라 모든 칸을 확인하는 방법은 사용 불가능하다.

    차원이 하나였다면, x의 시작 범위 순으로 정렬해서 다음 시작 범위가 이번 끝 안에 들어오는지 체크했을 것이다.

    A, B, C순으로 정렬되었다고 할 때,
    1. A의 넓이는 그대로 Answer에 저장한다.
    2. B를 본다 {
        1. A의 x축 끝값이 B의 시작값보다 작은 값인 경우 -> 둘이 겹칠 일이 없는 것이므로, B의 넓이를 계산해서 Answer에 더한다

        2. A의 x축 끝값이 B의 시작값보다 큰 값인 경우 -> 둘의 x좌표가 일부 겹치는 것이다. y범위에 대해서도 검사를 실행한다
            2-1. 둘의 y범위가 겹치지 않는 경우 (B.y.start < B.y.end < A.y.start || A.y.end < B.y.start < B.y.end)
                 A와 B는 겹치지 않는 것이므로 B의 넓이를 계산해서 Answer에 더한다.

            2-2. 둘의 y범위가 겹치는 경우 (B.y.start < A.y.start < B.y.end || B.y.start < A.y.end < B.y.end)
                 겹치지 않는 y값의 크기를 구하고, (겹치지 않는 y값) x (겹치는 x값) + (y값) x (겹치지 않는 x값)으로 값을 구해 B를 더한다.

            2-3. B의 y범위가 A의 y범위에 포함되는 경우 (A.y.start <= B.y.start < B.y.end <= A.y.end)
                 A와 B의 겹치는 x값에 대해서는 계산하지 않고, 겹치지 않는 x값에 대한 부분만 구한다.

            2-4. A의 y범위가 B의 y범위에 포함되는 경우 (B.y.start <= A.y.start < A.y.end <= B.y.end)
                 겹치는 x값 부분에서는 (A.y.start - B.y.start) + (B.y.end - A.y.end)를 곱해서 구해주고, 나머지는 그대로 구한다.
        }
    3. A -> B, B -> C로 바꿔서 2를 반복한다.
    @@@@ 위의 방법 잘 되지 않는다. 한 공간에 3개 이상의 사각형이 생기면 정신을 못 차림

    채치피티가 다른 방법을 안내해주었다.
    1. 가로축(x축)을 따라 스캔할 것이다.
    2. 어떤 사각형을 입력받으면, x축의 시작부분에 시작 이벤트를, x축의 끝부분에 끝 이벤트를 만든다. 이벤트에는 x축 값, y범위, 시작종료여부가 포함된다
        2-1. 예를 들어, 1,1 ~ 5,5의 사각형을 받으면, 시작 x값인 1에 (1, 1, 5, 1)로 시작 이벤트를 만든다
        2-2. 그리고 (5, 1, 5, -1)로 종료 이벤트를 만든다. 
        2-3. 시작 이벤트에서 그물을 펼치고, 종료 이벤트에서 그물을 접는다고 생각하면 된다. 약간 누적합 느낌?
    3. 현재 펼쳐져있는 범위들을 고려하며 값의 합을 구한다.
*/
typedef pair<int, int> range;

// 각 Event에 값이 4개나 되어서, vector<int>로 그냥 사용하기엔 너무 코드가 이해하기 어려워 질 것 같아 Class로 생성
class Event {
public :
    // 값을 초기화해주는 생성자
    Event(int x_loc, int y_start, int y_end, bool is_start)
    : xLoc(x_loc), yStart(y_start), yEnd(y_end), isStart(is_start) {};

    int xLoc;
    int yStart;
    int yEnd;
    bool isStart;
};

// Event들을 xLoc기준으로 정렬하기 위한 static 구조체
struct event_compare {
    bool operator()(Event a, Event b) {
        return a.xLoc > b.xLoc;
    }
};

// 범위 정렬에 있어 시작 값 기준으로 오름차순 정렬에 사용하기 위한 함수
bool range_compare(range a, range b) {
    return a.first < b.first;
}

int main() {
    int N;
    cin >> N;

    priority_queue<Event, vector<Event>, event_compare> Events;
    // 먼저 사각형들을 받고, 이벤트를 만들어서 proiority_queue에 넣는다
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;

        // y1 < y2 조건을 만족시키기 위해 입력받는 순서를 바꾸었다.
        cin >> x1 >> y2 >> x2 >> y1;
        
        // 시작 이벤트, 종료 이벤트를 만들어서 Priority_queue에 집어넣는다.
        Events.push(Event(x1, y1, y2, true));
        Events.push(Event(x2, y1, y2, false));
    }

    long answer(0);
    // Queue가 빌 때까지 Event를 보면서 넓이의 총합을 구할 것이다.
    vector<range> ranges;
    while (true) {
        int xLoc = Events.top().xLoc;
        int yStart = Events.top().yStart;
        int yEnd = Events.top().yEnd;
        bool isStart = Events.top().isStart;
        Events.pop();
        // cout << "이벤트 : " << xLoc << ", " << yStart << ", " << yEnd << ", " << isStart << endl;

        // 지금 받은 값이 이벤트의 시작이라면, ranges에 값을 집어넣는다.
        if (isStart) {
            ranges.push_back({yStart, yEnd});
        }

        // 시작이 아니라면, ranges에서 값을 삭제한다
        else {
            for (auto iter = ranges.begin(); iter != ranges.end(); iter++) {
                if (iter->first == yStart && iter->second == yEnd) {
                    ranges.erase(iter);
                    break;
                }
            }
        }

        // cout << "현재 Range 목록 : ";
        // for (auto range : ranges)
        //     cout << "(" << range.first << ", " << range.second << "), ";
        // cout << endl;

        // 다음 이벤트가 없으면, while문이 끝난다.
        if (Events.empty()) {
            break;
        }

        // 다음 이벤트까지는 이 범위를 그대로 유지할 것이다.
        // 따라서 겹침을 고려한 총 넓이를 구한다.
        int y_range(0);

        // 계산을 위해 시작 값 기준으로 범위를 정렬
        sort(ranges.begin(), ranges.end(), range_compare);


        // cout << "계산된 Range : ";

        // 범위(y_range)를 계산한다
        int y_start(-1), y_end(-1);
        for (auto range_now = ranges.begin(); range_now != ranges.end(); range_now++) {
            // 첫 값은 그냥 start,end에 대입한다.
            if (y_start == -1 && y_end == -1) {
                y_start = range_now->first;
                y_end = range_now->second;
            }

            // 이번이 마지막 값이라면, 다음 범위가 없을 것이므로 지금의 범위를 y_range에 더한다
            if (range_now == ranges.end() - 1) {
                // cout << "(" << y_start << ", " << y_end << "), ";
                y_range += y_end - y_start;
            }
            
            // 다음 범위를 보았을 때, (다음 start) <= (현재 end)라면 둘의 범위가 겹치는 것이다.
            else if (range_now->first <= y_end) {
                // (다음 end) < (현재 end)라서 아예 다음 범위가 이번 범위에 포함되는 경우
                // 이 경우에는 범위를 따로 수정할 필요 없다. 그대로 놔두기
                if (range_now->second <= y_end) {}
                
                // (현재 end) < (다음 end)라서 범위가 오른쪽으로 조금 더 넓어져야 하는 경우에는 늘려준다
                else {
                    y_end = range_now->second;
                }
            }

            // (현재 end) < (다음 start)를 만족하여 다음 범위가 아예 이번 범위랑 연관조차 없는 경우 
            // 현재 start, end를 통해 범위의 크기를 계산하고 다음 값을 받는다
            else {
                // cout << "(" << y_start << ", " << y_end << "), ";
                y_range += y_end - y_start;
                y_start = range_now->first;
                y_end = range_now->second;
            }
        }

        // cout << endl;

        // 범위 * x길이 로 넓이를 계산한다.
        int next_xLoc = Events.top().xLoc;
        answer += (next_xLoc - xLoc) * y_range;
        // cout << "answer = " << answer << endl << endl;
    }
    

    cout << answer << endl;
    return 0;
}