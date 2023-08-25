// 2169 로봇 조종하기
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_NM = 1000;
const int MIN_INF = -213456789;

int dr[3] = { 0, 1, 0 }; // 왼, 위, 오
int dc[3] = { -1, 0, 1 };

int MAP[MAX_NM][MAX_NM]; // 각 지점의 가치
int visited[MAX_NM][MAX_NM]; // 각 지점의 방문여부 기록
int dp[MAX_NM][MAX_NM][3]; // dp - 각 지점에 어느 방향으로 들어왔냐에 따른 가치 최대값
int N, M; // 격자 사이즈

// (cr, cc) 지점에 dir 방향으로 들어왔을 때 가치 총합의 최대값
int dfs(int cr, int cc, int dir) {
	// 최종 지점에 도달시 해당 지점의 가치만을 저장
	if (cr == N - 1 && cc == M - 1) return dp[cr][cc][dir] = MAP[cr][cc];
	// 이미 최대값을 찾았다면 반환
	if (dp[cr][cc][dir] != MIN_INF) return dp[cr][cc][dir];

	visited[cr][cc] = 1; // (cr, cc) 지점 방문 기록

	int bValue = MIN_INF;
	for (int i = 0; i < 3; i++) { // 왼쪽, 아래, 오른쪽으로 다음 지점을 탐색
		int nr = cr + dr[i];
		int nc = cc + dc[i];
		
		if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue; // 격자 밖은 무시
		if (visited[nr][nc] > 0) continue; // 기방문 지점은 무시

		// 즉, (cr, cc)에서 갈 수 있는 3 방향이 있다
		// 그 지점들로부터 반환받은 값 중 최대값에 (cr, cc)의 가치를 더하면
		// (cr, cc)에서부터 (N-1, M-1) 까지의 가치 총합의 최대가 된다 (Top-down 방식)
		bValue = max(bValue, dfs(nr, nc, i));
	}

	visited[cr][cc] = 0; // (cr, cc) 지점 방문 기록 원복

	return dp[cr][cc][dir] = MAP[cr][cc] + bValue; // 최대값 저장하며 반환
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			
			// dp 배열 초기화
			for (int k = 0; k < 3; k++) {
				dp[i][j][k] = MIN_INF;
			}
		}
	}

	// (0, 0)에서 시작
	dfs(0, 0, 0);

	// output - (0, 0)에서 시작하여 (N-1, M-1) 까지 도달하는데 지나간 가치의 최대값
	cout << dp[0][0][0] << "\n";

	return 0;
}