#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
using namespace std;

/*
    N개의 전구가 원형으로 있다.
    버튼을 한번 누를 때마다 룰에 따라 전구가 동시에 꺼지고 켜진다
    나의 왼쪽 전구가 켜져있으면 전구 상태가 바뀐다.
    
    이 룰대로 전구가 작동한다고 가정할 떄, 버튼을 B번 누르면, 마지막에 어떤 상태인지 출력하자.
    켜진 것은 1로, 꺼진 것은 0으로 표현한다.

    최대 누르기 횟수가 10^15회이기 때문에 절대 하나하나 누르는건 안된다.
    일단, 루프가 존재하는지 확인해야 한다.
    반드시 루프가 존재한다고 장담할 수 있는가? -> 모름
    그래도, 이걸 찾지 못하면 말이 안됨
    
    루프 탐색을 위해 이진수 값을 이용하자.
    unordered_map<int, int>를 통해 저장할 것
    첫 값은 이진수 결과, 두번째 값은 등장했던 순서

    100회 반복해야 하는데, 
    3번째와 14번째가 같은 값이다.
    그럼 3번째부터 14번째는 루프이다.
    따라서 100번째는 
    14
    25
    36
    47
    58
    69
    80
    91 -> 반복 상태에서 9번만 반복하면 된다.

    (100 - 3) % 11 회만 하면 되는 것.
*/

// vector<bool> 값을 10진수로 변환해주는 함수
int to_binVal(vector<bool> &lights) {
    int result = 0;

    for (int i = lights.size() - 1; i >= 0; i--) {
        if (lights[i]) {
            result += int(pow(2, lights.size() - i - 1));
        }
    }

    return result;
}

// 버튼을 한번 눌렀을 때의 상태 변화를 보여주는 함수
void push_button(vector<bool> &lights) {
    vector<bool> new_state(lights.size());

    // 0번은 마지막 값 보기
    new_state[0] = lights[lights.size() - 1] ? !lights[0] : lights[0];

    for (int i = 1; i < lights.size(); i++) {
        new_state[i] = lights[i - 1] ? !lights[i] : lights[i];
    }

    lights = new_state;
}

int main() {
    int N;
    long long B;
    cin >> N >> B;
    vector<bool> lights(N);

    for (auto v : lights) {
        int tmp;
        cin >> tmp;
        if (tmp == 1) v = true;
        else v = false;
    }

    // 십진수 값과 그 index를 저장한다.
    unordered_map<int, long long> myMap;
    long long idx = 0;
    bool return_flag = false;

    // 일단, 10번 변환해보면서 각각의 val 확인하기

    /*
    for (int i = 0; i < 15; i++) {
        int val = to_binVal(lights);
        push_button(lights);
        for (auto v : lights) cout << v << " ";
        cout << endl << "val : " << val << endl;
    }
    */

    
    // idx가 목표에 도달했거나, return_flag가 true가 될 때까지 반복한다.
    while (idx < B && !return_flag) {
        // 일단 현재 조명 상태를 값으로 변환한다.
        int val = to_binVal(lights);

        // 만약 전에 이미 있던 상태라면, 반복을 찾은 것이니 이를 통해 결과를 구한다.
        if (myMap.find(val) != myMap.end()) {
            auto it = myMap.find(val);
            long long first_idx = it->second;
            long long repeat_step = idx - first_idx;

            long long needed_transform_count = (B - first_idx) % repeat_step;

            for (long long i = 0; i < needed_transform_count; i++) push_button(lights);

            return_flag = true;
            idx = B;
        }

        // 아직 없는 값이라면, 값을 집어넣고 lights상태를 변화시킨다.
        else {
            myMap.insert({val, idx});
            push_button(lights);
            idx++;
        }
    }

    // 결과를 반환한다
    for (auto v : lights) cout << v << endl;
    return 0;
}