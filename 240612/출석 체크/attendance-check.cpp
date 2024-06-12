#include <iostream>
#include <string>
#include <map>
#include <utility>

using namespace std;

/*
    수업 시작, 끝, 출석 시간이 정해져있다.
    수업 시간 이전에 활동 기록이 있어야 한다. (시작 시간 땡이어도 됨)

    (수업 종료 이후 - 출석 인정 시간 이전)에 활동 기록이 있어야 함(종료 시간, 출석 인정 시간에 있어도 됨)

    1. 학생별로 1번 인정 기준, 2번 인정 기준 만족 여부를 체크할 것
    2. 학생별로 MAP 만들 것.
    2-1. map<string, string> 타입이며, 앞의 값은 학생 이름, 뒤의 값은 출석 여부이다.
    2-2. 출석 여부는 00이 기본이며, 10이면 시작 시간 전에 출석한 것, 01이면 종료 출석한 것, 11이면 모두 출석한 것이다.

    시간값 처리는 String으로 받아 substr(0, 2) + substr(3, 2)를 int로 변환하여 시간값으로 사용할 것 ex)06:00 -> 600, 12:30 -> 1230
*/

int main() {
    int start_time;
    int end_time;
    int ack_time;

    string tmp;
    // 시작 시간 입력받기
    cin >> tmp;
    start_time = stoi(tmp.substr(0, 2) + tmp.substr(3, 2));

    // 종료 시간 입력받기
    cin >> tmp;
    end_time = stoi(tmp.substr(0, 2) + tmp.substr(3, 2));

    // 출석 인정 시간 입력받기
    cin >> tmp;
    ack_time = stoi(tmp.substr(0, 2) + tmp.substr(3, 2));

    int N;
    cin >> N;

    map<string, string> student_check;

    for (int i = 0; i < N; i++) {
        string name, time_str;
        int time_int;
        cin >> time_str >> name;

        time_int = stoi(time_str.substr(0, 2) + time_str.substr(3, 2));

        int checking_value = -1;
        // 현재 시간이 출석 이전 시간 혹은 출석 이후 시간인지 확인
        if (time_int <= start_time) 
            checking_value = 0;
        else if (time_int >= end_time && time_int <= ack_time) 
            checking_value = 1;

        // 체크 시간에 해당되지 않으면 이후 과정은 진행할 필요 없음
        if (checking_value == -1)
            continue;
        
        // Map에 이 이름이 있는지 확인하고, 없으면 추가
        if (student_check.find(name) == student_check.end()) {
            // cout << "이름 존재하지 않으므로 추가함" << endl;
            student_check[name] = "00";
        }

        student_check[name][checking_value] = '1';
        // cout << "값 변경하였음. map[" << name << "] = " << student_check[name] << endl;
    }


    // 다 봤다면, 이제 모든 값을 순회하면서 값이 11인 친구들을 확인한다.
    int answer = 0;
    for (auto iter = student_check.begin(); iter != student_check.end(); iter++) {
        if (iter->second == "11")
            answer++;
    }

    cout << answer << endl;
    return 0;
}