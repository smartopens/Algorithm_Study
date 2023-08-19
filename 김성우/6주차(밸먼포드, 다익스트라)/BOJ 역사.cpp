#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int INF = 999;

int n, m, s;
int dist[405][405];

void sol() {

	// memcpy(dist, init_dist, sizeof(init_dist));

	for (int mid = 1; mid <= n; mid++) {
		for (int from = 1; from <= n; from++) {
			for (int to = 1; to <= n; to++) {

				dist[from][to] = min(dist[from][to], dist[from][mid] + dist[mid][to]);

			}
		}
	}


}

void input() {



	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = INF;
		}
	}

	for (int i = 0; i < m; i++) {
		int from, to;
		cin >> from >> to;
		dist[from][to] = 1;
		
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();

	sol();
	/*
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << dist[i][j] << " ";
		}
		cout << "\n";
	}
	*/
	int ans = 0;
	cin >> s;
	for (int i = 0; i < s; i++) {
		int front = 0; int back = 0;
		cin >> front >> back;
		if (dist[front][back] < INF) ans = -1;
		else if (dist[front][back] >= INF) {
			if (dist[back][front] < INF) ans = 1;
			else if (dist[back][front] >= INF) ans = 0;
		}

		cout << ans << "\n";
	}

	

}