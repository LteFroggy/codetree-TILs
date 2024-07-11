#include <iostream>
#include <vector>
using namespace std;

/*
    N개의 칸이 있다. A_i부터 B_i까지 블럭을 1씩 쌓으라는 명령이 주어진다.
    1번부터 N번까지 쌓인 블럭의 개수를 오름차순으로 정렬했을 떄, 가운데 수를 출력하는 프로그램을 작성해라.

    누적합으로 합 구하고, 사이즈 25000짜리 vector<int> sort 만들어서 Count sort 수행하자.
    총 원소가 N개라면, N / 2 + 1번째가 중간값(가운데 숫자)이다.

    따라서 for (i = 0; i <= 25000; i++) { value + sort[i] } 해가면서 value >= N / 2 + 1 되는 지점을 찾으면 된다.
*/

int main() {
    // radix sort 저장용 배열
    // 누적합이기 때문에 뒤에 한 칸을 여유분으로 잡아주어야 오류 없이 돌아간다.
    int *nArr = new int[25002]{0};

    int N, K;
    cin >> N >> K;

    int *nValues = new int[N + 1]{0};

    for (int i = 0; i < K; i++) {
        int start, end;
        cin >> start >> end;
        nValues[start]++;
        nValues[end + 1]--;
    }
    // for (int i = 1; i <= N; i++) { cout << nValues[i] << " "; };
    // cout << endl << endl;

    for (int i = 1; i <= N; i++) {
        // 누적합 적용하기 및 Count sort 수행하기
        nValues[i] += nValues[i-1];
        nArr[nValues[i]]++;
    }

    // for (int i = 1; i <= N; i++) { cout << nValues[i] << " "; };
    // cout << endl;

    // nArr을 보면서 int(N / 2) + 1번째 원소가 뭔지 알아낼 것
    int nCount = 0;
    for (int i = 0; i <= 25000; i++) {
        nCount += nArr[i];

        if (nCount >= (N / 2) + 1) {
            cout << i << endl;
            break;
        }
    }

    delete[] nArr;
    delete[] nValues;
    return 0;
}