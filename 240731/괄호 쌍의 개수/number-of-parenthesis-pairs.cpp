#include <iostream>
using namespace std;

/*
    괄호로만 있다! 정확히 하나의 소괄호 방향을 바꾸었을 때, 올바른 괄호 순서가 되는 가지수를 구해보자.
    최대 10만 글자이다.

    모든 값을 바꾸고 10만개의 글자를 읽으면서 가능한지 판단하는 것은 사실 쉽지 않다. 10^10까지 가기 때문.
    그럼에도 이렇게 해보아야 할 듯. 다른 방법이 생각이 나지 않아서..

    일단 괄호 판단은 int값을 사용해서 하자. 왼쪽 괄호를 만나면 +1, 오른쪽 괄호를 만나면 -1로 하고 중간에 음수가 되면 실패한 것이다.
    또한 하나의 괄호만 바꿀 수 있으므로, 모든 괄호를 세었을 때 (나 )중 하나가 2개 많을 것이다.
    왼쪽이 두 개 많다면, 왼쪽 하나를 오른쪽으로 바꿔야 하고 오른쪽이 두 개 많다면 오른쪽을 하나 왼쪽으로 바꿔야 한다.

    1. 왼쪽 괄호가 오른쪽 괄호보다 2개 많은 경우
     -> 왼쪽 괄호 하나를 오른쪽 괄호로 바꿔야 한다.
        바꿔서(괄호 판단용 값을 -2해 보았을 때에) 음수가 나오지 않으면 다 됨.
        
    
    2. 오른쪽 괄호가 왼쪽 괄호보다 2개 많은 경우
     -> 이 경우 괄호 판단용 값이 -2가 아닌 모든 오른쪽 괄호를 왼쪽 괄호로 바꿀 수 있다.
        괄호 판단용 값이 -2가 되는 값을 변경할 경우 앞에 오른쪽 열린 괄호 하나가 남아버리기 때문
*/
int answer(0);

int main() {
    
    string brackets;
    cin >> brackets;

    int check = 0;
    int left_possible(0), right_possible(0);
    // check값을 수정해가면서 수정 가능한 왼쪽 괄호의 개수, 수정 가능한 오른쪽 괄호의 개수를 센다.
    for (int i = 0; i < brackets.size(); i++) {
        // 먼저 체크값을 수정하고, 만약 이 왼쪽 괄호가 오른쪽 괄호로 바뀌었을 때 문제가 없다면 left_possible을 1 추가시킨다.
        if (brackets[i] == '(') {
            check++;
            if (check >= 2) {
                left_possible++;
            }
        }

        else {
            check--;
            if (check != -2) {
                right_possible++;
            }
        } 
    }   

    char target;
    // 만약 다 셌는데 왼쪽 괄호가 두개 더 많다면, (를 )로 바꿔야 하는 경우이므로 left_possible을 출력한다.
    if (check == 2) {
        cout << left_possible << endl;
    }
    
    // 반대라면 right_possible을 출력한다.
    else if (check == -2) {
        cout << right_possible << endl;
    }

    /
    else {
        cout << 0 << endl;
    }

    return 0;
}