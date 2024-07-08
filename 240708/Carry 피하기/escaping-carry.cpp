#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
    Carry가 전혀 발생하지 않게 최대로 고를 수 있는 숫자의 수를 계산해보자.
    각 자리수를 모두 더했을 때 10이 넘지 않게 하는 것이 중요하다.

    n은 최대 20개이다.
    그리고 자리수는 9개이다

    어떻게 하면 넘기지 않으면서 최대한 많은 수를 고를 수 있을까?
    n <= 20이니 넣고, 넣지 않고의 모든 경우를 고려해보기?
    2^20에서 모든 경우가 처리될 수 있기는 하다.
    2^10 = 1024, 2^20 = 2^10 * 2^10 = 1024 x 1024로 대략 10^6이기 때문에 시간복잡도는 적절하다.
    int는 하나에 4KB이므로 최대 10^6 * 4B = 400,000B = 약 4MB이므로 메모리도 괜찮다.
*/

int sAnswer = 0;

/*
    n은 몇 번째 원소를 볼 차례인지
    value는 현재 값
    count는 지금까지 몇 개의 값을 더했는지
    numbers는 숫자가 들어간 벡터
*/

// 풀이용 출력 없는 버전
void GetResult(int n, int value, int count, vector<int> numbers);
// 디버깅용 출력 있는 버전
void GetResult2(int n, int value, int count, vector<int> numbers);

int main() {
    int N;
    cin >> N;

    // 숫자 입력받기
    vector<int> numbers(N);
    for (int i = 0; i < N; i++) {
        cin >> numbers[i];
    }

    // 0 ~ N번째 숫자까지 각각 사용하는 경우, 사용하지 않는 경우의 두 가지를 계속 수행해 나갈 것
    GetResult(0, 0, 0, numbers);

    // 결과를 출력한다.
    cout << sAnswer << endl;

    return 0;
}



// 풀이용 출력 없는 버전
void GetResult(int n, int value, int count, vector<int> numbers) {
    // n == N이라면 더 이상 값은 없다. 끝까지 다 본 것이니 결과를 저장한다
    if (n == numbers.size()) {
        if (sAnswer < count) { 
            sAnswer = count;
        }
        return;
    }

    // n번째 값을 사용할 수도, 사용하지 않을 수도 있다.

    /* 사용하는 경우 */
    // 먼저 사용 가능한지 조건을 봐야 한다
    int possible_flag = true;
    int i = 1;

    // number[n]의 자리수까지만 체크해본다
    while (numbers[n] / int(pow(10, i - 1)) != 0) {
        // 234에서 2번째 수를 구하고 싶다면, 234 % 10^2 를 한 결과를 10^(2-1)로 나눠야 3이라는 값을 얻을 수 있다.
        int ith_number = (numbers[n] % int(pow(10, i))) / int(pow(10, i - 1));
        int ith_value = (value % int(pow(10, i))) / int(pow(10, i - 1));

        // 올림이 발생한다면, 이 수를 고를 수는 없다. 불가능으로 처리하고 루프를 끝낸다.
        if (ith_number + ith_value >= 10) {
            possible_flag = false;
            break;
        }
        i++;
    }

    // 만약 숫자를 더하는 데에 무리가 없었다면, 숫자를 더해서 다음으로 보낸다
    if (possible_flag) {
        GetResult(n+1, value + numbers[n], count + 1, numbers);
    }

    // 숫자를 더할 수 없었다면 더이상 진행할 수 없는 것이니 결과를 저장한다.
    else if (!possible_flag) {
        if (sAnswer < count) {
            sAnswer = count;
        }
    }

    /* 사용하지 않는 경우 */
    GetResult(n + 1, value, count, numbers);
}


// 디버깅용 출력 있는 버전 
void GetResult2(int n, int value, int count, vector<int> numbers) {
    // n == N이라면 더 이상 값은 없다. 끝까지 다 본 것이니 결과를 저장한다
    if (n == numbers.size()) {
        if (sAnswer < count) { 
            sAnswer = count;
        }
        return;
    }

    // n번째 값을 사용할 수도, 사용하지 않을 수도 있다.

    /* 사용하는 경우 */
    // 먼저 사용 가능한지 조건을 봐야 한다
    int possible_flag = true;
    int i = 1;

    cout << numbers[n] << "과 " << value << "를 비교하는 상황입니다." << endl;

    // number[n]의 자리수까지만 체크해본다
    while (numbers[n] / int(pow(10, i - 1)) != 0) {
        // 234에서 2번째 수를 구하고 싶다면, 234 % 10^2 를 한 결과를 10^(2-1)로 나눠야 3이라는 값을 얻을 수 있다.
        int ith_number = (numbers[n] % int(pow(10, i))) / int(pow(10, i - 1));
        int ith_value = (value % int(pow(10, i))) / int(pow(10, i - 1));

        cout << i << "번째 자리수는 각각 " << ith_number << " " << ith_value << endl;
        cout << "더한 결과는 " << ith_number + ith_value << endl;

        // 올림이 발생한다면, 이 수를 고를 수는 없다. 불가능으로 처리하고 루프를 끝낸다.
        if (ith_number + ith_value >= 10) {
            possible_flag = false;
            break;
        }
        i++;
    }

    // 만약 숫자를 더하는 데에 무리가 없었다면, 숫자를 더해서 다음으로 보낸다
    if (possible_flag) {
        cout << value + numbers[n] << "이 다음 값으로 간다" << endl << endl;
        GetResult(n+1, value + numbers[n], count + 1, numbers);
    }

    // 숫자를 더할 수 없었다면 더이상 진행할 수 없는 것이니 결과를 저장한다.
    else if (!possible_flag) {
        cout << "올림이 발생해서 종료함" << endl;
        cout << "현재 Count = " << count << endl;
        if (sAnswer < count) {
            cout << "갱신됨" << endl;
            sAnswer = count;
        }
        else {
            cout << "갱신 안됨" << endl;
        }
        cout << endl << endl;
    }

    /* 사용하지 않는 경우 */
    GetResult(n + 1, value, count, numbers);
}