/* 빙산 */
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define MAX_N 300
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 1, 0, 0 };
int cdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N]; // 지도
int visited[MAX_N][MAX_N]; // 방문여부 저장

int N, M; // 격자 사이즈 (N*M)

void bfs(int r, int c) {
	int TMP[MAX_N][MAX_N] = { 0, }; // 이번 턴에 줄어들 빙산의 높이를 저장

	// bfs탐색을 위한 queue 준비
	queue<pair<int, int>> q;
	q.push({ r, c });

	visited[r][c] = 1; // 방문 표기

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		int cnt = 0; // now칸 기준 4방향을 탐색하여 높이가 0인 칸의 수
		for (int i = 0; i < DIR_NUM; i++) {
			int nr = now.first + rdir[i];
			int nc = now.second + cdir[i];

			// 높이가 0인 칸은 cnt만 세고 지나간다
			// 0인 칸은 bfs 탐색의 대상이 아니다
			if (MAP[nr][nc] == 0) {
				cnt++;
				continue;
			}

			if (visited[nr][nc] == 1) continue; // 기방문한 칸은 무시
			visited[nr][nc] = 1; // 방문 처리
			q.push({ nr, nc });
		}

		TMP[now.first][now.second] = cnt; // 주변에 0인 칸의 개수를 저장
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// 줄어들 빙산의 높이만큼 깎아주기
			MAP[i][j] -= TMP[i][j];
			if (MAP[i][j] < 0) MAP[i][j] = 0; // 음수가 되었다면 0으로 맞춰주기
		}
	}
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	// solve
	int ans = 0; // 탐색 종료되는데 걸린 시간
	while (1) {
		memset(visited, 0, sizeof(visited)); // 매 턴마다 visited 초기화
		int cnt = 0; // 빙산 그룹 개수
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (MAP[i][j] > 0 && visited[i][j] == 0) { // 빙산이 남아있으면서 미방문인 칸부터 탐색
					bfs(i, j); // (i, j)부터 탐색 시작
					cnt++; //빙산 그룹 증가
				}
			}
		}

		// 그룹이 2개 이상이면 탐색 종료
		// 그룹이 1개이면 탐색 계속
		// 그룹이 0개이면 1개였던 그룹이 동시에 사라진 것이므로 탐색 종료
		if (cnt >= 2) break;
		else if (cnt == 0) {
			ans = 0;
			break;
		}

		ans++; // 시간 증가
	}

	// output
	cout << ans;

	return 0;
}