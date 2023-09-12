// 코드트리 - 메이즈러너
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

struct POS {
	int r;
	int c;
};

int dr[4] = { -1, 1, 0, 0 }; //상하좌우
int dc[4] = { 0, 0, -1, 1 };

queue<POS> players; //참가자들의 위치
POS cExit; //출구의 현위치
int position[11][11]; //매 턴의 참가자들의 위치 & 회전 대상인 미로의 격자 표기
int MAP[11][11]; //격자
int N, M; //N: 격자의 사이즈, M: 초기 참가자의 수
int dist; //모든 참가자들의 이동 거리

// 1. 참가자 동시 이동
void Move() {
	memset(position, 0, sizeof(position));

	int sz = players.size(); //현재 남은 참가자 수만큼 탐색

	for (int i = 0; i < sz; i++) {
		POS now = players.front();
		players.pop();

		int nowDist = abs(now.r - cExit.r) + abs(now.c - cExit.c); //현재 위치 ~ 탈출구의 거리
		int nxtDir = -1; //이번 턴에 이동할 방향

		POS nxt;
		for (int j = 0; j < 4; j++) {
			nxt = { now.r + dr[j], now.c + dc[j] };
			int nxtDist = abs(nxt.r - cExit.r) + abs(nxt.c - cExit.c); //j방향으로 이동시 탈출구까지의 거리

			if (nxt.r <= 0 || nxt.c <= 0 || nxt.r > N || nxt.c > N) continue; //격자 밖은 무시
			if (MAP[nxt.r][nxt.c] > 0) continue; //내구도가 1 이상이라면 이동 불가
			if (nxtDist >= nowDist) continue; //현재보다 탈출구와의 거리가 멀어지는 방향으로 이동 불가

			nxtDir = j; //이번 턴에 이동할 방향을 찾았다면 방향 저장 및 탐색 중지
			break;
		}

		if (nxtDir == -1) { //이동 가능한 방향이 없다면
			position[now.r][now.c]++; //이동하지 않고 현재 위치에 머무르기
			players.push(now);
		}
		else { //이동 가능한 방향이 있다면
			dist++; //참가자의 이동거리 증가

			if (nxt.r == cExit.r && nxt.c == cExit.c) continue; //이동한 위치가 탈출구라면 탈출! => 더이상 위치 탐색 X

			position[nxt.r][nxt.c]++; //이동한 위치로 저장
			players.push({ nxt.r, nxt.c });
		}
	}
}

// 2-2. (r, c)를 기점으로 sz 크기의 정사각형을 시계 방향 90도로 회전
void rotExecute(int r, int c, int sz) {
	memset(position, 0, sizeof(position));
	int TMP[11][11] = { 0, };

	//MAP을 회전한 결과를 TMP에 저장
	//position에는 이번 턴에 회전 대상인 칸을 저장 -> 참가자 회전을 위함
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			TMP[r + i][c + j] = MAP[sz - j - 1 + r][c + i];
			position[i + r][j + c] = 1;
		}
	}

	//회전한 칸의 내구도 -1
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			if (TMP[i + r][j + c] > 0) TMP[i + r][j + c]--;
			MAP[i + r][j + c] = TMP[i + r][j + c];
		}
	}

	//탈출구의 위치 회전 적용
	int tmpR = cExit.r, tmpC = cExit.c;
	cExit = { tmpC - c + r, sz - tmpR + r + c - 1};

	//회전 대상인 격자칸에 위치한 참가자도 회전시키기
	int cnt = players.size();
	for (int i = 0; i < cnt; i++) {
		POS curr = players.front();
		players.pop();

		if (position[curr.r][curr.c] == 1) { //회전 대상
			curr = { curr.c - c + r, sz - curr.r + r + c - 1 };
		}
		players.push(curr);
	}
}

// 2-1. (rStart, cStart) 지점으로부터 sz 크기의 정사각형을 탐색하며 참가자가 포함되었는지 탐색
bool findPlayer(int rStart, int cStart, int sz) {
	for (int i = 0; i < sz; i++) {
		int nr = rStart + i;
		if (nr <= 0 || nr > N) return false; //격자 밖으로 넘어가면 정사각형 만들기 불가로 판단

		for (int j = 0; j < sz; j++) {
			int nc = cStart + j;
			if (nc <= 0 || nc > N) return false; //격자 밖으로 넘어가면 정사각형 만들기 불가로 판단

			if (position[nr][nc] > 0) { //참가자 발견하였다면
				rotExecute(rStart, cStart, sz); //해당 부분을 회전하기
				return true; //회전 완료 후 탐색 종료
			}
		}
	}

	return false; //해당 정사각형에서 참가자를 1명도 발견하지 못했다면 false 반환
}

// 2. 미로 회전
void Rotate() {
	//정사각형은 최소 2x2의 사이즈이다
	for (int i = 2; i <= N; i++) {
		//탈출구를 기준으로 좌측상단->우측상단->좌측하단->우측하단 순으로 돌아가며 탐색을 한다
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < i; k++) {
				//이번에 찾은 정사각형에 참가자가 1명이라도 포함된지 탐색
				if (findPlayer(cExit.r - i + 1 + j, cExit.c - i + 1 + k, i)) {
					return; //정사각형을 찾아서 회전하였다면 이번 턴 끝!
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
		players.push({ ir, ic }); //참가자의 위치 저장
	}

	cin >> cExit.r >> cExit.c; //탈출구의 현재 위치

	//K초동안 진행
	for (int i = 0; i < K; i++) {
		Move(); //1. 참가자 동시 이동

		if (players.empty()) break; //참가자 전원이 탈출 완료시 게임 종료

		Rotate(); //2. 미로 회전
	}

	//output
	cout << dist << "\n" << cExit.r << " " << cExit.c << "\n";

	return 0;
}