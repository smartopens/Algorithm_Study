// �ڵ�Ʈ�� - �������
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

struct POS {
	int r;
	int c;
};

int dr[4] = { -1, 1, 0, 0 }; //�����¿�
int dc[4] = { 0, 0, -1, 1 };

queue<POS> players; //�����ڵ��� ��ġ
POS cExit; //�ⱸ�� ����ġ
int position[11][11]; //�� ���� �����ڵ��� ��ġ & ȸ�� ����� �̷��� ���� ǥ��
int MAP[11][11]; //����
int N, M; //N: ������ ������, M: �ʱ� �������� ��
int dist; //��� �����ڵ��� �̵� �Ÿ�

// 1. ������ ���� �̵�
void Move() {
	memset(position, 0, sizeof(position));

	int sz = players.size(); //���� ���� ������ ����ŭ Ž��

	for (int i = 0; i < sz; i++) {
		POS now = players.front();
		players.pop();

		int nowDist = abs(now.r - cExit.r) + abs(now.c - cExit.c); //���� ��ġ ~ Ż�ⱸ�� �Ÿ�
		int nxtDir = -1; //�̹� �Ͽ� �̵��� ����

		POS nxt;
		for (int j = 0; j < 4; j++) {
			nxt = { now.r + dr[j], now.c + dc[j] };
			int nxtDist = abs(nxt.r - cExit.r) + abs(nxt.c - cExit.c); //j�������� �̵��� Ż�ⱸ������ �Ÿ�

			if (nxt.r <= 0 || nxt.c <= 0 || nxt.r > N || nxt.c > N) continue; //���� ���� ����
			if (MAP[nxt.r][nxt.c] > 0) continue; //�������� 1 �̻��̶�� �̵� �Ұ�
			if (nxtDist >= nowDist) continue; //���纸�� Ż�ⱸ���� �Ÿ��� �־����� �������� �̵� �Ұ�

			nxtDir = j; //�̹� �Ͽ� �̵��� ������ ã�Ҵٸ� ���� ���� �� Ž�� ����
			break;
		}

		if (nxtDir == -1) { //�̵� ������ ������ ���ٸ�
			position[now.r][now.c]++; //�̵����� �ʰ� ���� ��ġ�� �ӹ�����
			players.push(now);
		}
		else { //�̵� ������ ������ �ִٸ�
			dist++; //�������� �̵��Ÿ� ����

			if (nxt.r == cExit.r && nxt.c == cExit.c) continue; //�̵��� ��ġ�� Ż�ⱸ��� Ż��! => ���̻� ��ġ Ž�� X

			position[nxt.r][nxt.c]++; //�̵��� ��ġ�� ����
			players.push({ nxt.r, nxt.c });
		}
	}
}

// 2-2. (r, c)�� �������� sz ũ���� ���簢���� �ð� ���� 90���� ȸ��
void rotExecute(int r, int c, int sz) {
	memset(position, 0, sizeof(position));
	int TMP[11][11] = { 0, };

	//MAP�� ȸ���� ����� TMP�� ����
	//position���� �̹� �Ͽ� ȸ�� ����� ĭ�� ���� -> ������ ȸ���� ����
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			TMP[r + i][c + j] = MAP[sz - j - 1 + r][c + i];
			position[i + r][j + c] = 1;
		}
	}

	//ȸ���� ĭ�� ������ -1
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			if (TMP[i + r][j + c] > 0) TMP[i + r][j + c]--;
			MAP[i + r][j + c] = TMP[i + r][j + c];
		}
	}

	//Ż�ⱸ�� ��ġ ȸ�� ����
	int tmpR = cExit.r, tmpC = cExit.c;
	cExit = { tmpC - c + r, sz - tmpR + r + c - 1};

	//ȸ�� ����� ����ĭ�� ��ġ�� �����ڵ� ȸ����Ű��
	int cnt = players.size();
	for (int i = 0; i < cnt; i++) {
		POS curr = players.front();
		players.pop();

		if (position[curr.r][curr.c] == 1) { //ȸ�� ���
			curr = { curr.c - c + r, sz - curr.r + r + c - 1 };
		}
		players.push(curr);
	}
}

// 2-1. (rStart, cStart) �������κ��� sz ũ���� ���簢���� Ž���ϸ� �����ڰ� ���ԵǾ����� Ž��
bool findPlayer(int rStart, int cStart, int sz) {
	for (int i = 0; i < sz; i++) {
		int nr = rStart + i;
		if (nr <= 0 || nr > N) return false; //���� ������ �Ѿ�� ���簢�� ����� �Ұ��� �Ǵ�

		for (int j = 0; j < sz; j++) {
			int nc = cStart + j;
			if (nc <= 0 || nc > N) return false; //���� ������ �Ѿ�� ���簢�� ����� �Ұ��� �Ǵ�

			if (position[nr][nc] > 0) { //������ �߰��Ͽ��ٸ�
				rotExecute(rStart, cStart, sz); //�ش� �κ��� ȸ���ϱ�
				return true; //ȸ�� �Ϸ� �� Ž�� ����
			}
		}
	}

	return false; //�ش� ���簢������ �����ڸ� 1�� �߰����� ���ߴٸ� false ��ȯ
}

// 2. �̷� ȸ��
void Rotate() {
	//���簢���� �ּ� 2x2�� �������̴�
	for (int i = 2; i <= N; i++) {
		//Ż�ⱸ�� �������� �������->�������->�����ϴ�->�����ϴ� ������ ���ư��� Ž���� �Ѵ�
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < i; k++) {
				//�̹��� ã�� ���簢���� �����ڰ� 1���̶� ���Ե��� Ž��
				if (findPlayer(cExit.r - i + 1 + j, cExit.c - i + 1 + k, i)) {
					return; //���簢���� ã�Ƽ� ȸ���Ͽ��ٸ� �̹� �� ��!
				}
			}
		}
	}
}

int main() {
	int K;

	// input
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}

	int ir, ic;
	for (int i = 0; i < M; i++) {
		cin >> ir >> ic;
		players.push({ ir, ic }); //�������� ��ġ ����
	}

	cin >> cExit.r >> cExit.c; //Ż�ⱸ�� ���� ��ġ

	//K�ʵ��� ����
	for (int i = 0; i < K; i++) {
		Move(); //1. ������ ���� �̵�

		if (players.empty()) break; //������ ������ Ż�� �Ϸ�� ���� ����

		Rotate(); //2. �̷� ȸ��
	}

	//output
	cout << dist << "\n" << cExit.r << " " << cExit.c << "\n";

	return 0;
}