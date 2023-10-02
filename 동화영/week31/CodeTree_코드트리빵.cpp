#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Person {
	int num; //m��
	int r; //��ġ
	int c;
};

int dr[4] = { -1, 0, 0, 1 }; //���¿���
int dc[4] = { 0, -1, 1, 0 };

queue<Person> people; //������� ���� ��ġ
vector<pair<int, int>> stores; //��ǥ ������
int MAP[16][16]; //0:��ĭ, 1:���̽�ķ��, -1:������ ���̽�ķ��, 2~:timer�п� ������ ������
int n, m; //n:������ ������, m:����� ��
int arrived; //��ǥ �������� ������ ����� ��
int timer; //Ÿ�̸�

//curr����� �̵��� ���� Ž��
//����ġ -> ���������� �̵��� ���� ����� ��η� �� ĭ �̵� ����
//����, BFSŽ���� �ϵ� �� ��κ��� �̵������� �Բ� ����
//BFS Ž�� �Ϸ� ��, ������ Ž���ϸ� ��� �������� �̵������� ��ȯ
int BFS(Person curr) {
	queue<pair<int, int>> q;
	int visited[16][16] = { 0, };
	int dirHistory[16][16] = { 0, }; //�� �̵������� �̵� ����

	visited[curr.r][curr.c] = 1;
	q.push({ curr.r, curr.c });

	//BFSŽ��
	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = now.first + dr[i];
			int nc = now.second + dc[i];

			if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue; //���� ���� �̵��Ұ�
			if (visited[nr][nc] > 0) continue; //��湮 ������ ����
			if (MAP[nr][nc] < 0 || (MAP[nr][nc] > 1 && MAP[nr][nc] < timer)) continue; //������ ���̽�ķ���̰ų�, timer ������ ������ �������� �̵� �Ұ�
			//timer�п� ������ ���������δ� �̵� ����(������ ����)

			q.push({ nr, nc }); //Ž���� ���� push
			visited[nr][nc] = 1;
			dirHistory[nr][nc] = i; //�̵� ���� ����
		}
	}

	//BFS ����� ������ ����
	pair<int, int> history = stores[curr.num]; //�������������� Ž�� ����
	while (1) {
		int dir = dirHistory[history.first][history.second];
		int nr = history.first - dr[dir]; //����� ������ �ݴ�� �̵�
		int nc = history.second - dc[dir];

		if (nr == curr.r && nc == curr.c) { //����ġ�� ã�Ҵٸ�
			return dir; //ù �̵������� ��ȯ
		}

		history = { nr, nc }; //�̵��ϸ鼭 Ž��
	}

	return -1;
}

//1. ���� �� �ο� �̵�
void Move() {
	int sz = people.size(); //���� �̵��� �����ŭ Ž��
	for (int i = 0; i < sz; i++) {
		Person curr = people.front();
		people.pop();

		//BFS - �̹��� Ž���� curr ����� �̵��� ����
		int dir = BFS(curr);
		int nr = curr.r + dr[dir]; //�̵�
		int nc = curr.c + dc[dir];

		//��ǥ �������� �����ߴٸ�
		if (stores[curr.num].first == nr && stores[curr.num].second == nc) {
			arrived++; //���� �ο� ī����
			MAP[nr][nc] = timer; //MAP�� ǥ��(timer�п� ������ ������)
			continue; //�̵� ����
		}

		people.push({ curr.num, nr, nc }); //���� ���� ���� ����� ��� �̵�
	}
}

//timer�� ����� ���� ���̽�ķ�� ã��
pair<int, int> GoBasecamp() {
	pair<int, int> tStore = stores[timer]; //��ǥ �������� ��ġ
	int visited[16][16] = { 0, };
	queue<pair<int, int>> q;
	
	q.push({ tStore.first, tStore.second });
	visited[tStore.first][tStore.second] = 1;

	while (!q.empty()) {
		pair<int, int> curr = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = curr.first + dr[i];
			int nc = curr.second + dc[i];

			if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue; //���� ���� �̵��Ұ�
			if (visited[nr][nc] > 0) continue; //��湮 ������ ����
			if (MAP[nr][nc] < 0 || MAP[nr][nc] > 1) continue; //������ ���̽�ķ���� ���������δ� �̵��Ұ�

			if (MAP[nr][nc] == 1) return { nr, nc }; //���� ���� ã�� ���̽�ķ���� ��ȯ

			q.push({ nr, nc }); //Ž�� ���
			visited[nr][nc] = 1;
		}
	}

	return { 0, 0 };
}

int main() {
	//input
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> MAP[i][j];
		}
	}

	stores.push_back({ 0, 0 });
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		stores.push_back({ x, y }); //m�� ����� ��ǥ ������
	}

	timer = 0;
	while (arrived < m) { //���� ������ ������ ����
		timer++; //Ÿ�̸� �۵�

		//1. ���� �� ���� �̵�(�ִܰŸ�) & 2.������ ���� ó��
		Move();

		//3. timer�� ����� ���̽�ķ���� �̵�
		if (timer > m) continue; //��, ���� ����ߴٸ� ����

		pair<int, int> target = GoBasecamp(); //������ ���̽�ķ�� (��ǥ �������� ���� ����� ��)
		if (target.first != 0) {
			MAP[target.first][target.second] = -1; //���̽�ķ�� ����
			people.push({ timer, target.first, target.second }); //m�� ����� �̵� ����
		}
	}

	//output
	cout << timer << "\n";

	return 0;
}