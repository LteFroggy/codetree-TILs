#include <iostream>
#include <stack>
using namespace std;

/*
    2가지 숫자만 나와야 하나를 제했을 때 최대 길이를 만들 수 있게 된다. 따라서 2개의 숫자만 사용한 최대 문자열의 길이를 구한다.

    숫자 하나를 num1, 숫자 하나를 num2로 저장하면서 값을 쭉 보다가 num1, num2가 아닌 값을 만나면 num1, num2중 큰 값을 answer에 저장한다.
    
    num1, num2, num1_count, num2_count, stack<int>를 사용한다.
    num1, num2 모두 아닌 수가 나온다면 num1, num2 중 큰 값을 answer에 저장한다(단, num1 != 0 && num2 != 0 을 만족해야 한다.)
*/

int main() {
    int N;
    cin >> N;

    // 값 저장용 변수들
    int num1(0);
    int num2(0);
    int num1_count(0);
    int num2_count(0);
    stack<int> stk;
    int answer(0);

    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        // 처음, num1 저장되어있지 않다면 이 값을 num1으로 사용한다.
        if (num1 == 0) {
            num1 = tmp;
            num1_count++;
        }

        //  이번에 들어온 값이 Num1값이면 num1_count를 하나 늘린다
        else if (num1 == tmp) {
            num1_count++;
        }

        // num1값이 아닌 값이 나왔는데 num2가 비어있다면, num2로 저장해준다
        else if (num2 == 0) {
            num2 = tmp;
            num2_count++;
        }

        // num2값이면 num2_count를 늘린다
        else if (num2 == tmp) {
            num2_count++;
        }

        // tmp가 num1값도, num2값도 아니라면 이제 새로운 값이 등장한 것이다. answer를 저장하고 num1, num2를 바꿔준다. 
        else {
            // 일단 num1_count와 num2_count중 큰 값을 answer로 저장한다.
            int max_val = num1_count > num2_count ? num1_count : num2_count;
            if (max_val > answer) {
                answer = max_val;
            } 

            // 이제 num2와 num1을 바꿔야 한다.
            // num1은 새로 나온 값으로 설정하면 되고, num2는 stack을 보면서 바로 앞의 값으로 해주면 된다.
            num1 = tmp;
            num1_count = 1;

            num2 = stk.top();
            num2_count = 0;

            // num2_count의 설정을 위해 stack 탐색하기
            while (!stk.empty()) {
                if (stk.top() == num2) {
                    stk.pop();
                    num2_count++;
                }
                else {
                    // 탐색이 끝났으니 스택을 비운다
                    while (!stk.empty()) {
                        stk.pop();
                    }
                    break;
                }
            }
        }

        // 값은 stack에 넣어둔다
        stk.push(tmp);
    }

    // 모든 값을 다 받은 후에 남은 값에 대해서도 길이를 계산해준다.
    // 대신, num2가 0인 경우에는 계산하면 안 됨. 값이 하나밖에 없던 것이기 때문
    if (num2 != 0) {
        int max_val = num1_count > num2_count ? num1_count : num2_count;
        if (max_val > answer) {
            answer = max_val;
        }
    }

    cout << answer << endl;
    return 0;
}