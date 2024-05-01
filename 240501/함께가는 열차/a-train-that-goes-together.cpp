#include <iostream>
#include <stack>

using namespace std;

/*
    무한한 선로 위에서 이제 출발하려는 N개의 열차가 있다.
    각자 출발 위치, 속도가 다르다
    선로가 하나라서, 추월 불가능하고 앞차 속도에 맞춰진다.

    무한한 시간이 흘러서 열차가 더 이상 맞닿을 일이 없을 때. 연결된 열차 덩어리의 개수를 출력해보자.

    나보다 빠르지만 뒤에 있는 친구들은 모두 나와 덩어리가 된다.
    스택으로 어찌어찌 해결할 수 있을 것 같긴 하다.

    나보다 뒤에 있는데 나보다 빠르면 별도의 덩어리가 맞다. 그러나 나보다 앞에 있는데 느리다면??? 하나가 되는 것이다. 그리고 그 속도로 맞춰짐
    위치는 오름차순으로 주어진다고 했으니, 속도가 역순이 되면 그것보다 작은 속도가 나올때까지 pop하면서 마지막에 스택의 수를 세자.
*/

int main() {
    int N;
    cin >> N;

    stack<int> stk;

    for (int i = 0; i < N; i++) {
        int loc, speed;
        cin >> loc >> speed;
        // 위치는 오름차순이니 중요하지 않다. 속도만 신경쓰자
        if (stk.empty()) {
            stk.push(speed);
            continue;
        }

        // 나보다 뒤에 있는 친구가 나보다 빠르면, 나와 한 덩어리가 될 것
        while (!stk.empty() && stk.top() > speed) {
            stk.pop();
        }
        
        stk.push(speed);
    }


    cout << stk.size() << endl;
    return 0;
}