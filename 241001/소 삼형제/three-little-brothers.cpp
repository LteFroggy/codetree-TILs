#include <iostream>
#include <unordered_map>
using namespace std;

/*
    세 마리의 소가 방을 드나든다.
    올때마다 이름을 적는데, 가장 많이 들어온 조합이 몇 번 들어왔는지 구하자

    이거 map으로 해서 그냥 세면 될지도..
*/

int main() {
    int N;
    unordered_map<string, int> myMap;

    cin >> N;

    for (int i = 0; i < N; i++) {
        string names;
        getline(cin, names);
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

    cout << names << endl;
    return 0;
}