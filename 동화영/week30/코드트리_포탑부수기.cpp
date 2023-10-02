//�ڵ�Ʈ�� - ��ž�μ���
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct POS {
	int r;
	int c;
};

const int MAX_NM = 10;
int MAP[MAX_NM][MAX_NM]; //�� ��ž�� ���ݷ�
int HISTORY[MAX_NM][MAX_NM]; //�� ��ž�� �ֱ� ���� ����
int related[MAX_NM][MAX_NM]; //�� �Ͽ� �� ��ž�� ���ݰ� ������ �ִ°��� ���
int N, M; //���� ������ N*M

int dr[8] = { 0, 1, 0, -1, -1, 1, 1, -1 }; //�����»� + �밢��
int dc[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };

//���� ���� ��ž ����
//���ݷ� �ּ� -> �ֱ� ������ ��ž -> ��� ���� �� �ִ� -> �� �ִ�
POS findWeak() {
	POS ret = { -1, -1 }; //��ȯ�� ������ ��ġ
	int prev = 0; //��ȯ�� ĭ ��ž�� �ֱ� ���� ����
	int power = 10000; //��ȯ�� ĭ ��ž�� ���ݷ�

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 0) continue; //������ ��ž�� ����

			if (MAP[i][j] < power) { //1)���ݷ� ��
				ret = { i, j };
				prev = HISTORY[i][j];
				power = MAP[i][j];
			}
			else if (MAP[i][j] == power) {
				if (HISTORY[i][j] > prev) { //2)�ֱ� ���� ���� ��
					ret = { i, j };
					prev = HISTORY[i][j];
				}
				else if (HISTORY[i][j] == prev) {
					if ((i + j) > (ret.r + ret.c)) { //3)��� ���� �� ��
						ret = { i, j };
					}
					else if ((i + j) == (ret.r + ret.c)) {
						if (j > ret.c) { //4)�� ��
							ret = { i, j };
						}
					}
				}
			}
		}
	}

	return ret;
}

//���� ���� ��ž ����
//���ݷ� �ִ� -> �������� ������ ��ž -> ��� ���� �� �ּ� -> �� �ּ�
POS findStrong(POS attacker) {
	POS ret = { -1, -1 };
	int prev = 1001;
	int power = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 0) continue; //������ ��ž�� ����
			if (i == attacker.r && j == attacker.c) continue; //�����ڷ� ������ ��ž�� ����

			if (MAP[i][j] > power) { //1)���ݷ� ��
				ret = { i, j };
				prev = HISTORY[i][j];
				power = MAP[i][j];
			}
			else if (MAP[i][j] == power) {
				if (HISTORY[i][j] < prev) { //2)�ֱ� ���� ���� ��
					ret = { i, j };
					prev = HISTORY[i][j];
				}
				else if (HISTORY[i][j] == prev) {
					if ((i + j) < (ret.r + ret.c)) { //3)��� ���� �� ��
						ret = { i, j };
					}
					else if ((i + j) == (ret.r + ret.c)) {
						if (j < ret.c) { //4)�� ��
							ret = { i, j };
						}
					}
				}
			}
		}
	}

	return ret;
}

// 1.  ������ ����
POS SelectAttacker() {
	POS weaker = findWeak(); //���� ���� ��ž ����
	MAP[weaker.r][weaker.c] += (N + M); //���ݷ� (N+M)��ŭ ����
	related[weaker.r][weaker.c] = 1; //�ݹ� ���ݰ� �������� ǥ��

	return weaker;
}

//2-1)������ ����
//��) st�κ��� en���� BFS Ž������ �̵��� �����Ѱ��� Ž��(�Ÿ��� ������ ����)
//��) �̵� �Ұ��ϴٸ� ����
//��) �̵� �����ϴٸ� ������ �ǵ��ư��� ���������� ����
bool LaserAttack(POS st, POS en) {
	queue<POS> q;
	int visited[10][10] = { 0, };
	int dir[10][10] = { 0, };
	q.push(st);
	visited[st.r][st.c] = 1;

	while (!q.empty()) {
		POS curr = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = curr.r + dr[i];
			int nc = curr.c + dc[i];

			//���� �׵θ����� ��ȯ ó��
			nr = (nr + N) % N;
			nc = (nc + M) % M;

			if (MAP[nr][nc] == 0) continue; //������ ��ž���δ� �̵� �Ұ�
			if (visited[nr][nc] > 0) continue; //��湮 ������ �̵� �Ұ�

			q.push({ nr,nc });
			visited[nr][nc] = visited[curr.r][curr.c] + 1; //�̵��Ÿ��� ����
			dir[nr][nc] = i;
		}
	}

	int cnt = visited[en.r][en.c];
	if (visited[en.r][en.c] == 0) return false; //en���� ���� �Ұ��ϴٸ� �Լ� ����

	//������ ã�� ��θ� ������ �ǵ��ư��� ������ ���� ����
	//�̵� ��ο� ��ġ�ϴ� ��ž���� (�������� ���ݷ�)/2 ��ŭ�� ����
	int aPower = MAP[st.r][st.c] / 2;
	POS now = en;
	for (int i = 2; i < cnt; i++) { //��ο� �ִ� ��ž���� ������� Ž��
		int nDir = (dir[now.r][now.c] + 2) % 4; //�ǵ��ư� ����
		int nxtR = now.r + dr[nDir];
		int nxtC = now.c + dc[nDir];

		//���� �׵θ����� ��ȯ ó��
		nxtR = (nxtR + N) % N;
		nxtC = (nxtC + M) % M;

		MAP[nxtR][nxtC] -= aPower; //������ ���� ���ظ�ŭ ����
		if (MAP[nxtR][nxtC] < 0) MAP[nxtR][nxtC] = 0; //��ž�� �������ٸ� 0���� ǥ��
		related[nxtR][nxtC] = 1; //�ݹ� ���ݰ� �������� ǥ��
		now = { nxtR, nxtC }; //now ���� ����
	}

	//���� Ÿ�ٿ� ���� ����
	//(�������� ���ݷ�)��ŭ ����
	MAP[en.r][en.c] -= MAP[st.r][st.c];
	if (MAP[en.r][en.c] < 0) MAP[en.r][en.c] = 0;
	related[en.r][en.c] = 1;

	return true;
}

