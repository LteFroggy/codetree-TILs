#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

/*
    N개의 직사각형이 만들어내는 총 넓이 구하기
    x, y모두 범위가 20000이므로 총 넓이가 4 x 10^8이라 모든 칸을 확인하는 방법은 사용 불가능하다.

    차원이 하나였다면, x의 시작 범위 순으로 정렬해서 다음 시작 범위가 이번 끝 안에 들어오는지 체크했을 것이다.

    A, B, C순으로 정렬되었다고 할 때,
    1. A의 넓이를 구해 Answer에 더한다.
    2. B를 본다 {
        1. A의 x축 끝값이 B의 시작값보다 작은 값인 경우 -> 둘이 겹칠 일이 없는 것이므로, B의 넓이를 계산해서 Answer에 더한다

        2. A의 x축 끝값이 B의 시작값보다 큰 값인 경우 -> 둘의 x좌표가 일부 겹치는 것이다. y범위에 대해서도 검사를 실행한다
            2-1. 둘의 y범위가 겹치지 않는 경우 (B.y.start < B.y.end < A.y.start || A.y.end < B.y.start < B.y.end)
                 A와 B는 겹치지 않는 것이므로 B의 넓이를 계산해서 Answer에 더한다.

            2-2. 둘의 y범위가 겹치는 경우 (B.y.start < A.y.start < B.y.end || B.y.start < A.y.end < B.y.end)
                 겹치지 않는 y값의 크기를 구하고, (겹치지 않는 y값) x (겹치는 x값) + (y값) x (겹치지 않는 x값)으로 B를 구한 후에 Answer에 더한다.

            2-3. B의 y범위가 A의 y범위에 포함되는 경우 (A.y.start <= B.y.start < B.y.end <= A.y.end)
                 A와 B의 겹치는 x값에 대해서는 계산하지 않고, 겹치지 않는 x값에 대한 부분만 구한다.

            2-4. A의 y범위가 B의 y범위에 포함되는 경우 (B.y.start <= A.y.start < A.y.end <= B.y.end)
                 겹치는 x값 부분에서는 (A.y.start - B.y.start) + (B.y.end - A.y.end)를 곱해서 구해주고, 나머지는 그대로 구한다.
            
        }
    3. A -> B, B -> C로 바꿔서 2를 반복한다.
*/

typedef pair<int, int> point;

struct cmp {
    bool operator()(pair<point, point> a, pair<point, point> b) {
        if (a.first.first == b.first.first) {
            return a.first.second > b.first.second;
        }
        return a.first.first > b.first.first;
    }
};


