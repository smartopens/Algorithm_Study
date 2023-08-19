#include<iostream>
#include<queue>
#include<string>
#include<cstring>
using namespace std;

int n;
char map[105][105];
char Gmap[105][105];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
int visited[105][105];
queue<pair<int, int>> q;
int ans1, ans2;

void input() {

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			Gmap[i][j] = map[i][j];
			if (Gmap[i][j] == 'G') Gmap[i][j] = 'R';
		}
	}
}

void Gsol() {

	memset(visited, 0, sizeof(visited));
	while (!q.empty()) q.pop();
	
	int cnt = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == 1) continue;
			visited[i][j] = 1;
			char word;
			word = Gmap[i][j];
			cnt++;

			q.push({ i, j });

			// 인접한 부분을 방문처리
			while (!q.empty()) {

				int row = q.front().first;
				int col = q.front().second;
				q.pop();

				for (int dir = 0; dir < 4; dir++) {
					int nr = row + dr[dir];
					int nc = col + dc[dir];

					if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
					if (visited[nr][nc] == 1) continue;
					if (Gmap[nr][nc] != word) continue;
					if (Gmap[nr][nc] == word) visited[nr][nc] = 1;

					q.push({ nr, nc });

				}
			}
		}
	}

	ans2 = cnt;

}

void sol() {

	int cnt = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == 1) continue;
			visited[i][j] = 1;
			char word;
			word = map[i][j];
			cnt++;

			q.push({ i, j });

			// 인접한 부분을 방문처리
			while (!q.empty()) {

				int row = q.front().first;
				int col = q.front().second;
				q.pop();

				for (int dir = 0; dir < 4; dir++) {
					int nr = row + dr[dir];
					int nc = col + dc[dir];

					if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
					if (visited[nr][nc] == 1) continue;
					if (map[nr][nc] != word) continue;
					if (map[nr][nc] == word) visited[nr][nc] = 1;
					

					q.push({ nr, nc });

				}
			}
		}
	}

	ans1 = cnt;
}

int main() {

	input();

	sol();

	Gsol();

	cout << ans1 << " " << ans2;
}