//2-2)��ź����
void BombAttacker(POS st, POS en) {
	//���� Ÿ�ٿ� ���� ����
	//(�������� ���ݷ�)��ŭ ����
	MAP[en.r][en.c] -= MAP[st.r][st.c];
	if (MAP[en.r][en.c] < 0) MAP[en.r][en.c] = 0;
	related[en.r][en.c] = 1;

	//���� Ÿ���� ���� 8ĭ�� ���� ����
	//(�������� ���ݷ�)/2��ŭ ����
	int aPower = MAP[st.r][st.c] / 2;
	for (int i = 0; i < 8; i++) {
		int nr = en.r + dr[i];
		int nc = en.c + dc[i];

		//���� �׵θ����� ��ȯ ó��
		nr = (nr + N) % N;
		nc = (nc + M) % M;

		if (nr == st.r && nc == st.c) continue; //�����ڰ� ���� ����̶�� ����
		if (MAP[nr][nc] == 0) continue; //�̹� ������ ��ž�̶�� ����

		//�ֺ��� ���� ����
		MAP[nr][nc] -= aPower;
		if (MAP[nr][nc] < 0) MAP[nr][nc] = 0;
		related[nr][nc] = 1;
	}
}

//2.�������� ���� + 3.��ž �μ���
void Attack(POS attacker) {
	POS stronger = findStrong(attacker); //���� ���� ��ž�� �����Ͽ� Ÿ������ ����

	if (!LaserAttack(attacker, stronger)) { //������ ������ �������� Ž�� �� �����ϴٸ� ����������
		BombAttacker(attacker, stronger); //������ ������ �Ұ��ϴٸ� ��ź ����
	}
}

//4.��ž ����
int Heal() {
	int remain = N * M; //�����ִ� ��ž�� �� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 0) remain--; //������ ��ž�� ����
			else if (MAP[i][j] > 0 && related[i][j] == 0) { //��������鼭 �ݹ� ���ݰ� ������ ��ž�� ���ݷ� 1 ����
				MAP[i][j]++;
			}
		}
	}

	return remain;
}

int main() {
	//input
	int K;
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	//solve
	for (int i = 1; i <= K; i++) {
		memset(related, 0, sizeof(related));

		POS attacker = SelectAttacker(); //1.������ ����
		Attack(attacker); //2.�������� ���� + 3.��ž �μ���
		HISTORY[attacker.r][attacker.c] = i; //�������� �ֱ� ���� �̷� ����
		int remain = Heal(); //4.��ž ����

		if (remain <= 1) break; //��ž�� 1�� ���Ҵٸ� ��� ���� ����
	}

	//output
	POS ans = findStrong({ -1, -1 }); //���������� ���� ���� ��ž ����
	cout << MAP[ans.r][ans.c] << "\n";

	return 0;
}

/*
4 4 10
0 1 4 4
8 0 10 13
8 0 11 26
0 0 0 0

*/

/* 4168
10 10 20
995 3976 1850 0 0 0 0 0 2823 0
0 2197 4554 0 3991 0 0 0 0 0
2243 918 206 2051 0 0 0 0 0 2354
0 0 2211 394 3896 2763 0 0 3580 3094
0 0 4364 0 0 0 0 0 0 4990
0 0 0 0 0 0 736 0 1159 0
1374 0 2610 3165 3653 0 2651 0 0 0
4493 0 1423 0 2416 0 0 0 3580 0
0 4112 3779 0 3654 1247 0 0 132 712
92 2643 1459 4675 4838 0 2539 850 2040 2153
*/

/*727
10 6 1000
3362 3908 4653 3746 4119 3669
4174 0 0 868 1062 854
633 51 759 0 4724 1474
2735 365 1750 3382 498 1672
141 3700 0 436 2752 974
3494 0 4719 2016 3870 0
3357 0 4652 3468 0 3758
4610 3125 0 2364 3303 1904
0 0 0 0 3959 3324
3187 0 105 2821 3642 160
*/