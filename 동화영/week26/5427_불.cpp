// 5427 불
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, -1, 0, 1 };

queue<pair<int, int>> q;
int MAP[1000][1000]; // 지도 0:빈공간, -1:벽, 1~:불의 발생 시간
int visited[1000][1000]; // 상근이의 방문 여부
pair<int, int> sPoint; // 상근이의 시작 위치
int H, W; // 격자 사이즈

// 불이 번져나가는 시각 측정 (BFS)
void bfsFire() {
	// 각 지점에 번지는 시간을 기록해야 되므로
	// cnt 변수를 1씩 증가시키며 매 초에 번져간 위치를 기록
	int cnt = 1;
	while (!q.empty()) {
		cnt++;
		int sz = q.size();

		for (int i = 0; i < sz; i++) {
			pair<int, int> curr = q.front();
			q.pop();

			for (int j = 0; j < 4; j++) {
				int nr = curr.first + dr[j];
				int nc = curr.second + dc[j];

				if (nr < 0 || nc < 0 || nr >= H || nc >= W) continue; // 격자 밖은 무시
				if (MAP[nr][nc] != 0) continue; // 벽이거나 이미 불이 번졌다면 무시

				q.push({ nr, nc });
				MAP[nr][nc] = cnt;
			}
		}
	}
}

// 상근이의 탈출 시도 (BFS)
int runSang() {
	int ret = 1;
	memset(visited, 0, sizeof(visited));
	visited[sPoint.first][sPoint.second] = 1; // 상근이의 초기위치에서 시작
	q.push({ sPoint.first, sPoint.second });
	
	while (!q.empty()) {
		ret++;
		int sz = q.size();

		for (int i = 0; i < sz; i++) {
			pair<int, int> curr = q.front();
			q.pop();

			for (int j = 0; j < 4; j++) {
				int nr = curr.first + dr[j];
				int nc = curr.second + dc[j];

				if (nr < 0 || nc < 0 || nr >= H || nc >= W) { // 무사히 격자 밖으로 빠져나갔다면
					while (!q.empty()) q.pop(); // queue 데이터 비우기
					return ret - 1; // 소요 시간을 반환 (1초부터 시작했으므로 -1 처리)
				}

				if (MAP[nr][nc] == -1) continue; // 벽은 진입 불가
				if (visited[nr][nc] > 0) continue; // 기방문 지점은 진입 불가
				// ret초에 진입하려는 칸에 불이 번진 시점이 ret 이하라면
				// 즉, 상근이가 (nr, nc)에 진입하기 전에 이미 불이 번졌다면 진입 불가
				// ret초마다 (불 번짐 -> 상근이 이동) 순서로 생각
				if (MAP[nr][nc] > 0 && MAP[nr][nc] <= ret) continue;

				q.push({ nr, nc });
				visited[nr][nc] = ret;
			}
		}
	}

	return -1; // 탈출 불가
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// init & input
		memset(MAP, 0, sizeof(MAP));
		cin >> W >> H;

		char inp;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> inp;
				if (inp == '@') { // 상근이의 초기위치
					sPoint = { i, j }; // 저장
					MAP[i][j] = 0; // 빈 공간으로 생각
					continue;
				}
				else if (inp == '*') { // 불의 초기 위치
					q.push({ i, j }); // queue에 저장
				}

				MAP[i][j] = inp == '.' ? 0 : inp == '#' ? -1 : 1; // 각 지점을 MAP에 저장
			}
		}

		bfsFire(); // 불이 번져나가는 시각 측정
		int time = runSang(); // 상근이의 탈출 시도

		// output
		if (time > 0) cout << time << "\n"; // 탈출 성공 시 소요 시간 출력
		else cout << "IMPOSSIBLE\n"; // 탈출 불가 시 IMPOSSIBLE 출력
	}

	return 0;
}


/*
1
5 6
*#.##
#...#
#...#
#...#
#.@.#
#####
*/