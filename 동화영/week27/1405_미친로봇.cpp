// 1405 미친로봇
#include <iostream>
using namespace std;

int dr[4] = { 0, 0, 1, -1 }; // 동서남북
int dc[4] = { 1, -1, 0, 0 };

bool visited[30][30]; // 각 지점에 방문여부 (최대 14번 움직이므로 30*30으로 잡았다)
int percentage[4]; // 동서남북 방향으로 이동할 확률을 저장
int N; // 총 이동횟수

/* 문제 회고
맨 처음 이 문제를 접했을 때 잘못 이해했던 부분이 있다.
각 방향으로 이동할 확률에 대해서 이다.
처음에는, 각 방향으로 이동할 확률에 따라 이동이 일어난다고 생각했다. 즉, 매 턴마다 어느 방향으로 이동했는지를 카운팅하여 횟수 자체에 제한을 거는 로직이다.
그런데 생각해보니 확률이라는 것은 각 경우가 "일어날 확률"인 것이다. 즉, 모든 경우가 가능하며 그 경우들에 따라 확률을 곱해주면 되는 것이다.
따라서, "단순한 경로"로 가는 경우만을 탐색하였으며, 각 경우에 대해 확률을 곱해주었다.
*/

double dfs(int r, int c, int depth) {
	if (depth == N) { // N 번 이동을 완료한 경우, 1.0을 반환하여 확률에는 변화가 없게 하였다.
		return 1.0;
	}

	double ret = 0.0; // 현재 (r,c) 지점으로부터 이동하여 얻을 확률
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if (visited[nr][nc]) continue; // 기방문 지점으로 이동하면 "단순한 경로"가 아니다. 따라서, 무시

		visited[nr][nc] = 1; // 방문 표기
		ret += dfs(nr, nc, depth + 1) * ((double)percentage[i] / 100); // i방향으로 이동할 확률과 이동했을 때 이후의 확률을 곱하자
		visited[nr][nc] = 0; // 방문 표기 원복
	}

	return ret;
}

int main() {
	// input
	cin >> N;
	for (int i = 0; i < 4; i++) {
		cin >> percentage[i];
	}

	visited[14][14] = 1; // 30*30 격자의 중앙에서 시작
	printf("%.10f\n", dfs(14, 14, 0)); // 절대/상대 오차는 10^(-9)까지 허용 => 소수점 10자리까지 출력인가 보다 (처음에 소수점 자리 신경 안썼다가 오답이었다..)

	return 0;
}