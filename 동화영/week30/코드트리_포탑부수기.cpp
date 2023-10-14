//코드트리 - 포탑부수기
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct POS {
	int r;
	int c;
};

const int MAX_NM = 10;
int MAP[MAX_NM][MAX_NM]; //각 포탑의 공격력
int HISTORY[MAX_NM][MAX_NM]; //각 포탑의 최근 공격 시점
int related[MAX_NM][MAX_NM]; //매 턴에 각 포탑이 공격과 연관이 있는가를 기록
int N, M; //격자 사이즈 N*M

int dr[8] = { 0, 1, 0, -1, -1, 1, 1, -1 }; //우하좌상 + 대각선
int dc[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };

//가장 약한 포탑 선정
//공격력 최소 -> 최근 공격한 포탑 -> 행과 열의 합 최대 -> 열 최대
POS findWeak() {
	POS ret = { -1, -1 }; //반환할 격자의 위치
	int prev = 0; //반환할 칸 포탑의 최근 공격 시점
	int power = 10000; //반환할 칸 포탑의 공격력

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 0) continue; //무너진 포탑은 무시

			if (MAP[i][j] < power) { //1)공격력 비교
				ret = { i, j };
				prev = HISTORY[i][j];
				power = MAP[i][j];
			}
			else if (MAP[i][j] == power) {
				if (HISTORY[i][j] > prev) { //2)최근 공격 시점 비교
					ret = { i, j };
					prev = HISTORY[i][j];
				}
				else if (HISTORY[i][j] == prev) {
					if ((i + j) > (ret.r + ret.c)) { //3)행과 열의 합 비교
						ret = { i, j };
					}
					else if ((i + j) == (ret.r + ret.c)) {
						if (j > ret.c) { //4)열 비교
							ret = { i, j };
						}
					}
				}
			}
		}
	}

	return ret;
}

//가장 강한 포탑 선정
//공격력 최대 -> 공격한지 오래된 포탑 -> 행과 열의 합 최소 -> 열 최소
POS findStrong(POS attacker) {
	POS ret = { -1, -1 };
	int prev = 1001;
	int power = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 0) continue; //무너진 포탑은 무시
			if (i == attacker.r && j == attacker.c) continue; //공격자로 선정된 포탑은 제외

			if (MAP[i][j] > power) { //1)공격력 비교
				ret = { i, j };
				prev = HISTORY[i][j];
				power = MAP[i][j];
			}
			else if (MAP[i][j] == power) {
				if (HISTORY[i][j] < prev) { //2)최근 공격 시점 비교
					ret = { i, j };
					prev = HISTORY[i][j];
				}
				else if (HISTORY[i][j] == prev) {
					if ((i + j) < (ret.r + ret.c)) { //3)행과 열의 합 비교
						ret = { i, j };
					}
					else if ((i + j) == (ret.r + ret.c)) {
						if (j < ret.c) { //4)열 비교
							ret = { i, j };
						}
					}
				}
			}
		}
	}

	return ret;
}

// 1.  공격자 선정
POS SelectAttacker() {
	POS weaker = findWeak(); //가장 약한 포탑 선정
	MAP[weaker.r][weaker.c] += (N + M); //공격력 (N+M)만큼 증가
	related[weaker.r][weaker.c] = 1; //금번 공격과 연관됨을 표기

	return weaker;
}

