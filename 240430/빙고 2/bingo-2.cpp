#include <iostream>
#include <utility>
#include <vector>
#include <map>

using namespace std;

/*
    1부터 25까지의 자연수가 이루어진다.
    숫자 순서대로 지울 때, 직선 3개가 만들어졌을 때가 언제인지 보자

    빙고는 가로, 세로, 대각선이 있다. 대각선은 2개 뿐이므로, i = j인 경우에는 A대각선, i + j = 4인 경우에는 B대각선에 주면 된다.
    가로 세로 칸마다 빙고값을 주자.

    그럼 위치는 어떻게 빨리 찾을까??? Hash로 저장하고 값을 찾자
*/

int main() {
    vector<int> row_bingo(5, 0);
    vector<int> col_bingo(5, 0);
    vector<int> extra_bingo(2, 0);
    map<int, pair<int, int>> map;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int tmp;
            cin >> tmp;
            map.insert(make_pair(tmp, make_pair(i, j)));
        }
    }

    int bingo_count = 0;
    int count = 0;
    while (++count) {
        int tmp;
        cin >> tmp;
        // 입력받아서 가로, 세로 값 얻기
        int i = map[tmp].first;
        int j = map[tmp].second;
        // cout << "입력받은 값은 " << tmp << endl;
        // cout << i+1 << "번째 행, " << j+1 << "번째 열에 존재함" << endl;

         
        // 각 가로, 세로 열에 해당하는 값 추가해주기
        if (++(row_bingo[i]) == 5) {
            bingo_count++;
        }

        if (++(col_bingo[j]) == 5) {
            bingo_count++;
        }
        // cout << i+1 << "번째 가로 값이 " << row_bingo[i] << "로 증가" << endl;
        // cout << j+1 << "번째 세로 값이 " << col_bingo[j] << "로 증가" << endl;

        // 대각선 빙고 보기
        if (i == j) {
            if (++extra_bingo[0] == 5) {
                bingo_count++;
            }
            // cout << "대각선 1번 값도 1 증가하여 " << extra_bingo[0] << "이 됨" << endl;
        }

        if (i + j == 4) {
            if (++extra_bingo[1] == 5) {
                bingo_count++;
            }
            // cout << "대각선 2번 값도 1 증가하여 " << extra_bingo[1] << "이 됨" << endl;
        }

        if (bingo_count >= 3) {
            break;
        }
    }

    cout << count << endl; 
    return 0;
}