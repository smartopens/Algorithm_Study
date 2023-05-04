/* 뱀 */
#include <iostream>
#include <queue>
using namespace std;
#define MAX_N 101
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // 상좌하우
int cdir[DIR_NUM] = { 0, -1, 0, 1 };

queue<pair<int, char>> corner; // 뱀의 방향 전환 정보
int APPLE[MAX_N][MAX_N]; // 사과 위치 정보
int MAP[MAX_N][MAX_N]; // 뱀의 위치 정보 저장용
int N; // 격자 사이즈

pair<int, int> head, tail; // 뱀의 머리와 꼬리
int dir; // 뱀의 방향

// 뱀 이동
int move() {
	// 현재 방향으로 진행 시 뱀 머리의 다음 위치
	int nr = head.first + rdir[dir];
	int nc = head.second + cdir[dir];

	// 벽 혹은 뱀의 몸에 부딪히면 게임 종료
	if ((nr < 1 || nc < 1 || nr > N || nc > N) || MAP[nr][nc] > 0) {
		return 0;
	}

	// 뱀의 머리 이동
	MAP[nr][nc] = MAP[head.first][head.second] + 1; // 진행할수록 숫자 증가 -> 뱀 꼬리의 이동경로 파악을 위해
	head = { nr, nc };

	// 이동한 방향에 사과가 있다면
	if (APPLE[nr][nc] == 1) {
		APPLE[nr][nc] = 0; // 사과 먹고 꼬리는 이동 X
	}
	// 사과가 없다면
	else {
		// 꼬리 기준 4방향 탐색하여 꼬리 바로 앞칸을 발견 시 꼬리 앞으로 이동
		for (int i = 0; i < DIR_NUM; i++) {
			int nxtR = tail.first + rdir[i];
			int nxtC = tail.second + cdir[i];

			if (MAP[nxtR][nxtC] == MAP[tail.first][tail.second] + 1) {
				MAP[tail.first][tail.second] = 0;
				tail = { nxtR, nxtC };
				break;
			}
		}
	}

	return 1; // 정상 이동 시 1 반환
}

int main() {
	// input
	int K, L, X, a, b;
	char C;
	int timer = 0; // 소요 시간

	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		cin >> a >> b;
		APPLE[a][b] = 1; // 사과 정보
	}

	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> X >> C;
		corner.push({ X,C }); // 뱀의 방향 전환 정보
	}

	// init - 초기 정보
	dir = 3;
	MAP[1][1] = 1;
	head = { 1, 1 };
	tail = { 1, 1 };

	// solve
	while (1) {
		++timer; // 시간 추가

		// 1. 뱀 이동
		// 0 반환시 게임 종료
		if(move() == 0) break;

		// 2. 뱀의 진행방향 바꿀 타이밍이라면 바꿔주기
		if (!corner.empty() && corner.front().first == timer) {
			pair<int, char> turn = corner.front();
			corner.pop();

			if (turn.second == 'L') dir = (dir + 1) % DIR_NUM; // 왼쪽으로 90도 회전 
			else if (turn.second == 'D') dir = (dir - 1 + DIR_NUM) % DIR_NUM; // 오른쪽으로 90도 회전
		}
	}

	// output
	cout << timer;

	return 0;
}