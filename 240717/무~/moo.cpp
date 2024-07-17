#include <iostream>
#include <vector>

using namespace std;

/*
    moo를 출력한다.
    S(t)는 그 전것을 출력하고, moo에서 o를 t+2번 출력한 다음에 전의 것을 다시 출력한다

    채치피티가 알려준 해결책
    1. N을 사용해서 이게 왼쪽 값인지, 오른쪽 값인지, 가운데 값인지 판단한다.
    S[t] = S[t - 1], t + 3, S[t - 1]
              왼쪽   가운데  오른쪽
    이다.

    이걸 이용해서 타고 올라가면서 찾아낼 것

    예를 들어 S[0] (moo)의 길이는 3이고, 왼쪽 오른쪽은 없으며 가운데는 0 + 3 = 3의 길이를 가진다.
    그 다음 S[1] = (moomooomoo)의 길이는 3 * 2 + 1 = 7이고, 왼쪽은 3, 오른쪽도 3, 가운데가 4이다.
*/

int main() {
    int N;
    cin >> N;
    int length(3);
    int t(0);

    // 일단 어디까지 가야 S[t]가 N보다 커지는지(N의 위치까지 도달할 수 있는지) 찾아낸다
    while (N > length) {
        t++;
        length *= 2;
        length += t + 3;
    }

    // cout << "t = " << t << "까지 진행함" << endl;
    // cout << "이 때의 총 길이는 " << length << endl;

    // 거기서부터 N의 위치를 파악해 나갈 것
    while (true) {
        // 사용하는 값은 왼쪽 길이, 가운데 길이, 오른쪽 범위이다.
        // 왼쪽의 길이는 S[t-1] + t + 3 + S[t-1]에서 S[t-1]까지만이다.
        // 따라서 S[t] - t - 3 / 2를 수행하면 왼쪽 길이가 나옴
        // 가운데 길이는 S[t]에 대해 t + 3이므로 t + 3이 가운데 길이이다.
        // 오른쪽 길이는, 왼쪽 길이 + 가운데 길이보다 N값이 크면 오른쪽에 포함되는 것이다. 이를 이용해서 수행

        int left_length = (length - t - 3) / 2;
        int center_length = t + 3;
        int right_length = left_length + center_length;

        // cout << endl;
        // cout << "t = " << t << "인 경우" << endl;
        // cout << "총 길이는 " << length << endl;
        // cout << "왼쪽 길이는 " << left_length << endl;
        // cout << "가운데 길이는 " << center_length << endl;
        // cout << "오른쪽 범위는 " << right_length << "이상인 경우부터이다." << endl;
        // cout << "현재 N값은 " << N << endl;

        // N이 왼쪽에 포함되는 경우
        if (N < left_length) {
            length = left_length;
            t--;

            // cout << "N은 왼쪽 범위에 포함된다. " << endl;
        }

        // N이 오른쪽에 포함되는 경우
        else if (right_length <= N) {
            N -= right_length;
            length = left_length;
            t--;

            // cout << "N은 오른쪽 범위에 포함된다. " << endl;
        }

        // N이 가운데에 포함되는 경우
        else {
            N -= left_length;
            // cout << "N이 가운데 범위에 포함된다. " << endl;

            // 가운데에서 1번째 원소인 경우에만 m이고, 나머지는 o이다.
            if (N == 1) {
                cout << 'm' << endl;
            }
            
            else {
                cout << 'o' << endl;
            }
            break;
        }
    }

    return 0;
}