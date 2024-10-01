#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int INF = 1e9;

/*
    여행할 것.
    n개의 도시 연결하는 m개의 간선
    도시는 0 ~ n-1번까지 번호 있고, 방향성 없다.
    두 도시 사이 간선 여러개 가능, 셀프 돌기도 할 수 있다.

    출발지는 항상 0번

    투어는 5개의 명령을 가진다. 
    1)  정보 바탕 그래프 생성 
    2)  id, 매출, 도착지를 적은 여행 상품 만든다
    3)  이미 id를 가지는 상품이 있다면 덮어쓴다.
    4)  조건에 맞는 최적의 여행 상품을 선택해 판매한다. 판매는 이득(판매금 - 드는돈)이 최대가 되어야 하며, 같은 값을 가진 게 여러개라면
        id가 가장 작은 것을 택한다. 여기서 드는돈은 여행 상품의 출발지로부터 목적지까지 도달하기 위한 최소거리이다.
        만약, 도달이 불가능하거나 cost가 이득보다 큰 경우에는 판매 불가가 된다.
        판매 가능 상품 중 가장 우선순위가 높은 것을 팔며, 이것의 id를 출력하고 관리 목록에서 제거한다.
        판매가 불가능하다면 -1을 출력한다
    5) 모든 출발지를 s로 변경하기

    가중치는 음수가 되지 않는다! 그러니 다익스트라로 가능하다.
    그런데, 매번 계산하기에는 overhead가 클지도?.. 그런데 최대 15회이니 괜찮다!
*/

// 한 여행상품의 정보를 저장하기 위한 struct
struct product_info {
    product_info(int a, int b, int c, int d) : id(a), dest(b), revenue(c), profit(d) {};

    int id;
    int dest;
    int revenue;
    int profit;
};

// 여행상품 정렬을 위한 정렬기준을 제시하는 구조체
struct comp {
    bool operator() (product_info a, product_info b) {
        // 이익 기준으로 정렬한다.
        // 둘이 같을 경우에는 id가 작아야 한다.
        if (a.profit == b.profit) 
            return a.id > b.id;

        else 
            return a.profit < b.profit;
    }
};

// 다익스트라 알고리즘을 수행한 최단거리 테이블을 반환해주는 함수
// N은 노드 개수, edges는 각 도시에서 갈 수 있는 도시와 그 거리를 저장한 함수, start는 출발지
vector<int> djikstra(int N, const vector<vector<pair<int, int>>> &edges, int start);

