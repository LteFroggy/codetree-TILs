#include <iostream>
#include <vector>

using namespace std;

/*
    moo를 출력한다.
    S(t)는 그 전것을 출력하고, moo에서 o를 t+2번 출력한 다음에 전의 것을 다시 출력한다

    S(0) = m o o
    S(1) = m o o m o o o m o o
    S(2) = m o o m o o o m o o m o o o o m o o m o o o m o o

    S[0] = 3;
    S[1] = 3 4 3;
    S[2] = 3 4 3 5 3 4 3;
    S[3] = 3 4 3 5 3 4 3 6 3 4 3 5 3 4 3;
    ...
    에서 각 숫자는 mo..o의 길이이다.

    각 S[n]을 vector<int>로 정의하자
    S[i] = S[i - 1], i + 3, S[i - 1]이 된다.
    

    // 방법 1.
    먼저 N이 주어지면, S[i].sum <= N을 만족하는 시점까지 S[i]을 구한다.
    S[i].sum = S[i-1].sum * 2 + (i + 3); 이다.
    
    이렇게 S[i]를 구했다면, S[i]에서 N번째 원소가 무엇인지 세면 된다.
    셀 때는 하나하나 세지 않고, 
    for (j = 0; j < S[i].size(); j++) {
        // 이번 mo..o를 세어도 목표치까지 도달하지 못한다면, 계속 센다.
        if (N - S[i][j] > 0) {
            N -= S[i][j];
        }


        // 이번 mo..o에서 목표치에 도달한다면, m인지 o인지 확인하기 위해 아래 조건문으로 들어간다
        else {
            // 만약 N == 1(하나만 더 세는 경우)이라면, mo..o에서 m이 내가 찾던 문자열인 것
            if N == 1
                cout << 'm' << endl;
            // 그게 아니라면 o가 내가 찾던 문자열이다.
            else 
                cout << 'o' << endl;
        }
    } 
    위와 같은 방식으로 처리한다.
*/

int main() {
    int N;
    cin >> N;

    // i = 0일 때 S[0].sum = 3이므로 sum은 3으로 시작
    vector<int> S_sum;
    int i(0);
    S_sum.push_back(3);
    // 먼저 S가 어디까지 확장되어야 하는지 확인한다.
    while (S_sum[i] < N) {
        // i가 1 늘어날때마다 sum = sum * 2 + (i + 3)이 된다.
        i++;
        S_sum.push_back(S_sum[i - 1] * 2 + (i + 3));
    }
    /*
        출력해본 S_sum
        S_sum : 3 10 25 
    */
    

    vector<vector<int>> S(i + 1);
    S[0].push_back(3);

    // 이제 S를 만든다.
    for (int j = 1; j < i; j++) {
        S[j].insert(S[j].begin(), S[j - 1].begin(), S[j - 1].end());
        S[j].push_back(j + 3);
        S[j].insert(S[j].end(), S[j - 1].begin(), S[j - 1].end());
    }

    // i번째 값은 아래와 같이 만든다. 설명은 111번 줄 주석에 있음
    S[i].push_back(i + 3);
    S[i].insert(S[i].end(), S[i - 1].begin(), S[i - 1].end());

    /*
        출력해본 S
        S[0] = 3 
        S[1] = 3 4 3 
        S[2] = 3 4 3 5 3 4 3 
    */

    // 확인용 S_sum과 S 출력
    // cout << "S_sum : ";
    // for (auto v : S_sum) {
    //     cout << v << " ";
    // }
    // cout << endl;

    // for (int i = 0; i < S.size(); i++) {
    //     cout << "S[" << i << "] = ";
    //     for (auto v : S[i]) {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

/*
    이제 N번째 원소를 찾아야 한다. 
    S[i]에서 N번째 원소를 찾을 수 있다. 그러나 실행속도 향상을 위해 약간의 조작을 수행하자.
    S[i] = {S[i - 1], i + 3, S[i - 1]}이다. 예를 들어
    S[0] = {3}이라면, S[1] = {3 4 3}인 것이다.

    그러므로 S[i] 에서 N번째 원소를 찾는 것은 {i + 3, S[i-1]}에서 N - S_sum[i-1]번째 원소를 찾는 것과 같다.
    이를 이용해 풀어보자
*/

    N -= S_sum[i - 1];
    
    for (int j = 0; j < S[i].size(); j++) {
        // 이번 mo..o를 세어도 목표치까지 도달하지 못한다면, 계속 센다.
        if (N - S[i][j] > 0) {
            N -= S[i][j];
        }

        // 이번 mo..o에서 목표치에 도달한다면, m인지 o인지 확인하기 위해 아래 조건문으로 들어간다
        else {
            // 만약 N == 1(하나만 더 세는 경우)이라면, mo..o에서 m이 내가 찾던 문자열인 것
            if (N == 1) {
                cout << 'm' << endl;
                break;
            }
            // 그게 아니라면 o가 내가 찾던 문자열이다.
            else {
                cout << 'o' << endl;
                break;
            }
        }
    }
    return 0;
}