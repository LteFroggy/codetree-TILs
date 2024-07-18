#include <iostream>
#include <string>
using namespace std;

/*
    이진수가 주어지면 십진수로 바꿔서 17배 하고 2진수로 나타내기
    최대 자리수가 1000자리?.. 그럼 최대값이 2^1000 - 1?...

    17a = 2^4 * a + a이다.
    따라서 4칸 왼쪽으로 shift하고 a자체를 더하면 된다
*/

int main() {
    string sInput;
    cin >> sInput;
    
    // 먼저 16배 해주기
    string sResult = sInput + "0000";
    // 더할 때, 자리수가 맞도록 추가해주기
    sInput = "0000" + sInput;
    
    // 거기에 원본 값 더하기
    for (int i = sResult.size() - 1; i >= 0; i--) {
        sResult[i] = char(int(sResult[i] - '0') + int(sInput[i] -'0') + '0');
        // cout << sResult.size() - i << " 번째 자리 값은 " << char(int(sResult[i] - '0') + int(sInput[i] -'0') + '0') << endl;
    }

    // 근데, 그냥 값을 더하기만 했으므로 2 이상의 값이 나올 수 있다. 따라서 올림을 좀 해 주어야 함
    // 자리수가 넘어갈 경우를 대비해 여분 공간 마련하기
    sResult = '0' + sResult;

    for (int i = sResult.size() - 1; i > 0; i--) {
        if (sResult[i] - '0' > 1) {
            int div = int(sResult[i] - '0') / 2;
            int remain = int(sResult[i] - '0') % 2;
            sResult[i] = char(remain + '0');
            sResult[i - 1] = char(int(sResult[i - 1] - '0') + div) + '0';
        }
    }
    
    // 자리수 넘어갈 경우를 대비해 만든 값이 사용되지 않았다면, 삭제한다
    if (sResult[0] == '0')
        sResult = sResult.substr(1, sResult.size() - 1);
    cout << sResult << endl;
    return 0;
}