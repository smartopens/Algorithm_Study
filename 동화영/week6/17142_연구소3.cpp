/* 연구소 3 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX_N 50
#define DIR_NUM 4

struct Node {
	int y;
	int x;
};

vector<Node> virus; // 바이러스의 위치 정보
vector<int> target; // 뽑힌 M개의 바이러스

int ydir[DIR_NUM] = { -1, 1, 0, 0 }; // 상하좌우
int xdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N]; // 연구소의 맵
int N, M; // N: 연구소의 사이즈, M: 선택할 바이러스의 수

int aCnt; // 벽을 제외한 구간의 수
int ans; // 최소 시간

// M개의 바이러스를 선택한 후 들어왔다
// 이제 퍼지는데 걸리는 시간을 계산한다
int bfs() {
	int ret = 0; // 걸린 시간

	int cnt = 0; // 감염된 칸의 수 (이 칸이 aCnt와 동일해야 전 지역에 퍼졌다고 판단)
	int visited[MAX_N][MAX_N] = { 0, }; // 각 칸에 퍼지는데 걸린 시간을 저장
	queue<Node> q;

	// 금번에 활성화된 바이러스들에서 시작 처리
	for (int i = 0; i < virus.size(); i++) {
		if (target[i] == 1) {
			Node t = virus[i];
			visited[t.y][t.x] = 1;
			q.push({ t.y, t.x });
			cnt++;
		}
	}

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) { // 인접한 4방향으로 퍼진다
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // 격자 밖은 무시
			if (MAP[ny][nx] == -1) continue; // 벽은 진입불가

			if (visited[ny][nx] > 0) continue; // 이미 방문한 칸은 무시

			// 이제 여기는 방문해도 되는 칸이다
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny, nx });
			cnt++;

			// 해당 칸이 바이러스가 아니라면 걸린 최종 시간을 갱신
			// 해당 칸이 바이러스라면 갱신할 필요 X
			if(MAP[ny][nx] != 2) ret = visited[ny][nx];
		}
	}

	if (cnt < aCnt) return -1; // 모든 칸에 전염되지 않은 경우 -1 리턴
	
	if (ret == 0) return 0; // 모든 칸에 전염이 되긴 했으나, 소요시간이 0인 경우 - 비활성화 바이러스로 꽉 참

	return ret - 1; // 시작 지점을 1로 시작했으므로 -1 해주기
}

int main() {
	// input
	cin >> N >> M;

	aCnt = N * N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];

			if (MAP[i][j] == 1) { // 벽
				MAP[i][j] = -1;
				aCnt--;
			}
			else if (MAP[i][j] == 2) { // 바이러스
				virus.push_back({ i,j });
			}
		}
	}

	// 조합 돌리기 위한 vector
	// 1: 활성화, 0: 비활성화
	for (int i = 0; i < virus.size() - M; i++) target.push_back(0);
	for (int i = 0; i < M; i++) target.push_back(1);

	ans = 21e8;
	
	do {
		int sec = bfs(); // 이번에 바이러스가 퍼지는데 걸린 시간

		// 전 지역에 바이러스가 퍼진 케이스 중에 최소 시간을 갱신
		if (sec != -1 && sec < ans) ans = sec;
	} while (next_permutation(target.begin(), target.end())); // 활성화시킬 바이러스 M개를 선택한다

	// 단 한번도 갱신이 안됐다면 바이러스 퍼뜨리기 실패 -> -1 출력
	if (ans == 21e8) ans = -1;
	cout << ans;

	return 0;
}}