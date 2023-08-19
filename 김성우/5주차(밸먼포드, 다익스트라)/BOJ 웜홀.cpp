#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

const int INF = 1000001;

int T; // 주기
int n, m, w;
int sum; // n + m
vector<pair<int, int>> route[510];
int dist[510];
bool cycle = false;
bool ans = false;

void bf(int start) {

	for (int i = 0; i <= n; i++) {
		dist[i] = INF;
	}
	dist[start] = 0;

	for (int i = 1; i <= n; i++) { // sum번째에 변환이 일어난다면 싸이클이 일어난다는 뜻
		for (int cur = 1; cur <= n; cur++) {
			for (int k = 0; k < route[cur].size(); k++) {

				int next_node = route[cur][k].first; int next_dist = route[cur][k].second;

				if (dist[next_node] > next_dist + dist[cur]) {
					dist[next_node] = next_dist + dist[cur];
					if (i == n) cycle = true;
				} 
			}
		}
	}
}

void sol() {

	bf(1);
}

void input() {

	cin >> n >> m >> w;
	for (int i = 0; i < m; i++) {
		int s, e, t;
		cin >> s >> e >> t;
		route[s].push_back({ e, t });
		route[e].push_back({ s, t });
	}

	for (int j = 0; j < w; j++) {
		int s, e, t;
		cin >> s >> e >> t;
		route[s].push_back({ e, -t });
	}

	sum = m + w;

}

int main() {

	cin >> T;

	for (int tc = 1; tc <= T; tc++) {

		// 초기화
		memset(dist, 0, sizeof(dist));
		for (int i = 0; i < 510; i++) {
			while (!route[i].empty()) {
				route[i].pop_back();
			}
		}
		cycle = false;

		input();

		sol();

		if (cycle) ans = true;
		else ans = false;

		if (ans) cout << "YES" << "\n";
		else cout << "NO" << "\n";
	}
}