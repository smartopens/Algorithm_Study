// 2169 �κ� �����ϱ�
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_NM = 1000;
const int MIN_INF = -213456789;

int dr[3] = { 0, 1, 0 }; // ��, ��, ��
int dc[3] = { -1, 0, 1 };

int MAP[MAX_NM][MAX_NM]; // �� ������ ��ġ
int visited[MAX_NM][MAX_NM]; // �� ������ �湮���� ���
int dp[MAX_NM][MAX_NM][3]; // dp - �� ������ ��� �������� ���ԳĿ� ���� ��ġ �ִ밪
int N, M; // ���� ������

// (cr, cc) ������ dir �������� ������ �� ��ġ ������ �ִ밪
int dfs(int cr, int cc, int dir) {
	// ���� ������ ���޽� �ش� ������ ��ġ���� ����
	if (cr == N - 1 && cc == M - 1) return dp[cr][cc][dir] = MAP[cr][cc];
	// �̹� �ִ밪�� ã�Ҵٸ� ��ȯ
	if (dp[cr][cc][dir] != MIN_INF) return dp[cr][cc][dir];

	visited[cr][cc] = 1; // (cr, cc) ���� �湮 ���

	int bValue = MIN_INF;
	for (int i = 0; i < 3; i++) { // ����, �Ʒ�, ���������� ���� ������ Ž��
		int nr = cr + dr[i];
		int nc = cc + dc[i];
		
		if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue; // ���� ���� ����
		if (visited[nr][nc] > 0) continue; // ��湮 ������ ����

		// ��, (cr, cc)���� �� �� �ִ� 3 ������ �ִ�
		// �� ������κ��� ��ȯ���� �� �� �ִ밪�� (cr, cc)�� ��ġ�� ���ϸ�
		// (cr, cc)�������� (N-1, M-1) ������ ��ġ ������ �ִ밡 �ȴ� (Top-down ���)
		bValue = max(bValue, dfs(nr, nc, i));
	}

	visited[cr][cc] = 0; // (cr, cc) ���� �湮 ��� ����

	return dp[cr][cc][dir] = MAP[cr][cc] + bValue; // �ִ밪 �����ϸ� ��ȯ
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			
			// dp �迭 �ʱ�ȭ
			for (int k = 0; k < 3; k++) {
				dp[i][j][k] = MIN_INF;
			}
		}
	}

	// (0, 0)���� ����
	dfs(0, 0, 0);

	// output - (0, 0)���� �����Ͽ� (N-1, M-1) ���� �����ϴµ� ������ ��ġ�� �ִ밪
	cout << dp[0][0][0] << "\n";

	return 0;
}