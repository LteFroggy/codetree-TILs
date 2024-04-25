#include <iostream>
#include <vector>

using namespace std;

/* 


    2라면?
    0
    2   1

    0
    8   1
    7   9   2
    6   5   4   3

    0
    1   1
    0   2   2
    9   4   3   3
    8   7   6   5   4
    대각선 줄 먼저 채우고, 아랫줄을 채우고, 첫 줄을 채운 후에 이를 반복하면 된다.

    2,1에서부터 3짜리 사각형을 만들려면?
    2,1 
    3,2
    4,3까지 만든다.


        3이라면?
    0
    5   1
    4   3   2
*/  


void make_triangle(vector<vector<int>>& vec, int size, int start_i, int start_j, int start_val) {
    
    // 대각선 줄 채우기
    for (int i = 0; i < size; i++) {
        vec[i + start_i][i + start_j] = start_val++;
    }
    
    // 제일 아래 줄 채우기
    for (int j = size - 2; j >= 0; j--) {
        vec[(size - 1) + start_i][j + start_j] = start_val++;
    }

    // 올라오기
    for (int i = size - 2; i > 0; i--) {
        vec[i + start_i][start_j] = start_val++;
    }

    
    // 더 만들 수 있으면 재귀 진행
    if (size > 3) {
        make_triangle(vec, size - 3, start_i + 2, start_j + 1, start_val);
    }
    
}


int main() {
    int N;
    cin >> N;
    vector<vector<int>> triangle(N, vector<int>(N, -1));

    make_triangle(triangle, N, 0, 0, 0);

    for (auto v : triangle) {
        for(auto v_ : v) {
            if (v_ != -1) {
                cout << v_ % 10 << " ";
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    return 0;
}