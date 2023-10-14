//CodeTree �ο�
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Player {
	int r;
	int c;
	int d;
	int s;
	int gun;
};

int dr[4] = { -1, 0, 1, 0 }; //�������
int dc[4] = { 0, 1, 0, -1 };

int Point[401]; //Player���� ȹ�� ����
vector<int> GUNS[21][21];
int MAP[21][21]; //Player�� ��ȣ���� ����
vector<Player> players; //Player���� ����
int N, M; //N:������ ������, M:�÷��̾� �ο���

//�ִ� ���ݷ��� �� ȹ�� - ind�� �÷��̾ (r,c)��ġ����
void getGun(int ind, int r, int c) {
	int maxi = 0;
	int mInd = -1;

	//������ �ִ� �ѵ� �� �ִ� ���ݷ� ã��
	for (int i = 0; i < GUNS[r][c].size(); i++) {
		if (GUNS[r][c][i] > maxi) {
			maxi = GUNS[r][c][i];
			mInd = i;
		}
	}

	//�÷��̾ ������ ���� �ִ� �Ѱ� ���Ͽ� �ٲܰŶ�� ���� �Ѱ� ��ü
	if (maxi > players[ind].gun) {
		int tmp = players[ind].gun;
		players[ind].gun = maxi;
		GUNS[r][c][mInd] = tmp;
	}
}

//���� ó��
void GoWinner(int ind) {
	Player curr = players[ind];
	MAP[curr.r][curr.c] = ind; //�÷��̾��� ��ġ ����
	getGun(ind, curr.r, curr.c); //�ִ� ���ݷ��� �� ȹ��
}

//���� �̵� �� ó��
void GoLoser(int ind) {
	Player curr = players[ind];
	GUNS[curr.r][curr.c].push_back(curr.gun); //���� �ٴڿ� �����α�
	players[ind].gun = 0;

	//�̵� - ���� �� or Ÿ�÷��̾� ����� 90���� ȸ���ϸ� ã��
	for (int i = 0; i < 4; i++) {
		int nd = (curr.d + i) % 4;
		int nr = curr.r + dr[nd];
		int nc = curr.c + dc[nd];

		if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue;
		if (MAP[nr][nc] != 0) continue;

		//�̵��� ����� ��ġ�� ã�Ҵٸ�
		getGun(ind, nr, nc); //�ִ� ���ݷ��� ���� �� ȹ��
		players[ind].d = nd; //�̵�
		players[ind].r = nr; players[ind].c = nc;
		MAP[nr][nc] = ind; //�÷��̾��� ��ġ ���� ����
		break;
	}
}

//���� ����
void Play() {
	//M���� �÷��̾ ���������� �̵�
	for (int i = 1; i <= M; i++) {
		Player curr = players[i];
		int nr = curr.r + dr[curr.d];
		int nc = curr.c + dc[curr.d];

		if (nr <= 0 || nc <= 0 || nr > N || nc > N) { //�̵��� ĭ�� ���� ���̶�� �ݴ� �������� ��ȯ
			players[i].d = curr.d = (curr.d + 2) % 4;
			nr = curr.r + dr[curr.d];
			nc = curr.c + dc[curr.d];
		}
		MAP[curr.r][curr.c] = 0; //������ ��ġ�ϴ� ĭ�� �ʱ�ȭ
		players[i].r = nr; players[i].c = nc; //�̵��� ĭ���� ����

		if (MAP[nr][nc] == 0) { //�̵��� ĭ�� �÷��̾ ���ٸ�
			getGun(i, nr, nc); //�ִ� ���ݷ��� �� ȹ��
			MAP[nr][nc] = i; //i�� �÷��̾��� ��ġ ����
		} else { //�̵��� ĭ�� �÷��̾ �ִٸ�
			Player nPlayer = players[MAP[nr][nc]]; //�� ĭ���� curr�� nPlayer�� ������ �ο�

			//2�� �÷��̾��� ����(�ʱ� �ɷ�ġ + ���� ���ݷ�)
			int pA = curr.s + curr.gun;
			int pB = nPlayer.s + nPlayer.gun;

			int winner = 0, loser = 0; //���ڿ� ������ �ε��� ����
			if (pA > pB) {
				winner = i;
				loser = MAP[nr][nc];
			}
			else if (pA < pB) {
				winner = MAP[nr][nc];
				loser = i;
			}
			else {
				if (curr.s > nPlayer.s) {
					winner = i;
					loser = MAP[nr][nc];
				}
				else {
					winner = MAP[nr][nc];
					loser = i;
				}
			}

			Point[winner] += abs(pA - pB); //���ڰ� ����Ʈ ȹ��(���� ���� ���̸�ŭ)
			GoLoser(loser); //���ڰ� ���� �̵� �� ó��
			GoWinner(winner); //���� ó��
		}
	}
}

int main() {
	//input
	int K;
	cin >> N >> M >> K;

	int inp;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> inp;
			if (inp == 0) continue;
			GUNS[i][j].push_back(inp); //�ʱ� ���� ���� ���
		}
	}

	int ir, ic, id, is;
	players.push_back({ 0, 0, 0, 0, 0 }); //���̵�����
	for (int i = 1; i <= M; i++) {
		cin >> ir >> ic >> id >> is;
		players.push_back({ ir, ic, id, is, 0 }); //�÷��̾��� �ʱ� ����
		MAP[ir][ic] = i; //�÷��̾��� �ʱ� ��ġ ����
	}

	//K���嵿�� ���� �÷���
	for (int round = 1; round <= K; round++) {
		Play();
	}

	//output - M���� �÷��̾� ������ ȹ�� ����
	for (int i = 1; i <= M; i++) {
		cout << Point[i] << " ";
	}

	return 0;
}