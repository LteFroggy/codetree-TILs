#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
    3 5 2 3 2 1 4 2 3

    처음에는 0개로 시작한다.
    물의 높이가 1이 되면 1이 잠기면서 2개가 된다.
    2가 되면? 빙산이 2개 잠기면서 4개가 된다.
    3이 되면? 2개가 더 잠기긴 하는데, 개수는 오히려 줄어든다.

    나의 양쪽에 나보다 큰 값이 하나만 존재한다면, 내가 잠겼어도 빙산의 수는 변화가 없다.
    근데 주변에 나보다 작은 값만이 존재한다면, 내가 잠겼을 경우에 빙산이 줄어든다
    반대로 나보다 큰 값이 양쪽에 존재한다면, 내가 잠겼을 때 빙산이 늘어난다!

    @@@ 추가로 같은 높이의 빙산이 이어질 경우에는, 하나의 빙산으로 생각해야 한다.
    @@@ 어차피 높이가 같으면 같이 잠길 것이기 때문.

    이를 이용해 map<int, int> 를 저장하자. 해쉬맵같은 것.
    map의 첫 번째 값은 물의 높이, 두 번째 값은 물의 높이가 첫 값이 되었을 때에 늘어나는(혹은 줄어드는) 빙산의 개수를 의미한다.
    모든 물의 높이에 대해 저장하지 않는 이유는, 물의 높이가 1부터 10억까지이기 때문에 값을 너무 많이 잡아먹을 것 같기 때문이다.
*/

// target의 물 높이일 때 빙하의 개수가 value만큼 늘어남을 map에 적용해주는 함수
void addCount(map<int, int> &iceBergs, int target, int value) {
    // 먼저 target에 해당하는 값이 key로 존재하는지 확인하고, 존재한다면 값을 1 증가시킨다.
    if (iceBergs.find(target) != iceBergs.end()) {
        iceBergs[target] += value;
    }

    // 존재하지 않는다면, 값을 생성한다.
    else {
        iceBergs.insert({target, value});
    }
}

int main() {
    // 물의 높이가 key일 때, 빙산의 개수의 변화량을 value로 저장하는 map 자료형
    map<int, int> iceBergs;
    int N;
    cin >> N;
    
    // 각각 이전, 현재, 다음 빙산의 높이를 의미한다.
    // before, after값을 이용해 now의 값을 갱신할 것이다.
    // array나 vector등을 이용해 미리 빙산의 높이를 받아두면 조금 더 편하나, 메모리 절약을 위해 받아서 바로 처리하는 것으로 하였음.
    int before(0), now(0), after(0);

    // 0번째 값은 미리 받아놓는다.
    cin >> now;

    // 이제 after에 값을 계속 받아가면서 갱신을 이어간다.
    for (int i = 1; i <= N; i++) {
        // after값을 새로 받는다. 단 i가 N이 되었을 때에는 더이상 받을 값이 없을 것이므로 받지 않는다.
        if (i != N) {
            cin >> after;
        }
        // cout << endl << endl << i << "번째 빙산 확인 중" << endl;   
        // cout << "Before = " << before << endl;
        // cout << "Now = " << now << endl;
        // cout << "After = " << after << endl;

        // 같은 높이의 빙산이 뒤에 존재하는 경우에는, 하나로 보기 위해 그냥 새로 값을 받는다.
        if (after == now) {
            continue;
        }

        // before값이 0이라면 첫 빙산임을 의미한다.
        // 이 경우에는 after값만 now와 비교하면 된다!
        if (before == 0) {
            // 이 다음 값이 이 값보다 크다면, 물의 높이가 now가 된다고 해도 빙산의 개수에 변화는 없다
            if (after > now) {
                // cout << "뒤의 높이가 현재보다 크므로 잠겨도 변화 없음" << endl;
            }

            // 이 다음 값이 이 값보다 작다면, 물의 높이가 now가 되었을 때 빙산이 하나 사라지게 된다.
            else {
                // cout << "뒤의 높이가 현재보다 작으므로 잠기면 줄어듦" << endl;
                addCount(iceBergs, now, -1);
            }
        } ////// if (before == 0)
        
        // 만약 after가 0이라면 마지막 빙산인 것이다. before값만 사용해서 처리한다.
        else if (after == 0) {
            // 이전 빙산이 이것보다 크다면 물의 높이가 now가 되어도 빙산의 개수에 변화는 없다.
            if (before > now) {}
            
            // 이전 빙산이 이것보다 작다면, 물의 높이가 now가 되는 경우 빙산이 하나 줄어든다
            else {
                addCount(iceBergs, now, -1);
            }
        }
        

        // 첫 값이나 마지막 값이 아니라면, 앞뒤와 모두 비교해야 한다.
        else {
            int taller_than_now_count = 0;
            if (before > now) taller_than_now_count++;
            if (after > now) taller_than_now_count++;

            // 양쪽이 나보다 더 크다면, 내가 잠겼을 때 빙산이 하나 늘어난다.
            if (taller_than_now_count == 2) {
                // cout << "얘가 잠기면 빙산이 늘어난다." << endl;
                addCount(iceBergs, now, 1);
            }

            // 둘중에 한쪽만 나보다 크다면, 내가 잠겨도 별 변화는 없다
            else if (taller_than_now_count == 1) {
                // cout << "얘가 잠겨도 빙산에 변화 없다." << endl;
            }

            // 둘 다 나보다 작다면, 내가 잠겼을 때 빙산이 하나 줄어든다
            else {
                // cout << "얘가 잠기면 빙산이 줄어든다." << endl;
                addCount(iceBergs, now, -1);
            }
        } ////// else
        

        // 처리가 완료되었다면 now를 before로, after를 now로 변경한다.
        before = now;
        now = after;
        after = 0;
    }

    // 이제 빙산의 개수를 모두 파악했다. iceBergs를 순회하면서 빙산이 가장 많은 시점을 찾아내자
    int answer = 1;
    int iceBerg_count = 1;

    for (auto iter = iceBergs.begin(); iter != iceBergs.end(); iter++) {
        // cout << "물 높이 " << iter->first << "일 때, 빙산은 " << iter->second << "개 늘어난다." << endl;
        iceBerg_count += iter->second;
        if (answer < iceBerg_count) {
            answer = iceBerg_count;
        }
    }


    cout << answer << endl;
    return 0;
}