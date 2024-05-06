#include <iostream>
#include <stack>
using namespace std;

/*
    수열로 스택 만들기
    주어진 순서대로 수열을 활용하자

    가능한 연산은 두 개
    1. 사용하지 않은 수 중 가장 작은 수를 스택 맨 위에 쌓기
    2. 스택의 맨 위에서 수를 빼서 수열에 추가하기

    다음 값을 봤을 때, 현재 top보다 큰 수를 달라고 하면 줄 수 있다.
    그런데 현재 top보다 작은 수를 달라고 하면, 줄 수 없음.

    yes no 판별 이렇게 하자
*/

int main() {
    int N;
    cin >> N;

    string operators = "";
    int push_value = 1;
    stack<int> myStack;

    for (int i = 0; i < N; i++) {
        int needed_num;
        cin >> needed_num;

        // 지금 출력해야 하는 값이 스택의 top보다 작다면, 어찌 할 방법이 없음
        if (!myStack.empty() && needed_num < myStack.top()) {
            cout << "NO" << endl;
            return 0;
        }

        // 값을 하나 입력받을때마다, stk.top이 그 값보다 작다면 stk.top == input이 될때까지 값을 Push해야 한다.
        while (myStack.empty() || myStack.top() < needed_num) {
            myStack.push(push_value++);
            operators += '+';
        }

        myStack.pop();
        operators += '-';
    }


    for (int i = 0; i < operators.size(); i++) {
        cout << operators[i] << endl;
    }
    return 0;
}