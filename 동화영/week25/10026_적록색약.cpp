// 10026 적록색약
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int dr[4] = { -1, 0, 1, 0 }; // 상좌하우
int dc[4] = { 0, -1, 0, 1 };

int visited[100][100]; // 각 칸에 방문여부를 기록
char MAP[100][100]; // 각 칸의 색상을 저장(RGB)
int N; // 격자의 사이즈

// (r, c) : BFS 시작할 지점의 좌표
// flag : 적록색약의 여부
void bfs(int r, int c, bool flag) {
	queue<pair<int, int>> q;
	q.push({ r, c });
	visited[r][c] = 1;

	while (!q.empty()) {
		pair<int, int> curr = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = curr.first + dr[i];
			int nc = curr.second + dc[i];

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; // 격자의 범위 밖은 무시
			if (visited[nr][nc] > 0) continue; // 기방문 지점은 무시
			
			// 적록색약이 아닌 사람은 RGB 모두를 구분하기에 이전<>다음의 색상이 다른지만을 판단
			// 적록색약인 사람은 RG <> B 로 색상을 구분하기에 이전<>다음의 색상을 B를 기준으로 판단
			if (!flag && MAP[curr.first][curr.second] != MAP[nr][nc]) continue;
			if (flag) {
				if (MAP[curr.first][curr.second] == 'B' && MAP[nr][nc] != 'B') continue;
				else if (MAP[curr.first][curr.second] != 'B' && MAP[nr][nc] == 'B') continue;
			}

			q.push({ nr, nc }); // 다음에 탐색할 지점으로 저장
			visited[nr][nc] = 1;
		}
	}
}

int main() {
	// input
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> MAP[i][j];

	// 적록색약이 아닌 사람
	int ans1 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] == 0) { // 방문하지 않은 칸만 탐색
				bfs(i, j, false); // 적록색약이 아닌 사람으로 flag 구분
				ans1++; // 하나의 구역 탐색 완료
			}
		}
	}

	memset(visited, 0, sizeof(visited));

	// 적록색약인 사람
	int ans2 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] == 0) { // 방문하지 않은 칸만 탐색
				bfs(i, j, true); // 적록색약인 사람으로 flag 구분
				ans2++; // 하나의 구역 탐색 완료
			}
		}
	}

	// output
	cout << ans1 << " " << ans2 << "\n";

	return 0;
}