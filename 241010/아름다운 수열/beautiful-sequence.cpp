#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    N개의 원소인 수열 A와 M개의 숫자로 이루어진 수열 B가 있음
    수열 A에서 길이가 M인 연속 부분 수열 중, 아름다운 수열의 수를 세는 프로그램을 작성하자
    
    수열 B의 각 원소들에 동일한 숫자를 더하거나 뺴고, 순서를 바꿔서 나오는 수열을 아름다운 수열이라고 한다.
    예를 들어 수열 B가 4,6,7이라면 여기서 전부 1씩 뺀 356, 2씩 더한 689, 순서만 바꾼 647, 값을 빼고 순서를 바꾼 536 모두 아름다운 수열이다.

    어떻게 편하게 체크할까?
    약간 해쉬같은 느낌 적용해볼지 고민됨.
    해시 체크 먼저 하고, 그게 일치하면 확실한지 체크하러 가는 방법
    그렇게 하기 위해서는 B의 합 - A의 합 / M이 먼저 나누어 떨어져야 함.

    그리고 진짜인지 체크하기 위해서는, 저 위에서 나온 값을 A의 각 요소에 더한 후 중복체크를 해야 함.
    중복체크는 unordered_map을 만들고 ==연산자를 사용하자.
*/

int main() {
    int N, M;
    int count = 0;
    vector<int> idx;
    
    // A 입력받기
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    // B 입력받기
    cin >> M;
    vector<int> B(M);
    for (int i = 0; i < M; i++) cin >> B[i];
    // 추후 비교를 위해 B를 정렬해둔다
    sort(B.begin(), B.end());

    // B의 부분합 구해두기
    int B_sum = 0;
    for (auto v : B) B_sum += v;

    /*
    cout << "B : ";
    for (auto v : B) cout << v << " ";
    cout << endl;
    */

    int A_sum = 0;
    // A를 M개씩 잘라가면서 아름다운 수열인지 비교한다
    for (int i = 0; i + M <= N; i++) {
        // 첫 값이라면, 부분합 구하기
        if (i == 0) {
            for (int j = 0; j < M; j++) A_sum += A[j];
        }
        
        // 첫 값이 아니라면, 부분합 수정하기
        else {
            A_sum -= A[i - 1];
            A_sum += A[i + M - 1];
        }

        /// cout << "IDX : " << i << endl;
        /// cout << "A_Sum : " << A_sum << endl;
        /// cout << "B_Sum : " << B_sum << endl;

        // 이제 먼저 B_sum - A_sum % M을 수행해본다.
        // 이게 0이라면, 아름다운 수열일 가능성이 있음!
        // 모든 값에 동일한 숫자를 더하거나 뺴서 아름다운 수열이 될 수 있을지도 모르기 때문
        if ((B_sum - A_sum) % M == 0) {
            vector<int> tmp;

            /// cout << "A_Sum - B_sum % M = 0" << endl;

            // tmp에 동일한 숫자를 더하거나 뺸 후 저장해준다.
            for (int j = i; j < i + M; j++) {
                tmp.push_back(A[j] + ((B_sum - A_sum) / M));
            }

            // 그리고 그 값을 정렬한다
            sort(tmp.begin(), tmp.end());

            /*
            for (auto v : tmp) cout << v << " ";
            cout << endl;
            */

            // 만약 이 값이 B와 동일하다면, 이건 순서를 바꿔서 아름다운 수열이 될 수 있다
            if (tmp == B) {
                count++;
                idx.push_back(i);
            }
         }
    }

    cout << count << endl;
    for (auto v : idx) cout << v + 1 << endl;

    
    return 0;
}