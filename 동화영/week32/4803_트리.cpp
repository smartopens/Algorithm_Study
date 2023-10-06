// 4803 Ʈ��
#include <iostream>
#include <vector>
using namespace std;

vector<int> al[501]; //������ ����
int visited[501]; //������ �湮 ����

//before������ Ÿ�� ���� ind�������� Ž�� ����
bool dfs(int ind, int before) {
	visited[ind] = 1; //�湮 ǥ��

	for (int i = 0; i < al[ind].size(); i++) { //ind�� ����� �������� Ž��
		int nxt = al[ind][i];
		if (nxt == before) continue; //�̹� before�� ���ؼ� ind�� �������Ƿ� ����

		if (visited[nxt] != 0) return false; //��湮 ������ �����ߴٸ� ����Ŭ ���� - Ʈ���� �ƴ�
		if (!dfs(nxt, ind)) return false; //nxt�������� dfs Ž��
	}

	return true; //���� ���� �� Ʈ�� �߰�
}

int main() {
	int tc = 0;
	int n, m;
	while (1) {
		//init
		tc++;
		for (int i = 0; i < 501; i++) {
			al[i].clear();
			visited[i] = 0;
		}

		//input
		cin >> n >> m;

		//��������
		if (n == 0 && m == 0) break;

		int a, b;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			al[a].push_back(b); //���� ����
			al[b].push_back(a);
		}

		int cnt = 0; //Ʈ���� ��
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0) { //�̹湮 �������� Ž��
				if (dfs(i, 0)) cnt++; //dfs Ž���� true�� ��쿡�� Ʈ���� ����(false�̸� ����Ŭ �����Ͽ� Ʈ���� �ƴ�)
			}
		}

		//output
		if (cnt == 0) cout << "Case " << tc << ": No trees.\n";
		else if (cnt == 1) cout << "Case " << tc << ": There is one tree.\n";
		else cout << "Case " << tc << ": A forest of " << cnt << " trees.\n";
	}

	return 0;
}