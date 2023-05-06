/* 말이 되고픈 원숭이 */
#include <iostream>
#include <queue>
using namespace std;
#define MAX_W 200
#define HOR_NUM 8
#define DIR_NUM 4

struct Node {
	int r;
	int c;
	int hcnt;
};

int hrdir[HOR_NUM] = { -2, -1, 1, 2, 2, 1, -1, -2 }; // 말의 움직임
int hcdir[HOR_NUM] = { -1, -2, -2, -1, 1, 2, 2, 1 };
int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // 상좌하우
int cdir[DIR_NUM] = { 0, -1, 0, 1 };

int visited[MAX_W][MAX_W][31] = { 0, }; // 방문 여부 - visited[r][c][a] = 말의 움직임을 a번 사용하여 (r,c)에 도달하는데 걸린 이동 횟수
int MAP[MAX_W][MAX_W]; // 장애물 여부 표기
int H, W; // 격자 사이즈 (H * W)
int K; // 말의 움직임 가능 횟수

int Move() {
	// BFS 준비
	queue<Node> q;

	visited[0][0][0] = 1;
	q.push({ 0, 0, 0 });

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		int cnt = now.hcnt;

		// 도착지점을 발견했다면 반환 (시작지점의 visited 값이 1이었기에 -1 처리하여 반환)
		if (now.r == H - 1 && now.c == W - 1) return visited[H - 1][W - 1][cnt] - 1;

		if (cnt < K) { // 아직 말의 움직임이 가능하다면 말의 움직임으로 이동
			for (int i = 0; i < HOR_NUM; i++) {
				int nr = now.r + hrdir[i];
				int nc = now.c + hcdir[i];

				if (nr < 0 || nc < 0 || nr >= H || nc >= W) continue; // 격자 밖은 무시
				if (MAP[nr][nc] == 1) continue; // 장애물 칸은 이동 불가
				// 현재칸에서 말의 움직임 1을 사용하여 (nr, nc)로 움직일 것이기에
				// (nr, nc)에 도달할 때 말의 움직임 사용횟수는 cnt + 1 이다
				if (visited[nr][nc][cnt + 1] > 0 && visited[nr][nc][cnt + 1] <= visited[now.r][now.c][cnt] + 1) continue;

				// 다음 칸 탐색 예정
				q.push({ nr, nc, cnt + 1 });
				visited[nr][nc][cnt + 1] = visited[now.r][now.c][cnt] + 1;
			}
		}

		// 원숭이의 움직임은 항상 가능
		for (int i = 0; i < DIR_NUM; i++) {
			int nr = now.r + rdir[i];
			int nc = now.c + cdir[i];

			if (nr < 0 || nc < 0 || nr >= H || nc >= W) continue; // 격자 밖은 무시
			if (MAP[nr][nc] == 1) continue; // 장애물 칸은 이동 불가
			// 원숭이의 움직임이기에 말의 움직임 사용 횟수와는 무관
			if (visited[nr][nc][cnt] > 0 && visited[nr][nc][cnt] <= visited[now.r][now.c][cnt] + 1) continue;

			// 다음 칸 탐색 예정
			q.push({ nr, nc, cnt });
			visited[nr][nc][cnt] = visited[now.r][now.c][cnt] + 1;
		}
	}


	return -1;
}

int main() {
	// input
	cin >> K >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> MAP[i][j];
		}
	}

	// solve & output
	cout << Move() << "\n";

	return 0;
}