#include <sstream>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
    단어들이 랜덤으로 N번 주어진다.
    주어진 단어들로 전자사전을 만들고, 검색시에 알파벳 순서대로 주어진 단어들을 보여준다.

    정렬의 시간복잡도는 NlogN
    10^6.5정도니 문제 없긴 함

    탐색에서는 lowerbound와 upperbound를 사용한다.
*/

vector<string> split(string target, char delimeter = ' ') {
    vector<string> result;
    string tmp;

    stringstream ss(target);
    
    while (getline(ss, tmp, delimeter)) {
        result.push_back(tmp);
    }

    return result;
}

int main() {
    int N, T;
    cin >> N >> T;

    vector<string> texts;

    // 문자열 입력받기
    for (int i = 1; i <= N; i++) {
        string tmp;
        cin >> tmp;

        // 순서는 공백과 함께 문자열에 넣어준다.
        tmp += " " + to_string(i);

        texts.push_back(tmp);
    }

    sort(texts.begin(), texts.end());

    // 입력받는 과정이 끝났다면, 이제 탐색한다
    for (int i = 0; i < T; i++) {
        int order;
        string start;

        cin >> order >> start;

        int start_idx = start_idx = lower_bound(texts.begin(), texts.end(), start) - texts.begin();
        int end_idx;

        // end_idx는 목표 문자열의 제일 마지막 알파벳을 바꿔서 비교한다, 단 마지막 알파벳이 z인 경우에는 바꿀 수 없으므로 그냥 한다.
        if (start[start.length() - 1] == 'z') {
            end_idx = texts.size() - 1;
        }

        else {
            int tmp = lower_bound(texts.begin(), texts.end(), start) - texts.begin();
            start[start.length() - 1]++;
            end_idx = lower_bound(texts.begin(), texts.end(), start) - texts.begin();

            // 만약, 원본 문자열의 lower_bound와 마지막 알파벳을 변형한 후의 lower_bound가 같다면 이건 애초에 없는 문장이니, 그냥 -1을 출력한다
            if (tmp == end_idx) {
                cout << -1 << endl;
                continue;
            }

            // lower_bound가 끝에 가면 사이즈와 같아질 수 있으므로 이건 따로 수정해준다.
            if (end_idx == texts.size()) end_idx--;
        }

        

        // 이제 두 인덱스의 차가 몇 개인지 확인한다
        int diff = end_idx - start_idx + 1;
        /*
        cout << "diff : " << diff << ", " << start_idx << ", " << end_idx << endl;
        cout << texts[start_idx] << ", " << texts[end_idx] << endl;
        */

        // 갯수가 충분하지 않다면 -1을 출력한다
        if (diff < order) cout << -1 << endl;
        
        // 그렇지 않다면, 그 문자열을 스페이스 단위로 split해서 뒤의 것을 출력한다.
        else {
            string result = texts[start_idx + order - 1];
            cout << split(result)[1] << endl;
        }
        
    }
    return 0;
}