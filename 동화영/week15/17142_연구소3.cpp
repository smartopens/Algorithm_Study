// 17142 연구소3
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define MAX_N 50

struct NODE {
	int r;
	int c;
};

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, -1, 0, 1 };

vector<NODE> viruses; // 초기 비활성 바이러스들의 위치
vector<int> vec; // 순열을 위한 vector
int MAP[MAX_N][MAX_N]; // 초기 맵
int N, M; // N: 맵 사이즈, M: 활성화시킬 바이러스의 수
int notWall; // 빈 칸의 수

int bfs() {
	int cnt = 0, ret = 1; // cnt: 퍼뜨려진 빈 칸의 수, ret: 소요시간
	// bfs를 위한 셋팅
	int visited[MAX_N][MAX_N] = { 0, };
	queue<NODE> q;

	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == 1) { // 이번 턴에 활성화시킬 바이러스에서 시작
			visited[viruses[i].r][viruses[i].c] = 1;
			q.push({ viruses[i].r, viruses[i].c });
		}
	}

	while (!q.empty()) {
		NODE now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = now.r + dr[i];
			int nc = now.c + dc[i];

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; // 격자 밖은 무시
			if (visited[nr][nc] > 0) continue; // 기방문한 칸은 무시
			if (MAP[nr][nc] == 1) continue; // 벽은 진입 불가

			q.push({ nr, nc }); // 탐색 예정
			if(MAP[nr][nc] == 0) cnt++; // 빈 칸인 곳에 도달시 cnt 증가

			visited[nr][nc] = visited[now.r][now.c] + 1; // 각 칸에 도달하는데 소요시간 저장
			if(MAP[nr][nc] != 2) ret = visited[nr][nc]; // 빈 칸인 경우 소요시간 저장(비활성 바이러스는 상관 X)
		}
	}
	
	if (cnt < notWall) return 213456789; // 모든 칸에 도달 못한 경우
	return ret - 1; // 반환 (1로 시작하였으므로 -1 해서 반환)
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 2) viruses.push_back({ i, j }); // 바이러스 위치 저장
			if (MAP[i][j] == 0) notWall++; // 빈 칸의 수 세기
		}
	}

	int ans = 213456789;; // 답
	// 순열을 위한 벡터 셋팅
	for (int i = 0; i < viruses.size() - M; i++) vec.push_back(0);
	for (int i = 0; i < M; i++) vec.push_back(1);

	// 순열 돌면서 각 케이스별 시뮬레이션
	do {
		int ret = bfs();
		if (ret < ans) ans = ret; // 최소 시간인지 갱신
	} while (next_permutation(vec.begin(), vec.end()));

	// output
	if (ans == 213456789) ans = -1;
	cout << ans << "\n";

	return 0;
}