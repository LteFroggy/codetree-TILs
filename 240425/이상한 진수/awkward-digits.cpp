#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>

using namespace std;

/*
    N을 2진법으로 바꾸고, 한 숫자만 바꾼 a와 3진법으로 바꾸고 한 숫자만을 바꾼 b가 주어진다.

    원래 수를 찾아보자.

    1. 이진법의 수 제일 앞 수가 0이라면 답을 바로 알 수 있으므로, 그걸 보고 풀어낸다
    2. 삼진법의 수 제일 앞 수가 0이라면, 비교를 조금만 해도 알아낼 수 있다.
    3. 각 진법에 따라 가능한 숫자의 리스트가 나온다. 이를 이용해서 겹치는 숫자의 리스트를 찾아낼 수 있다.

    1010을 받았을 경우, 제일 앞 자리 수가 1이므로 제일 앞 자리는 바뀌지 않았을 것이라 가정할 수 있다.
    따라서 1010에 대해, 모든 변화를 체크하면서 가능한 경우의 수를 다 저장한다.

    1010 = 10에 대하여

    1110 = 14
    1000 = 8
    1011 = 11이 되는 것. 각 숫자당 한번씩만 변화가 가능하므로 이진수의 길이에 비례하는 개수가 나온다.
    최대값이 10^9이고 이는 대략 2^30정도에 해당하므로 총 30가지의 경우의 수가 나올 것

    3진법의 경우에도 
    212 = 23에 대하여

    112 = 14
    222 = 26
    202 = 20
    201 = 22
    200 = 21
    과 같은 리스트가 나오고,
    
    14가 겹치므로 이를 이용하는 것.
*/

// string의 이진수를 풀어주는 함수
int solve_binary(string val) {
    int result = 0;

    for (int i = 0; i < val.size(); i++) {
        result += int(val[i] - '0') * pow(2, val.size() - i - 1);
    }

    return result;
}

// 이진수 값을 보고 가능한 리스트를 추려주는 함수
vector<int> getList_binary(string val) {
    vector<int> possible_list;
    int result = solve_binary(val);

    for (int i = 1; i < val.size(); i++) {
        // 어떤 자리의 값이 0이었으면 1이었다고 가정하고 list에 추가, 그 반대면 0이었다고 가정하고 list에 추가
        int possible_value = (val[i] == '0' ? result + pow(2, val.size() - i - 1) : result - pow(2, val.size() - i - 1));
        possible_list.push_back(possible_value);
    }

    return possible_list;
}

int solve_3(string val) {
    int result = 0;

    for (int i = 0; i < val.size(); i++) {
        result += int(val[i] - '0') * pow(3, val.size() - i - 1);
    }

    return result;
}

// 삼진수 값을 보고  가능한 리스트를 추려주는 함수
vector<int> getList_3(string val) {
    int val_list[] = {0, 1, 2};
    int result = solve_3(val);

    vector<int> possible_list;
    int for_start;
    int for_end;
    // 첫 수가 0이라면, 첫 수가 바뀐 것이 확실하므로 첫 수만 보면 됨
    if (val[0] == 0) {
        for_start = 0;
        for_end = 1;
    }

    else {
        for_start = 0;
        for_end = val.size();
    }  

    // 각 자리수에 대해서 0, 1, 2가 들어갔을 경우를 모두 체크해야 한다.
    // 한 자리마다 3번의 반복을 돌며 0, 1, 2인 경우를 모두 본다.
    for (int i = for_start; i < for_end; i++) {
        for (int k = 0; k < 3; k++) {
            if (val[i] - '0' == val_list[k]) {
                continue;
            }
            else {
                int possible_value = result + (val_list[k] - int(val[i] - '0')) * pow(3, val.size() - i - 1);
                possible_list.push_back(possible_value);
            }
        }
    }

    return possible_list;
}


int main() {
    int answer = 0;
    string val_2;
    string val_3;
    cin >> val_2;
    cin >> val_3;

    // 2진수 첫 글자가 0이라면 답 알아내기
    if (val_2[0] == 0) {
        val_2[0] = '1';
        answer = (solve_binary(val_2));
        cout << answer << endl;
        return 0;
    }

    // 2진수에서 가능한 숫자 리스트 찾고 map에 넣기
    vector<int> list_2 = getList_binary(val_2);
    map<int, int> map;
    for (auto v : list_2) {
        map.insert(make_pair(v, 0));
    }

    /*
    cout << "2에서 가능한 리스트" << endl;
    for (auto v : list_2) {
        cout << v << " ";
    }
    cout << endl;
    */

    // 3진수 가능한 값 모두 가져오기
    vector<int> list_3 = getList_3(val_3);
 
    /*
    cout << "3에서 가능한 리스트" << endl;
    for (auto v : list_2) {
        cout << v << " ";
    }
    cout << endl;
    */

    for (auto val : list_3) {
        if (map.find(val) != map.end()) {
            cout << val << endl;
            break;
        }
    }
    return 0;
}