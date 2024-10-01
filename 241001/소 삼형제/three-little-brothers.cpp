#include <iostream>
#include <unordered_map>
using namespace std;

/*
    세 마리의 소가 방을 드나든다.
    올때마다 이름을 적는데, 가장 많이 들어온 조합이 몇 번 들어왔는지 구하자

    이거 map으로 해서 그냥 세면 될지도..
*/

// 세 이름을 사전순으로 하나의 문자열로 합쳐주는 함수
string getOrder(string name1, string name2, string name3);

int main() {
    int N;
    unordered_map<string, int> myMap;

    cin >> N;

    for (int i = 0; i < N; i++) {
        string name1, name2, name3;
        cin >> name1 >> name2 >> name3;

        // 서로 같은 조합이 순서가 달라 계산되지 않는 문제를 피하기 위해, 이름을 정렬한다.
        string names = getOrder(name1, name2, name3);
        
        if (myMap.find(names) == myMap.end()) 
            myMap.insert({names, 1});
        else 
            myMap[names]++;
    }

    // 제일 많이 나온 조합 찾기
    int maxCount(0);
    string names;

    for (auto v : myMap) {
        if (maxCount < v.second) {
            maxCount = v.second;
            names = v.first;
        }
    }

    cout << maxCount << endl;
    return 0;
}


string getOrder(string name1, string name2, string name3) {
    string names;
    if (name1 > name2) {
        if (name2 > name3) 
            names = name3 + name2 + name1;
        else {
            if (name1 > name3) 
                names = name2 + name3 + name1;
            else
                names = name2 + name1 + name3;
        }
    }
    else {
        if (name2 > name3) {
            if (name1 > name3) 
                names = name3 + name1 + name2;
            else
                names = name1 + name3 + name2;
        }
        else
            names = name1 + name2 + name3;
    }
    
    return names;
}