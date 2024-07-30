#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    길이 L짜리 줄이 있음. 점도 N개 있음.

    줄을 특정 위치 기준으로 맞닿게 접었을 때, 접은 기점을 기준으로 오른쪽 점들이 왼쪽과 겹쳐지도록 하는 서로 다른 접히는 지점의 수 구하기

    접었을 때 만나지 못하는 점이 없어야 하고, 끝점은 접는 지점이 될 수 없다.
    점이 있는 곳을 접으면, 그 위치 점은 잘 맞닿앗다고 친다.
    왼쪽 줄과 오른쪽 줄이 겹치지 않으면, 그 부분은 검사할 필요가 없다.

    중간점으로부터의 "거리"가 동일해야만 두 점이 겹쳐진다.
    그런데, 중간점은 모든 실수 값이 될 수 있으므로 점 기준으로 접히는 자리를 찾는 것이 현명하다.    
    
    가장 오른쪽 점 A를 잡는다.
    그 다음 점 B, C, D와의 중간점을 본다(중간점의 좌표가 B보다 크지 않을 경우에만!)
    각 중간점에서 접어서 모든 점이 겹치는지 체크해본다.
    
    다음 점을 잡아 반복한다.
*/

int main() {
    int N, L;
    cin >> N >> L;
    vector<int> points(N);

    // 점 points에 집어넣은 후 정렬
    for (int i = 0; i < N; i++) {
        cin >> points[i];
    }

    sort(points.begin(), points.end());

    int answer(0);
    // 이제 점을 하나씩 꺼내면서 겹치는지 확인하기
    // 마지막 점(L 위치의 점)은 거기서 접힐 수가 없으니 볼 필요가 없다.
    for (int i = 0; i < N - 1; i++) {
        // 현재 보고 있는 점의 index가 i이다.
        int point_now = points[i];
        int point_next = points[i + 1];

        // cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        // cout << i + 1 << "번째 점 확인 중" << endl;
        // cout << "현재 점의 위치는 " << point_now << endl;
        // cout << "다음 점의 위치는 " << point_next << endl;

        // 이제 이 점 바로 왼쪽의 있는 점과 중간점을 모두 찾아 접어볼 것이다.   
        // 다음 점과의 중간점 찾아보기
        int j = i + 1;
        double middle_point = double(point_now + points[j]) / 2;

        // 모든 점이 겹치는지 확인하기
        int diff = 0;
        int left_start(j), right_start(i);
        // cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        // cout << i + 1 << "번째 점과 " << j + 1 << "번의 중간점은 " << middle_point << "로, " << point_next << "이하를 만족한다." << endl;
        // cout << i + 1 << " : " << point_now << ", 중간점과의 거리는 " << middle_point - point_now << endl;
        // cout << j + 1 << " : " << points[j] << ", 중간점과의 거리는 " << points[j] - middle_point << endl;
        
        // 점 하나하나가 일치하는지 확인
        bool flag = true;
        while (true) {
            diff++;
            // 줄의 길이가 넘어가면 더 볼 필요 없음.
            if (left_start + diff >= N || right_start - diff < 0) break;

            // 그렇지 않으면 추가로 확인한다.
            double left_loc = points[left_start + diff] - middle_point;
            double right_loc = middle_point - points[right_start - diff];
            // cout << "----" << endl;
            // cout << right_start - diff + 1 << " : " << points[right_start - diff] << ", 중간점과의 거리는 " << right_loc << endl;
            // cout << left_start + diff + 1 << " : " << points[left_start + diff] << ", 중간점과의 거리는 " << left_loc << endl;

            // 만약 두 점이 겹치지 못한다면, flag를 false로 바꾸고 반복문을 종료한다.
            if (left_loc != right_loc) {
                // cout << "다르므로 종료" << endl << endl;
                flag = false;
                break;
            }
            // cout << "같으므로 다음 점 체크" << endl;
        }

        // while문이 끝났을 때 flag가 true이면, 모든 점이 겹쳐지는 것이므로 answer를 1 증가시킨다.
        if (flag) {
            // cout << "모두 같으므로 answer를 1 증가시킨다" << endl << endl;
            answer++;
        }

        // 다음 점을 기준으로 접었을 때를 기준으로 생각해보기
        // 근데 다음 점이 마지막 점이면, 접으면 안 됨
        if (i + 1 == N - 1) continue;
        // 다음 점과의 중간점 찾아보기
        j = i + 2;
        middle_point = points[i + 1];

        // 모든 점이 겹치는지 확인하기
        diff = -1;
        left_start = j;
        right_start = i;
        // cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        // cout << j << "번 점을 기준으로 접었을 때이다. 중간점은 " << middle_point << endl;
        
        // 점 하나하나가 일치하는지 확인
        flag = true;
        while (true) {
            diff++;
            // 줄의 길이가 넘어가면 더 볼 필요 없음.
            if (left_start + diff >= N || right_start - diff < 0) break;

            // 그렇지 않으면 추가로 확인한다.
            double left_loc = points[left_start + diff] - middle_point;
            double right_loc = middle_point - points[right_start - diff];
            // cout << "----" << endl;
            // cout << right_start - diff + 1 << " : " << points[right_start - diff] << ", 중간점과의 거리는 " << right_loc << endl;
            // cout << left_start + diff + 1 << " : " << points[left_start + diff] << ", 중간점과의 거리는 " << left_loc << endl;

            // 만약 두 점이 겹치지 못한다면, flag를 false로 바꾸고 반복문을 종료한다.
            if (left_loc != right_loc) {
                // cout << "다르므로 종료" << endl << endl;
                flag = false;
                break;
            }
            // cout << "같으므로 다음 점 체크" << endl;
        }

        // while문이 끝났을 때 flag가 true이면, 모든 점이 겹쳐지는 것이므로 answer를 1 증가시킨다.
        if (flag) {
            // cout << "모두 같으므로 answer를 1 증가시킨다" << endl << endl;
            answer++;
        }
    }

    

    cout << answer << endl;    
    return 0;
}