int main() {
    int N;
    cin >> N;

    // 저장시에는 priority_queue<pair<pair<int, int>, pair<int, int>> 로 저장하자.
    priority_queue<pair<point, point>, vector<pair<point, point>>, cmp> squares;

    // 계산 시의 편의를 위해 y2, y1의 순서를 바꿔 저장
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        squares.push({{x1, x2}, {y2, y1}});
    }
    
    int answer(0);
    
    // A는 이전에 봤던 사각형, B는 이번에 보고 있는 사각형이다.
    // x1 < x2, y1 < y2임
    int A_x1, A_x2, A_y1, A_y2;
    int B_x1, B_x2, B_y1, B_y2;
    
    // 첫 사각형으로 A값 설정
    A_x1 = squares.top().first.first;
    A_x2 = squares.top().first.second;
    A_y1 = squares.top().second.first;
    A_y2 = squares.top().second.second;
    squares.pop();

    // 첫 사각형은 그냥 넓이를 저장한다.
    answer += abs(A_x2 - A_x1) * abs(A_y2 - A_y1);

    // 이후로는 A, B의 비교를 반복
    while (!squares.empty()) {
        B_x1 = squares.top().first.first;
        B_x2 = squares.top().first.second;
        B_y1 = squares.top().second.first;
        B_y2 = squares.top().second.second;
        squares.pop();

        // 1. A의 x2가 B의 x1보다 작은 값인 경우 -> 둘이 겹칠 일이 없는 것이므로, B의 넓이를 계산해서 Answer에 더한다
        if (A_x2 < B_x1) {
            answer += abs(B_x2 - B_x1) * abs(B_y2 - B_y1);
        }

        // 2. A의 x2가 B의 x1보다 큰 값인 경우 -> 둘의 x좌표가 일부 겹치는 것이다. y범위에 대해서도 검사를 실행한다
        else if (A_x2 > B_x1) {

            //  2-1. 둘의 y범위가 겹치지 않는 경우 (B.y.start < B.y.end < A.y.start || A.y.end < B.y.start < B.y.end)
            //       A와 B는 겹치지 않는 것이므로 B의 넓이를 계산해서 Answer에 더한다.
            if (B_y2 < A_y1 || B_y1 > A_y2) {
                answer += abs(B_x2 - B_x1) * abs(B_y2 - B_y1);
            }


            /// 2-2. 둘의 y범위가 겹치는 경우 (B.y.start < A.y.start < B.y.end || B.y.start < A.y.end < B.y.end)
            ///      겹치지 않는 y값의 크기를 구하고, (겹치지 않는 y값) x (겹치는 x값) + (y값) x (겹치지 않는 x값)으로 B를 구한 후에 Answer에 더한다.

            // A의 아래쪽에 B가 걸치는 경우 (B_y1 < A_y1 < B_y2 < A_y2)
            // 겹치는 x좌표에 대해서는 A_y1 - B_y1 만큼만 계산하고, 나머지 x값에선 B_y2 - B_y1만큼 계산한다.
            else if (B_y1 < A_y1 && A_y1 < B_y2 && B_y2 < A_y2) {
                answer += abs(A_x2 - B_x1) * abs(A_y1 - B_y1);
                answer += abs(B_x2 - A_x2) * abs(B_y2 - B_y1);             
            }

            // A의 위쪽에 B가 걸치는 경우 (A_y1 < B_y1 < A_y2 < B_y2)
            // 겹치는 x좌표에 대해서는 B_y2 - A_y2 만큼만 계산하고, 나머지 x값에선 B_y2 - B_y1만큼 계산한다.
            else if (A_y1 < B_y1 && B_y1 < A_y2 && A_y2 < B_y2) {
                answer += abs(A_x2 - B_x1) * abs(B_y2 - A_y2);
                answer += abs(B_x2 - A_x2) * abs(B_y2 - B_y1);             
            }

            // 2-3. B의 y범위가 A의 y범위에 포함되는 경우 (A.y.start <= B.y.start < B.y.end <= A.y.end)
            //      A와 B의 겹치는 x값에 대해서는 계산하지 않고, 겹치지 않는 x값에 대한 부분만 구한다.
            else if (A_y1 <= B_y1 && B_y2 <= A_y2) {
                answer += abs(B_x2 - A_x2) * abs(B_y2 - B_y1);
            }


            // 2-4. A의 y범위가 B의 y범위에 포함되는 경우 (B.y.start <= A.y.start < A.y.end <= B.y.end)
            //      겹치는 x값 부분에서는 (A.y.start - B.y.start) + (B.y.end - A.y.end)를 곱해서 구해주고, 나머지는 그대로 구한다.
            else {
                answer += abs(A_x2 - B_x1) * abs(A_y1 - B_y1);
                answer += abs(A_x2 - B_x1) * abs(B_y2 - A_y2);
                answer += abs(B_x2 - A_x2) * abs(B_y2 - B_y1);
            }
        }         

        // B -> A로 교체하고 다음 값을 본다
        A_x1 = B_x1;
        A_x2 = B_x2;        
        A_y1 = B_y1;
        A_y2 = B_y2;
    }

    cout << answer << endl;
    return 0;
}