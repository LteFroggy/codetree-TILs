#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    y - x ≤ z - y ≤ 2 * (y - x) 

    다 구하나??? 일단 다 구하기로 해보자
    
    first, end의 두 가지 포인터를 사용한다.
    복잡도는 최대 999 * 1000 / 2이다.

*/

// 각 값을 보고 가능한지 확인해준다
// 조건 만족시 0, 1번 조건 불만족시 1, 2번 조건 불만족시 2
inline bool possible_check(int a, int b, int c) {
    return (b - a <= c - b) && (c - b <= (b - a) * 2);
}

int main() {
    int answer(0);
    int N;
    cin >> N;

    vector<int> nums;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        nums.push_back(tmp);
    }

    // 정렬
    sort(nums.begin(), nums.end());

    // 들어간거 확인
    // for (int i = 0; i < nums.size(); i++) cout << nums[i] << " "; cout << endl;

    // 이제 탐색 진행
    int begin, middle, end;
    
    bool end_flag = false;
    // begin을 한 칸씩 밀어갈 것
    for (begin = 0; begin <= nums.size() - 3; begin++) {
        // end도 begin + 2부터 끝까지 민다
        for (end = begin + 2; end < nums.size(); end++) {
            // 그 사이 모든 값을 middle로 잡고, 하나씩 가능한지 체크한다
            for (middle = begin + 1; middle < end; middle++) {
                if (possible_check(nums[begin], nums[middle], nums[end])) answer++;
            }
        }
    }

    cout << answer << endl;

    return 0;
}