int main() {
    // 일단 개수 입력받기
    int Q;
    cin >> Q;

    // 처음에는 항상 건설이 이루어진다! 이것까지 for문 밖에서 처리한다.
    int N, M;
    // N에 값이 두 번 들어가는건, 건설 명령인 100을 없는 값처럼 처리하기 위함(덮어쓰기)
    cin >> N >> N >> M;
    
    // 각 도시에서 갈 수 있는 간선과 그 값을 기록하는 용도!
    vector<vector<pair<int, int>>> edges(N);

    // 입력값을 받아 edges를 갱신한다
    for (int i = 0; i < M; i++) {
        int start, end, cost;
        cin >> start >> end >> cost;

        // 간선에는 방향성이 없으므로 양쪽 다 넣어줘도 됨
        edges[start].push_back({end, cost});
        edges[end].push_back({start, cost});
    }

    // 먼저 출발지 0을 기준으로 모든 곳까지의 cost를 계산해둔다.
    vector<int> costs = djikstra(N, edges, 0);

    /*
    cout << "초기 거리 벡터" << endl;
    for (auto v : costs) {
        cout << v << " ";
    }
    cout << endl;
    */

    // 여행상품의 가능 여부를 저장하기 위한 배열! id는 최대 30000번까지 가능하니 그렇게 만든다.
    // true라면 현재 상품이 있는 것이고, false라면 없는 것이다.
    // 처음에는 모두 false로 처리한다.
    bool products_bool[30001];
    for (auto &v : products_bool) v = false;
    
    // 여행상품을 편하게 정렬해두기 위한 priority_queue
    // 만들어진 상품들은 이 안에 넣는다.
    priority_queue<product_info, vector<product_info>, comp> products;
    
    // 이제 진짜 명령을 처리하는 부분!
    for (int i = 0; i < Q - 1; i++) {
        int command;
        cin >> command;

        // 여행 상품 생성 단계이다! 입력값을 받고 저장한다.
        if (command == 200) {
            int id, revenue, dest, profit;
            cin >> id >> revenue >> dest;
            // 먼저 실제 이득을 계산한다.
            // 만약 도착 불가능한 곳이라면, 이득을 음수값으로 한다(판매불가).
            if (costs[dest] == INF) {
                profit = -1;
            }
            // 도착이 가능하면 이득을 계산한다.
            else {
                profit = revenue - costs[dest];
            }
            
            // 결과를 저장한다
            products.push(product_info(id, revenue, dest, profit));
            products_bool[id] = true;

            /*
            cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
            cout << "판매할 상품 생성됨" << endl;
            cout << "번호 : " << id << endl;
            cout << "목적지 : " << dest << endl;
            cout << "수익 : " << revenue << endl;
            cout << "목적지까지의 비용 : " << costs[dest] << endl;
            cout << "이득 : " << profit << endl << endl;

            cout << "현재 가장 팔기 좋은 상품 번호 : " << products.top().id << endl;
            */
        }


        // 여행상품을 취소하는 부분이다! 단순 bool을 false로 바꿔서 판매 불가능이라고 알려주면 된다.
        // 이렇게 했다가 나중에 판매 가능으로 바뀌어버리는 문제는, 주어지는 모든 id가 unique하기 때문에 신경쓸 필요 없다.
        else if (command == 300) {
            int id;
            cin >> id;
            products_bool[id] = false;
        }

        // 여행상품을 판매하는 부분이다!
        else if (command == 400) {
            int id, profit, dest;

            while (!products.empty()) {
                // 지금 팔기 가장 좋은 상품을 찾는다.
                id = products.top().id;
                dest = products.top().dest;
                profit = products.top().profit;

                // 만약 가장 좋은 상품이 단종됐다면, 다시 찾아야 한다.
                if (products_bool[id] == false) {
                    products.pop();
                    continue;
                }
                break;
            }

            // 판매 가능한 상품이 안 남았으면, 판매 불가능하다.
            if (products.empty()) {
                cout << -1 << endl;
            }

            // 찾았다면, 판매 불가능 상품은 아닌지 확인하고 판매한다.
            if (profit != -1) {
                products_bool[id] = false;
                cout << id << endl;
                products.pop();
                /*
                cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
                cout << "상품 판매함" << endl;
                cout << "번호 : " << id << endl;
                cout << "목적지 : " << dest << endl;
                cout << "이득 : " << profit << endl;
                */
            }

            // 판매가 불가능하면 그냥 넘긴다.
            else {
                cout << -1 << endl;
            }
        }

        // 출발지를 바꾼다! priority_queue를 모두 비운 후 다시 계산해야 한다.
        else if (command == 500) {
            int new_point;
            cin >> new_point;
            // 새로운 priority_queue
            priority_queue<product_info, vector<product_info>, comp> temp;

            // 일단 cost테이블을 갱신한다.
            costs = djikstra(N, edges, new_point);

            // 갱신된 cost테이블을 바탕으로 proirity_queue를 갱신한다.
            while (!products.empty()) {
                int id = products.top().id;
                int dest = products.top().dest;
                int revenue = products.top().revenue;
                int profit;
                products.pop();

                // profit을 계산한다
                // 도착 못하는 곳이라면, profit을 -1로 설정한다(판매불가).
                if (costs[dest] == INF) {
                    profit = -1;
                }

                else {
                    profit = revenue - costs[dest];
                }

                temp.push(product_info(id, dest, revenue, profit));
            }

            // 다 갱신 완료했다면, 이제 이걸로 products를 갱신한다
            products = temp;
        }
    }
    return 0;
}


vector<int> djikstra(int N, const vector<vector<pair<int, int>>> &edges, int start) {
    // 각 최소거리를 저장하는 벡터
    vector<int> dist(N, INF);

    // 다익스트라는 현재 방문하지 않은 노드 중 최소 비용을 가진 노드를 방문한다! 이를 위해 정렬을 자동으로 수행해주는 priority_queue 사용
    // 첫 값(정렬기준)은 가는데 드는 비용, 두번째 값은 도시 번호이다.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> myQueue;

    // 먼저, 출발지부터 적용한다
    dist[start] = 0;
    myQueue.push({0, start});

    while (!myQueue.empty()) {
        // 일단 꺼낸다
        int cost_now = myQueue.top().first;
        int city_now = myQueue.top().second;
        myQueue.pop();

        // 만약, 이미 다른 곳에서 내 값을 갱신해줬다면 난 이미 더 적은 코스트로 탐색을 완료했을 것이다.
        // 그러므로 지금 이건 쓸데없는 탐색이기 때문에 제거한다.
        if (dist[city_now] < cost_now) {
            continue;
        }

        for (auto dest : edges[city_now]) {
            int city_next = dest.first;
            int cost_next = cost_now + dest.second;

            // 내가 기존보다 더 짧은 길을 찾았다면, 값을 갱신하고 queue에 넣어준다
            if (cost_next < dist[city_next]) {
                dist[city_next] = cost_next;
                myQueue.push({cost_next, city_next});
            }
        }
    }

    // while문이 끝났으면 반환
    return dist;
}