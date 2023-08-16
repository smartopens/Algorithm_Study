// 5427 ��
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, -1, 0, 1 };

queue<pair<int, int>> q;
int MAP[1000][1000]; // ���� 0:�����, -1:��, 1~:���� �߻� �ð�
int visited[1000][1000]; // ������� �湮 ����
pair<int, int> sPoint; // ������� ���� ��ġ
int H, W; // ���� ������

// ���� ���������� �ð� ���� (BFS)
void bfsFire() {
	// �� ������ ������ �ð��� ����ؾ� �ǹǷ�
	// cnt ������ 1�� ������Ű�� �� �ʿ� ������ ��ġ�� ���
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

				if (nr < 0 || nc < 0 || nr >= H || nc >= W) continue; // ���� ���� ����
				if (MAP[nr][nc] != 0) continue; // ���̰ų� �̹� ���� �����ٸ� ����

				q.push({ nr, nc });
				MAP[nr][nc] = cnt;
			}
		}
	}
}

// ������� Ż�� �õ� (BFS)
int runSang() {
	int ret = 1;
	memset(visited, 0, sizeof(visited));
	visited[sPoint.first][sPoint.second] = 1; // ������� �ʱ���ġ���� ����
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

				if (nr < 0 || nc < 0 || nr >= H || nc >= W) { // ������ ���� ������ ���������ٸ�
					while (!q.empty()) q.pop(); // queue ������ ����
					return ret - 1; // �ҿ� �ð��� ��ȯ (1�ʺ��� ���������Ƿ� -1 ó��)
				}

				if (MAP[nr][nc] == -1) continue; // ���� ���� �Ұ�
				if (visited[nr][nc] > 0) continue; // ��湮 ������ ���� �Ұ�
				// ret�ʿ� �����Ϸ��� ĭ�� ���� ���� ������ ret ���϶��
				// ��, ����̰� (nr, nc)�� �����ϱ� ���� �̹� ���� �����ٸ� ���� �Ұ�
				// ret�ʸ��� (�� ���� -> ����� �̵�) ������ ����
				if (MAP[nr][nc] > 0 && MAP[nr][nc] <= ret) continue;

				q.push({ nr, nc });
				visited[nr][nc] = ret;
			}
		}
	}

	return -1; // Ż�� �Ұ�
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
				if (inp == '@') { // ������� �ʱ���ġ
					sPoint = { i, j }; // ����
					MAP[i][j] = 0; // �� �������� ����
					continue;
				}
				else if (inp == '*') { // ���� �ʱ� ��ġ
					q.push({ i, j }); // queue�� ����
				}

				MAP[i][j] = inp == '.' ? 0 : inp == '#' ? -1 : 1; // �� ������ MAP�� ����
			}
		}

		bfsFire(); // ���� ���������� �ð� ����
		int time = runSang(); // ������� Ż�� �õ�

		// output
		if (time > 0) cout << time << "\n"; // Ż�� ���� �� �ҿ� �ð� ���
		else cout << "IMPOSSIBLE\n"; // Ż�� �Ұ� �� IMPOSSIBLE ���
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