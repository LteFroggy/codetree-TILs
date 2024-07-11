#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

/*
    N명의 학생에게 B의 예산으로 선물 주기
    i가 원하는 가격과 배송비가 있고, 하나를 반값할인 받을 수 있다. 선물 가격만 반값인듯?
    선물 가능한 학생의 최대 명수 구해보자.

    선물 가격이 A, 배송비가 B라 할 때 A + B가 작은 순으로 사면 될 것 같다.
    쿠폰 하나 있으니 이걸 어디에 쓰는지가 중요하다.
    쿠폰 하나 해봤자 최대 줄어드는 가격은 (어떤 물건 / 2)이다.
    따라서 작은 순으로 정렬해서 구매한다고 할 때, 쿠폰의 적용 여부는 하나의 물건을 더 사게 해주냐 마냐만 결정한다.
    그러므로 하나를 더 살 수 있는지 없는지만 따지면 됨.
*/

struct cmp {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return (a.first + a.second) > (b.first + b.second);
    } 
};

int main() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> que;
    
    int N, B;
    cin >> N >> B;

    for (int i = 0; i < N; i++) {
        int present_price, transport_price;
        cin >> present_price >> transport_price;
        
        que.push(make_pair(present_price, transport_price));
    }

    int max_present_price = 0;
    int present_count = 0;
    while (que.top().first + que.top().second <= B && ++present_count) {
        if (que.top().first > max_present_price) {
            max_present_price = que.top().first;
        }

        // cout << "선물 가격 " << que.top().first << ", 배송비 " << que.top().second << "인 품목 구매함" << endl;
        B -= que.top().first + que.top().second;
        que.pop();
    }

    // 남은 돈이 다음 선물의 절반 가격도 안 된다면, 아무리 할인을 많이 받아도 하나 더 구매는 불가능하다.
    // 어떤 물건의 배송비가 0이라고 해도, 최대 할인되는 금액은 (물건의 총 금액 / 2)이기 때문
    // 그걸 고려하면서 다음 선물 후보들을 하나씩 본다
    while (!que.empty() && B >= (que.top().first + que.top().second) / 2) {
        // 어떤 물건을 할인받을지 정한다. 물건이 제일 비싼 것을 할인받는게 좋음
        int coupon_price = max_present_price > que.top().first ? max_present_price : que.top().first;

        // 정해진 그걸 할인받으면 물건 구매가 가능한지 본다.
        if (B + (coupon_price / 2) >= que.top().first + que.top().second) {
            // cout << coupon_price << "원 짜리를 할인받으면 ";
            // cout << "선물 가격 " << que.top().first << ", 배송비 " << que.top().second << "인 품목 구매 가능" << endl;
            present_count++;
            break;
        }

        que.pop();
    }

    cout << present_count << endl;
    return 0;
}