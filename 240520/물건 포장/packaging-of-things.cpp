#include <iostream>

using namespace std;

/*
    물건은 같이 포장하냐 새로 포장하냐밖에 없다
    그리디로 할 것
*/

int main() {
    int N, m, K;
    cin >> N >> m >> K;

    int min_size;
    int max_size;
    int bundle_count = 0;
    int answer = 0;
    for (int i = 0; i < N; i++) {
        cout << endl;
        int size;
        cin >> size;

        // 번들이 없으면 일단 새로운 번들에 싸야 함
        if (bundle_count == 0) {
            min_size = size;
            max_size = size;
            bundle_count = 1;
            cout << size << "는 박스가 없어 새로 포장 시작함" << endl;
        }

        // 번들이 있다면, 넣을지 새로 쌀지 결정해야 함
        else {
            int existing_box_cost;
            int new_box_cost;

            // 기존 박스에 그대로 넣으면 드는 비용 계산 (포장비 제외)
            int tmp_min_size = min_size;
            int tmp_max_size = max_size;

            if (min_size > size) {
                tmp_min_size = size;
            }
            else if (max_size < size) {
                tmp_max_size = size;
            }

            existing_box_cost = (bundle_count + 1) * (tmp_max_size - tmp_min_size);
            
            new_box_cost = (bundle_count) * (max_size - min_size) + K;

            // 새 박스를 쓰는 게 더 비용이 절감된다면, 새 박스 쓴다
            if (existing_box_cost >= new_box_cost) {
                cout << size << "에 대해 새 박스를 쓰는 것이 더 저렴하여 새 박스 사용함" << endl;
                cout << "현재 비용은 " << answer << " + " << K << " + (" << bundle_count << " * (" << max_size << " - " << min_size << "))" << " = " << answer + K + (bundle_count * (max_size - min_size)) << endl;
                answer += K + (bundle_count * (max_size - min_size));
                min_size = size;
                max_size = size;
                bundle_count = 1;
            }

            // 그게 아니면, 기존 박스에 넣는다
            else {
                cout << size << "는 기존 박스에 그대로 들어감" << endl;
                min_size = tmp_min_size;
                max_size = tmp_max_size;

                bundle_count++;

                // 기존 박스에 넣었는데, 박스가 꽉 찼다면 이제 포장하기
                if (bundle_count == m) {
                    cout << "박스가 다 차서 새로 포장 시작해야 함" << endl;
                    cout << "현재 비용은 " << answer << " + " << K << " + (" << bundle_count << " * (" << max_size << " - " << min_size << "))" << " = " << answer + K + (bundle_count * (max_size - min_size)) << endl;
                    answer += K + (bundle_count) * (max_size - min_size);
                    bundle_count = 0;
                }
            }
        }
    }

    // 끝났다면, 마지막 남은 박스까지 포장해준다
    if (bundle_count != 0) {
        answer += K + (bundle_count * (max_size - min_size));
    }
        

    cout << answer << endl;
    return 0;
}