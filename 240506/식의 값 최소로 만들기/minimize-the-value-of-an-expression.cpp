#include <iostream>

using namespace std;

/*
    최소값을 구해야 한다.
    빼기값을 크게 만들자
    뺄셈 뒤에 덧셈이 나오면, 괄호로 묶어서 모두 뺄셈으로 간주할 수 있다.
    앞에 뺄셈이 있냐 없냐만 신경쓰자.
*/

int main() {
    string whole_string;
    string number;
    bool anyMinusThere = false;

    cin >> whole_string;

    int answer = 0;
    for (int i = 0; i < whole_string.size(); i++) {
        // 숫자값을 만났다면, number에 추가해준다.
        if (whole_string[i] != '+' && whole_string[i] != '-') {
            number += whole_string[i];
        }

        // +나 -를 만났다면, 이전 operation을 이용해 answer값에 계산을 수행한다.
        else {
            // 그런데, 앞에서 -가 하나라도 있었다면, 항상 뺄셈으로 괄호를 사용해 바꿀 수 있음.
            if (anyMinusThere) {
                answer -= stoi(number);
                number = "";
            }
            // 아직 마이너스가 없었다면, 덧셈처리 해줘야 함.
            else {
                answer += stoi(number);
                number = "";
            }

            if (whole_string[i] == '-') {
                anyMinusThere = true;
            }
        }
    }
    
    // 계산이 끝나고, 마지막 숫자만 남는다. 이것 더해주기
    if (anyMinusThere) {
        answer -= stoi(number);
    }
    else {
        answer += stoi(number);
    }


    cout << answer << endl;
    return 0;
}