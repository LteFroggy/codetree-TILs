#include <iostream>
#include <vector>

using namespace std;

/*  
    m개의 지뢰가 서로 다른 격자 위에 숨겨져 있다.
    격자판의 어느 지점을 계속 선택하고, 지뢰가 있는 칸은 선택하지 않는다.
    각 칸을 보고 숫자를 예측해보자.
*/

bool inboard_check(int x, int y, int N) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

int main() {
    int N;
    cin >> N;

    vector<vector<int>> real_board(N, vector<int>(N, 0));
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    for (int i = 0; i < N; i++) {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < N; j++) {
            real_board[i][j] = tmp[j];
        }
    }


    for (int i = 0; i < N; i++) {
        string tmp;
        cin >> tmp;
        
        for (int j = 0; j < N; j++) {
            if (tmp[j] == '.') {
                cout << ".";
                continue;
            }
            
            int mine_count = 0;
            for (int k = 0; k < 8; k++) {
                int y = i + dy[k];
                int x = j + dx[k];

                if (!inboard_check(x, y, N)) {
                    continue;
                }

                if (real_board[y][x] == '*') {
                    mine_count++;
                }
            }

            cout << mine_count;
        }
        cout << endl;
    }

    return 0;
}