/* for문 원본
 // 이제 이 점 바로 왼쪽의 있는 점과 중간점을 모두 찾아 접어볼 것이다.
        for (int j = i + 1; j < i + 2; j++) {
            double middle_point = double(point_now + points[j]) / 2;
            // 대신, 중간점의 좌표가 다음 점의 위치 초과가 되면 안됨. 그럼 다음 점의 영역이 되니까 다음 점에서 체크할 것이기 때문
            if (middle_point > point_next) break;

            // 그렇지 않다면 모든 점이 겹치는지 확인해본다.
            int diff = 0;
            int left_start(j), right_start(i);
            cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
            cout << i + 1 << "번째 점과 " << j + 1 << "번의 중간점은 " << middle_point << "로, " << point_next << "이하를 만족한다." << endl;
            cout << i + 1 << " : " << point_now << ", 중간점과의 거리는 " << middle_point - point_now << endl;
            cout << j + 1 << " : " << points[j] << ", 중간점과의 거리는 " << points[j] - middle_point << endl;
            
            // 점 하나하나가 일치하는지 확인
            bool flag = true;
            while (true) {
                diff++;
                // 줄의 길이가 넘어가면 더 볼 필요 없음.
                if (left_start + diff >= N || right_start - diff < 0) break;

                // 그렇지 않으면 추가로 확인한다.
                double left_loc = points[left_start + diff] - middle_point;
                double right_loc = middle_point - points[right_start - diff];
                cout << "----" << endl;
                cout << right_start - diff + 1 << " : " << points[right_start - diff] << ", 중간점과의 거리는 " << right_loc << endl;
                cout << left_start + diff + 1 << " : " << points[left_start + diff] << ", 중간점과의 거리는 " << left_loc << endl;

                // 만약 두 점이 겹치지 못한다면, flag를 false로 바꾸고 반복문을 종료한다.
                if (left_loc != right_loc) {
                    cout << "다르므로 종료" << endl << endl;
                    flag = false;
                    break;
                }
                cout << "같으므로 다음 점 체크" << endl;
            }

            // while문이 끝났을 때 flag가 true이면, 모든 점이 겹쳐지는 것이므로 answer를 1 증가시킨다.
            if (flag) {
                cout << "모두 같으므로 answer를 1 증가시킨다" << endl << endl;
                answer++;
            }
        }

*/