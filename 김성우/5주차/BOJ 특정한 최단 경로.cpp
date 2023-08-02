#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

const int INF = 21e8;

int n, e;
int ans1, ans2;
vector<pair<int, int>> route[810];
int dist[810];
int v1, v2;
bool end_flag = false;
bool end_flag_1 = false;
bool end_flag_2 = false;
int visited[810];

int Dijiksta(int start, int end) {

    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    pq.push({ start, 0 });

    while (!pq.empty()) {

        int now_node = pq.top().first;
        int now_dist = -pq.top().second;

        pq.pop();

        for (int i = 0; i < route[now_node].size(); i++) {

            int next_node = route[now_node][i].first;
            int next_dist = route[now_node][i].second + now_dist;

            if (dist[next_node] > next_dist) {
                dist[next_node] = next_dist;
                pq.push({ next_node, -next_dist });
            }
        }

    }

    if (dist[end] != INF) {
        return dist[end];
    }
    else if (dist[end] == INF) {
        end_flag = true;
        return dist[end];
    }

}

void sol() {

    // flag를 각각 설정한다.

    // v1 먼저
    end_flag = false;
    ans1 = Dijiksta(0, v1 - 1) + Dijiksta(v1 - 1, v2 - 1) + Dijiksta(v2 - 1, n - 1);
    if (end_flag == true)
        end_flag_1 = true;
    // v2 먼저
    end_flag = false;
    ans2 = Dijiksta(0, v2 - 1) + Dijiksta(v2 - 1, v1 - 1) + Dijiksta(v1 - 1, n - 1);
    if (end_flag == true)
        end_flag_2 = true;
}

void input() {

    cin >> n >> e;

    for (int i = 0; i < e; i++) {
        int from, to, dist;
        cin >> from >> to >> dist;

        route[from - 1].push_back({ to - 1, dist });
        route[to - 1].push_back({ from - 1, dist });
    }

    cin >> v1 >> v2;

}

int main() {

    input();

    sol();

    if (end_flag_1 && end_flag_2)
        cout << -1;
    else
        //cout << ans1;
        if (ans1 >= ans2) cout << ans2;
        else cout << ans1;

}
