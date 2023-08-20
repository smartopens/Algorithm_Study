// 10026 ���ϻ���
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int dr[4] = { -1, 0, 1, 0 }; // �����Ͽ�
int dc[4] = { 0, -1, 0, 1 };

int visited[100][100]; // �� ĭ�� �湮���θ� ���
char MAP[100][100]; // �� ĭ�� ������ ����(RGB)
int N; // ������ ������

// (r, c) : BFS ������ ������ ��ǥ
// flag : ���ϻ����� ����
void bfs(int r, int c, bool flag) {
	queue<pair<int, int>> q;
	q.push({ r, c });
	visited[r][c] = 1;

	while (!q.empty()) {
		pair<int, int> curr = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = curr.first + dr[i];
			int nc = curr.second + dc[i];

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; // ������ ���� ���� ����
			if (visited[nr][nc] > 0) continue; // ��湮 ������ ����
			
			// ���ϻ����� �ƴ� ����� RGB ��θ� �����ϱ⿡ ����<>������ ������ �ٸ������� �Ǵ�
			// ���ϻ����� ����� RG <> B �� ������ �����ϱ⿡ ����<>������ ������ B�� �������� �Ǵ�
			if (!flag && MAP[curr.first][curr.second] != MAP[nr][nc]) continue;
			if (flag) {
				if (MAP[curr.first][curr.second] == 'B' && MAP[nr][nc] != 'B') continue;
				else if (MAP[curr.first][curr.second] != 'B' && MAP[nr][nc] == 'B') continue;
			}

			q.push({ nr, nc }); // ������ Ž���� �������� ����
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

	// ���ϻ����� �ƴ� ���
	int ans1 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] == 0) { // �湮���� ���� ĭ�� Ž��
				bfs(i, j, false); // ���ϻ����� �ƴ� ������� flag ����
				ans1++; // �ϳ��� ���� Ž�� �Ϸ�
			}
		}
	}

	memset(visited, 0, sizeof(visited));

	// ���ϻ����� ���
	int ans2 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] == 0) { // �湮���� ���� ĭ�� Ž��
				bfs(i, j, true); // ���ϻ����� ������� flag ����
				ans2++; // �ϳ��� ���� Ž�� �Ϸ�
			}
		}
	}

	// output
	cout << ans1 << " " << ans2 << "\n";

	return 0;
}