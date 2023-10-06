//CodeTree 싸움땅
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

int dr[4] = { -1, 0, 1, 0 }; //상우하좌
int dc[4] = { 0, 1, 0, -1 };

int Point[401]; //Player들의 획득 점수
vector<int> GUNS[21][21];
int MAP[21][21]; //Player의 번호만을 저장
vector<Player> players; //Player들의 정보
int N, M; //N:격자의 사이즈, M:플레이어 인원수

//최대 공격력의 총 획득 - ind번 플레이어가 (r,c)위치에서
void getGun(int ind, int r, int c) {
	int maxi = 0;
	int mInd = -1;

	//기존에 있는 총들 중 최대 공격력 찾기
	for (int i = 0; i < GUNS[r][c].size(); i++) {
		if (GUNS[r][c][i] > maxi) {
			maxi = GUNS[r][c][i];
			mInd = i;
		}
	}

	//플레이어가 기존에 갖고 있는 총과 비교하여 바꿀거라면 땅의 총과 교체
	if (maxi > players[ind].gun) {
		int tmp = players[ind].gun;
		players[ind].gun = maxi;
		GUNS[r][c][mInd] = tmp;
	}
}

//승자 처리
void GoWinner(int ind) {
	Player curr = players[ind];
	MAP[curr.r][curr.c] = ind; //플레이어의 위치 저장
	getGun(ind, curr.r, curr.c); //최대 공격력의 총 획득
}

//패자 이동 및 처리
void GoLoser(int ind) {
	Player curr = players[ind];
	GUNS[curr.r][curr.c].push_back(curr.gun); //총은 바닥에 내려두기
	players[ind].gun = 0;

	//이동 - 격자 밖 or 타플레이어 존재시 90도씩 회전하며 찾기
	for (int i = 0; i < 4; i++) {
		int nd = (curr.d + i) % 4;
		int nr = curr.r + dr[nd];
		int nc = curr.c + dc[nd];

		if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue;
		if (MAP[nr][nc] != 0) continue;

		//이동할 방향과 위치를 찾았다면
		getGun(ind, nr, nc); //최대 공격력을 가진 총 획득
		players[ind].d = nd; //이동
		players[ind].r = nr; players[ind].c = nc;
		MAP[nr][nc] = ind; //플레이어의 위치 정보 저장
		break;
	}
}

//게임 진행
void Play() {
	//M명의 플레이어가 순차적으로 이동
	for (int i = 1; i <= M; i++) {
		Player curr = players[i];
		int nr = curr.r + dr[curr.d];
		int nc = curr.c + dc[curr.d];

		if (nr <= 0 || nc <= 0 || nr > N || nc > N) { //이동할 칸이 격자 밖이라면 반대 방향으로 전환
			players[i].d = curr.d = (curr.d + 2) % 4;
			nr = curr.r + dr[curr.d];
			nc = curr.c + dc[curr.d];
		}
		MAP[curr.r][curr.c] = 0; //기존에 위치하던 칸은 초기화
		players[i].r = nr; players[i].c = nc; //이동한 칸으로 저장

		if (MAP[nr][nc] == 0) { //이동할 칸에 플레이어가 없다면
			getGun(i, nr, nc); //최대 공격력의 총 획득
			MAP[nr][nc] = i; //i번 플레이어의 위치 저장
		} else { //이동할 칸에 플레이어가 있다면
			Player nPlayer = players[MAP[nr][nc]]; //이 칸에서 curr와 nPlayer가 만나서 싸움

			//2명 플레이어의 점수(초기 능력치 + 총의 공격력)
			int pA = curr.s + curr.gun;
			int pB = nPlayer.s + nPlayer.gun;

			int winner = 0, loser = 0; //승자와 패자의 인덱스 저장
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

			Point[winner] += abs(pA - pB); //승자가 포인트 획득(둘의 점수 차이만큼)
			GoLoser(loser); //패자가 먼저 이동 및 처리
			GoWinner(winner); //승자 처리
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
			GUNS[i][j].push_back(inp); //초기 총의 정보 기록
		}
	}

	int ir, ic, id, is;
	players.push_back({ 0, 0, 0, 0, 0 }); //더미데이터
	for (int i = 1; i <= M; i++) {
		cin >> ir >> ic >> id >> is;
		players.push_back({ ir, ic, id, is, 0 }); //플레이어의 초기 정보
		MAP[ir][ic] = i; //플레이어의 초기 위치 저장
	}

	//K라운드동안 게임 플레이
	for (int round = 1; round <= K; round++) {
		Play();
	}

	//output - M명의 플레이어 각각의 획득 점수
	for (int i = 1; i <= M; i++) {
		cout << Point[i] << " ";
	}

	return 0;
}