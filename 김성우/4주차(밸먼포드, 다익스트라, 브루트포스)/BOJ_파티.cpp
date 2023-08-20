#include<iostream>
#include<queue>
#include<vector>
using namespace std;

#define INF 21e8

int n, m, x;
vector<pair<int, int>> route[1001];
int dist[1001];
int rlt[1001];

void Dijikstra(int start) {

	priority_queue<pair<int, int>> pq;

	for (int i = 0; i < n; i++) {
		dist[i] = INF;
	}

	dist[start] = 0;
	pq.push({ start, 0 });

	while (!pq.empty()) {

		int now = pq.top().first;
		int now_dist = - pq.top().second;
		pq.pop();

		for (int i = 0; i < route[now].size(); i++) {

			int next_node = route[now][i].first;
			int next_dist = route[now][i].second + now_dist;

			if (dist[next_node] > next_dist ) {
				dist[next_node] = next_dist;
				pq.push({ next_node, -next_dist });
			}

		}

	}

}

void sol() {

	int sum;

	Dijikstra(x - 1);
	for (int i = 0; i < n; i++) {
		rlt[i] = dist[i];
	}

	for (int i = 0; i < n; i++) {
		if (i == x - 1) continue;
		Dijikstra(i);
		rlt[i] += dist[x - 1];
	}

	Dijikstra(x - 1);

}

void input() {

	cin >> n >> m >> x;
	for (int i = 0; i < m; i++) {
		int from, to, dist = 0;
		cin >> from >> to >> dist;
		route[from - 1].push_back({ to - 1, dist });
	}

}

int main() {

	input();

	sol();

	int ans;
	int max = 0;
	for (int i = 0; i < n; i++) {
		if (rlt[i] > max)
			max = rlt[i];
	}

	ans = max;
	cout << ans;
}