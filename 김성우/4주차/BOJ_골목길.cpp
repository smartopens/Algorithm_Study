#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define INF 9999999

struct todist {
    int to;
    long long dist;
};

int n, m;
vector<todist> v[101];
vector<int> vrev[101];
long long dist[101];
int visited[101];
int Log[101];
bool cycle = false;
queue<int> q;

void bf() {

    for (int i = 0; i <= n; i++) {
        dist[i] = INF;
    }

    dist[1] = 0;

    for (int i = 1; i <= n; i++) { // n은 싸이클 확인용
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < v[j].size(); k++) {

                int next = v[j][k].to; int d = v[j][k].dist;

                if (dist[j] != INF && dist[next] > dist[j] + d) { // 최단 거리가 판단 되었을때
                    dist[next] = dist[j] + d;
                    // 여기를 수정해야 한다.
                    // 1. Cycle이 돌고 있는지
                    // 2. 돌고 있다면 그 Cycle이 목적지 까지 가는 길에서 발생하는 것인지
                    if (i == n && visited[next]) cycle = true; 
                    // i == n 일때 이미 경로 탐색이 끝나고 새로운 값이 갱신이 되면 안된다.
                    Log[next] = j; // 경로 저장

                }
            }
        }
    }

}

void sol() {

    q.push(n);
    visited[n] = 1;

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < vrev[now].size(); i++) {

            int next = vrev[now][i];

            if (!visited[next]) {
                visited[next] = 1;
                q.push(next);
            }
        }
    }

    bf(); // 함수 시작

    


}

void input() {

    cin >> n >> m;
    int from, to, dist;
    for (int i = 0; i < m; i++) {
        cin >> from >> to >> dist;
        v[from].push_back({ to, - dist }); // 최대값을 구하기 위해서 경로를 - 를 해서 최소값을 찾으면 된다
        vrev[to].push_back(from); // 이건 시작 ~ 끝까지 경로가 있는지 판단하기 위함
    }


}

int main() {

    input();

    sol();


    
    if (cycle) {
        cout << -1;
    }
    else {
        vector<int> ansv; int ans = n;
        while (ans >= 1) {
            ansv.push_back(ans);
            ans = Log[ans];
        }
        for (int i = ansv.size() - 1; i >= 0; i--) {
            cout << ansv[i] << ' ';
        }
    }

    return 0;
}
