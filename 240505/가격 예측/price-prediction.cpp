#include <iostream>
#include <vector>

using namespace std;

/*
    기본적으로 내려가면 사고, 올라가면 판다.
    위로 꺾이기 전에 사고 아래로 꺾이기 전에 팔기 반복하면 될 듯
*/

int main() {
    int N, money;
    cin >> N >> money;

    vector<int> price_per_day(N);

    for (int i = 0; i < N; i++) {
        cin >> price_per_day[i];
    }

    int stock_now = 0;
    for (int i = 0; i < N; i++) {
        // 현재 주식을 가지고 있다면, 내일 더 오르는지 아닌지 봐야 한다
        if (stock_now != 0) {
            // 내일 안 오르거나, 마지막 날이면, 오늘 팔기
            if (i == N - 1 || price_per_day[i + 1] < price_per_day[i]) {
                // cout << stock_now << "개를 " << price_per_day[i] << "원에 팔았습니다." << endl;
                money += stock_now * price_per_day[i];
                stock_now = 0;
                // cout << "현재 소지금은 " << money << "원입니다" << endl;
            }

            else {
                continue;
            }
        }

        // 현재 주식을 가지고 있지 않다면, 내일 가격이 오늘 가격보다 낮은지 봐야 한다.
        else {
            if (i != N - 1 && price_per_day[i] < price_per_day[i + 1]) {
                stock_now += money / price_per_day[i];
                money %= price_per_day[i];
                // cout << stock_now << "개를 " << price_per_day[i] << "원에 샀습니다." << endl;
                // cout << "현재 소지금은 " << money << "원입니다" << endl;
            }

            else {
                continue;
            }
        }
    }
    cout << money << endl;
    return 0;
}