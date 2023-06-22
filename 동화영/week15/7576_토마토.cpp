/* 토마토 */
#include <iostream>
#include <queue>
using namespace std;
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // 상좌하우
int cdir[DIR_NUM] = { 0, -1, 0, 1 };

// bfs 탐색을 위한 queue와 visited
queue<pair<int, int>> q;
int visited[1000][1000];

int MAP[1000][1000]; // 토마토 상자 - -1:빈칸 0:안익은 토마토 1:익은 토마토
int N, M; // N * M
int unripe; // 익지 않은 토마토의 수
int days; // 소요 시간

int main() {
	// input
	cin >> M >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 0) unripe++; // 익지 않은 토마토의 수 세기
			else if (MAP[i][j] == 1) { // 익은 토마토는 탐색 준비하기
				q.push({ i, j });
				visited[i][j] = 1;
			}
		}
	}

	// 최초 탐색 시작 시 익지 않은 토마토가 하나라도 있다면 while문 시작
	// 없다면 바로 0 출력하러 아래로 가기
	if (unripe != 0) {
		while (!q.empty() && unripe > 0) {
			int sz = q.size(); // 금일 기준 익은 토마토의 수
			days++;
			
			// 일자별로 토마토 탐색하기 -> 소요 일수를 구하기 위함
			for (int i = 0; i < sz; i++) {
				pair<int, int> now = q.front();
				q.pop();

				for (int j = 0; j < DIR_NUM; j++) {
					int nr = now.first + rdir[j];
					int nc = now.second + cdir[j];

					if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue; // 격자 밖은 무시
					if (visited[nr][nc] == 1) continue; // 기방문한 칸은 무시
					if (MAP[nr][nc] == -1) continue; // 토마토가 없는 칸은 무시

					// 다음 탐색할 칸으로 추가
					q.push({ nr, nc });
					visited[nr][nc] = 1;
					unripe--; // (nr, nc)칸은 이제 익었으므로 unripe 감소시키기
				}
			}
		}
	}

	// 탐색 이후에도 익지 않은 토마토가 한개라도 있다면 절대 익을 수 없는 토마토이다
	// -1로 출력 (익은 토마토들을 시작으로 동시에 전체 탐색을 하므로)
	if (unripe != 0) days = -1;

	// output
	cout << days << "\n";

	return 0;
}