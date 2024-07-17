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
        length *= 2;
        length += t + 3;
        t++;
    }

    // 거기서부터 N의 위치를 파악해 나갈 것
    while (true) {
        // 왼쪽의 길이는 S[t-1] + t + 3 + S[t-1]에서 S[t-1]까지만이다.
        // 따라서 S[t] - t - 3 / 2를 수행하면 왼쪽 길이가 나옴
        // 예를 들어 S[1]은 3 + 4 + 3이라, 총 길이는 10이고 0 1 2까지 왼쪽, 3 4 5 6이 가운데, 7 8 9가 오른쪽이다.
        // S[2]는 10 + 5 + 10이기 때문에 0 ~ 9(<10)가 왼쪽, 10 ~ 14(<15)가 중간, 15 ~ 24(15<=)가 오른쪽이다.
        int left_length = (length - t - 3) / 2;
        int right_length = left_length;
        int center_length = t + 3;

        // N이 왼쪽에 포함되는 경우
        if (N < left_length) {
            length = left_length;
            t--;
        }

        // N이 오른쪽에 포함되는 경우
        else if (left_length + center_length < N) {
            N -= left_length + center_length;
            length = right_length;
            t--;
        }

        // N이 가운데에 포함되는 경우
        else {
            N -= left_length;

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