//2-1)레이저 공격
//ㄱ) st로부터 en까지 BFS 탐색으로 이동이 가능한가를 탐색(거리와 방향을 저장)
//ㄴ) 이동 불가하다면 종료
//ㄷ) 이동 가능하다면 역으로 되돌아가며 레이저공격 시전
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

			//격자 테두리끼리 순환 처리
			nr = (nr + N) % N;
			nc = (nc + M) % M;

			if (MAP[nr][nc] == 0) continue; //무너진 포탑으로는 이동 불가
			if (visited[nr][nc] > 0) continue; //기방문 지점은 이동 불가

			q.push({ nr,nc });
			visited[nr][nc] = visited[curr.r][curr.c] + 1; //이동거리를 저장
			dir[nr][nc] = i;
		}
	}

	int cnt = visited[en.r][en.c];
	if (visited[en.r][en.c] == 0) return false; //en까지 도달 불가하다면 함수 종료

	//위에서 찾은 경로를 역으로 되돌아가며 레이저 공격 시전
	//이동 경로에 위치하는 포탑들은 (공격자의 공격력)/2 만큼씩 피해
	int aPower = MAP[st.r][st.c] / 2;
	POS now = en;
	for (int i = 2; i < cnt; i++) { //경로에 있는 포탑들을 대상으로 탐색
		int nDir = (dir[now.r][now.c] + 2) % 4; //되돌아갈 방향
		int nxtR = now.r + dr[nDir];
		int nxtC = now.c + dc[nDir];

		//격자 테두리끼리 순환 처리
		nxtR = (nxtR + N) % N;
		nxtC = (nxtC + M) % M;

		MAP[nxtR][nxtC] -= aPower; //공격을 입은 피해만큼 감소
		if (MAP[nxtR][nxtC] < 0) MAP[nxtR][nxtC] = 0; //포탑이 무너졌다면 0으로 표기
		related[nxtR][nxtC] = 1; //금번 공격과 연관됨을 표시
		now = { nxtR, nxtC }; //now 지점 갱신
	}

	//공격 타겟에 공격 시전
	//(공격자의 공격력)만큼 피해
	MAP[en.r][en.c] -= MAP[st.r][st.c];
	if (MAP[en.r][en.c] < 0) MAP[en.r][en.c] = 0;
	related[en.r][en.c] = 1;

	return true;
}

//2-2)포탄공격
void BombAttacker(POS st, POS en) {
	//공격 타겟에 공격 시전
	//(공격자의 공격력)만큼 피해
	MAP[en.r][en.c] -= MAP[st.r][st.c];
	if (MAP[en.r][en.c] < 0) MAP[en.r][en.c] = 0;
	related[en.r][en.c] = 1;

	//공격 타겟의 주위 8칸에 공격 시전
	//(공격자의 공격력)/2만큼 피해
	int aPower = MAP[st.r][st.c] / 2;
	for (int i = 0; i < 8; i++) {
		int nr = en.r + dr[i];
		int nc = en.c + dc[i];

		//격자 테두리끼리 순환 처리
		nr = (nr + N) % N;
		nc = (nc + M) % M;

		if (nr == st.r && nc == st.c) continue; //공격자가 피해 대상이라면 무시
		if (MAP[nr][nc] == 0) continue; //이미 무너진 포탑이라면 제외

		//주변에 공격 시전
		MAP[nr][nc] -= aPower;
		if (MAP[nr][nc] < 0) MAP[nr][nc] = 0;
		related[nr][nc] = 1;
	}
}

//2.공격자의 공격 + 3.포탑 부서짐
void Attack(POS attacker) {
	POS stronger = findStrong(attacker); //가장 강한 포탑을 선정하여 타겟으로 지정

	if (!LaserAttack(attacker, stronger)) { //레이저 공격이 가능한지 탐색 및 가능하다면 레이저공격
		BombAttacker(attacker, stronger); //레이저 공격이 불가하다면 포탄 공격
	}
}

//4.포탑 정비
int Heal() {
	int remain = N * M; //남아있는 포탑의 수 세기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 0) remain--; //무너진 포탑은 제외
			else if (MAP[i][j] > 0 && related[i][j] == 0) { //살아있으면서 금번 공격과 무관한 포탑은 공격력 1 증가
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

		POS attacker = SelectAttacker(); //1.공격자 선정
		Attack(attacker); //2.공격자의 공격 + 3.포탑 부서짐
		HISTORY[attacker.r][attacker.c] = i; //공격자의 최근 공격 이력 갱신
		int remain = Heal(); //4.포탑 정비

		if (remain <= 1) break; //포탑이 1개 남았다면 즉시 게임 종료
	}

	//output
	POS ans = findStrong({ -1, -1 }); //최종적으로 가장 강한 포탑 선정
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