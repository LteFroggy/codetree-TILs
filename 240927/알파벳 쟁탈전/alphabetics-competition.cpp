#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
    A, B, C중 하나의 문자를 가진다.
    조건을 위해, K번에 걸쳐서 두 학생이 같은 문자를 들고 있는지 다른 문자를 들고 있는지에 대한 정보가 주어짐

    조건을 전부 만족하며 나올 수 있는 서로 다른 가지수를 구하는 프로그램을 작성해보자.

    1. 어떤 친구와 관계가 주어진 경우에는, 경우의 수가 1이 되거나, 2가 된다. (같다 혹은 다르다)
    2. 관계가 없다면, 세 가지 모두 가능하다

    예를 들어 1, 2가 같고, 1, 3이 다르다면 1은 3가지, 2는 1가지, 3은 2가지, 4가 3가지 다 곱하면 9 x 2 = 18이 된다.

    근데 만약 말도 안 되는 조건이 있다면? 예를 들어 1과 3이 같고, 2와 3이 같은데 1과 2가 다르다던지 등.
    이런 건 없다고 생각하자.
*/

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> counts(N, 3);

    for (int i = 0; i < K; i++) {
        char condition;
        int a, b;
        cin >> condition >> a >> b;
        
        // 작은 값, 큰 값 구분하기
        int small = min(a, b);
        int big = max(a, b);


        // 두 개가 같은 조건이라면, 뒤의 것은 경우의 수가 1이 된다.
        if (condition == 'S') counts[big - 1] = 1;
        // 두 개가 다른 조건이라면, 뒤의 것은 경우의 수가 2가 된다.
        else counts[big - 1] = 2;
    }

    // 다 정리했으면 곱한다.
    int answer = 1;

    for (auto v : counts) answer *= v;

    cout << answer << endl;
    return 0;
}