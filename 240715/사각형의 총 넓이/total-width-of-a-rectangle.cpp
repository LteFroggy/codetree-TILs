#include <iostream>
#include <vector>

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

            2-3. B의 y범위가 A의 y범위에 포함되는 경우 (A.y.start < B.y.start < B.y.end < A.y.end)
                 A와 B의 겹치는 x값에 대해서는 계산하지 않고, 겹치지 않는 x값에 대한 부분만 구한다.

            2-4. A의 y범위가 B의 y범위에 포함되는 경우 (B.y.start < A.y.start < A.y.end < B.y.end)
                 겹치는 x값 부분에서는 (A.y.start - B.y.start) + (B.y.end - A.y.end)를 곱해서 구해주고, 나머지는 그대로 구한다.
            
        }
    3. A -> B, B -> C로 바꿔서 2를 반복한다.
*/

int main() {
    int N;
    cin >> N;

    // 저장시에는 pair<pair<int, int>, pair<int, int>> 로 저장하자.
    
    return 0;
}