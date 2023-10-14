//CodeTree �����ڸ�
#include <iostream>
using namespace std;

int dr[8] = { -1, 0, 1, 0, -1, -1, 1, 1 }; //�����Ͽ� + �밢��4����
int dc[8] = { 0, -1, 0, 1, 1, -1, -1, 1 };

int REMOVER[20][20]; //������ ��Ȳ (�� �б��� �����Ǵ°��� ����)
int MAP[20][20]; //������ ���� (-1:��, 0:��ĭ, 1~:����)
int N, K, C; //N:������ ������, K:�������� ���ı���, C:�������� �����ð�

int timer; //�ùķ��̼� �ҿ�ð�
int removed; //�ڸ��� �� ���� �׷��� ��

//1.������ ����
void Grow() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] <= 0) continue; //���� ������ �ִ� ĭ�� ���Ͽ�

			int cnt = 0;

			for (int k = 0; k < 4; k++) { //4���� �� ������ �ִ� ĭ�� ����ŭ ������ �����Ѵ�
				int nr = i + dr[k];
				int nc = j + dc[k];

				if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
				if (MAP[nr][nc] <= 0) continue;

				cnt++; //����ĭ �� ���� �ִ� ĭ�� ����
			}

			MAP[i][j] += cnt; //��������
		}
	}
}

//2.������ ����
void Spread() {
	int spreaded[20][20] = { 0, }; //�̹� �⿡ ���ĵǴ� ������ �׷� ���� ����

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] <= 0) continue; //������ �ִ� ĭ�� ���Ͽ�

			bool isSpread[4] = { 0, }; //�����Ͽ� 4���⿡ ������ �Ǵ°��� ���
			int cnt = 0; //���ĵǴ� ĭ�� ��
			for (int k = 0; k < 4; k++) {
				int nr = i + dr[k];
				int nc = j + dc[k];

				if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; //���� ���� ����
				if (MAP[nr][nc] != 0) continue; //��ĭ�� �ƴ϶�� ���� X (��, ���̰ų� �ٸ� ������ �ְų�)
				if (REMOVER[nr][nc] >= timer) continue; //���� �����ǰ� �ִ� �������� �ִٸ� ���� X

				isSpread[k] = true; //k�������� ���� ����
				cnt++;
			}

			for (int k = 0; k < 4; k++) { //4���� �� ���ĵǴ� ĭ�� ������ ���� ���
				if (isSpread[k]) {
					int nr = i + dr[k];
					int nc = j + dc[k];
					spreaded[nr][nc] += MAP[i][j] / cnt; //���ĵǴ� ĭ���� ������ŭ
				}
			}
		}
	}

	//���ĵǴ� ���� ���ϱ�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MAP[i][j] += spreaded[i][j];
		}
	}
}

//3-1.������ ������ ��ġ ���ϱ� ���� �ùķ��̼�
int Simul(int r, int c) {
	if (MAP[r][c] <= 0) return 0; //���̰ų� ������ ���� ĭ�� 0���� ��ȯ (���̻� Ȯ�� X)

	int cnt = MAP[r][c]; //(r,c)���� ���� �ڸ�
	for (int i = 4; i < 8; i++) { //�밢�� 4��������
		for (int j = 1; j <= K; j++) { //K���̸�ŭ Ȯ��
			int nr = r + dr[i] * j;
			int nc = c + dc[i] * j;

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
			if (MAP[nr][nc] <= 0) break; //��ĭ�̰ų� ���̸� ���̻� Ȯ�� X

			cnt += MAP[nr][nc]; //(r,c) �������� �ڸ�Ǵ� ������ �� ����
		}
	}

	return cnt; //�ڸ�Ǵ� ������ ���� ��ȯ
}

//3.������ �Ѹ���
void Remove() {
	//���� ���� ������ �ڸ��ϴ� ������ ������ ��ġ ã��
	int maxTree = 0, maxR = -1, maxC = -1; //������ ��ġ �� �� ���� ���� �ڸ� ��
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int trees = Simul(i, j); //(i,j)�� �������� �ѷ��� �� �ڸ��ϴ� ������ ��
			if (trees > maxTree) { //�ִ밪 ����
				maxTree = trees;
				maxR = i;
				maxC = j;
			}
		}
	}

	MAP[maxR][maxC] = 0; //(maxR, maxC)ĭ�� ������ �Ѹ���
	REMOVER[maxR][maxC] = timer + C; //����(timer)�κ��� C�Ⱓ ������ ����
	for (int i = 4; i < 8; i++) {
		for (int j = 1; j <= K; j++) {
			int nr = maxR + dr[i] * j;
			int nc = maxC + dc[i] * j;

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;

			REMOVER[nr][nc] = timer + C; //������ Ȯ��

			if (MAP[nr][nc] > 0) MAP[nr][nc] = 0; //������ �ִ� ĭ�̶�� ���� �ڸ�
			else if (MAP[nr][nc] <= 0) break; //��ĭ�̰ų� ���̶�� ���̻� Ȯ�� X
		}
	}

	removed += maxTree; //�ڸ��� �� ������ �� ����
}

int main() {
	//input
	int M;
	cin >> N >> M >> K >> C;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	//M�⵿�� �ùķ��̼� ����
	for (int i = 1; i <= M; i++) {
		timer++; //�������� �����ð� �񱳸� ���� Ÿ�̸� �۵�
		Grow(); //1.��������
		Spread(); //2.��������
		Remove(); //3.������ �Ѹ���
	}

	//output - �ڸ��� �� ������ �׷� ��
	cout << removed << "\n";

	return 0;
}