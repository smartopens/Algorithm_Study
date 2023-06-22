/* 청소년 상어 */
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define SIZE_N 4
#define SIZE_F 17
#define DIR_NUM 8

struct FISH {
	int y; // 좌표
	int x;
	int dir; // 방향
	int alive; // 살아있는가
};

int ydir[DIR_NUM] = { -1, -1, 0, 1, 1, 1, 0, -1 }; // 상, 좌상, 좌, ..., 우상
int xdir[DIR_NUM] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int MAP[SIZE_N][SIZE_N]; // -1: 상어, 0: 빈칸, 1~16: 물고기
FISH INFO[SIZE_F]; // 상어와 물고기들의 정보 (0: 상어, 1~16: 물고기)

int ans; // 최대값 (답)
int sum; // 청소년 상어가 잡아먹은 물고기들의 번호의 합

// 맵에서의 물고기 이동(번호 순서대로)
void moveFish() {
	for (int i = 1; i < SIZE_F; i++) {
		FISH now = INFO[i];
		if (now.alive == 1) { // 살아있는 물고기만 이동한다
			// 현재의 방향으로 이동 불가하다면
			// 한바퀴 돌면서 다른 방향으로 이동 가능한가를 판단
			for (int j = 0; j < DIR_NUM; j++) {
				int nDir = (now.dir + j) % DIR_NUM;

				int ny = now.y + ydir[nDir];
				int nx = now.x + xdir[nDir];

				if (ny < 0 || nx < 0 || ny >= SIZE_N || nx >= SIZE_N) continue;// 격자 밖은 이동 불가
				if (MAP[ny][nx] == -1) continue; // 상어가 있는 칸은 이동 불가

				if (MAP[ny][nx] == 0) { // 빈칸 - i번 물고기만 이동
					MAP[now.y][now.x] = 0;
					MAP[ny][nx] = i;

					INFO[i] = { ny, nx, nDir, 1 }; // 위치와 방향 갱신
					break;
				}
				else { // 다른 물고기가 있는 칸 - i번 물고기와 (ny, nx)의 물고기가 자리 변경
					int tmp = MAP[ny][nx];
					MAP[ny][nx] = MAP[now.y][now.x];
					MAP[now.y][now.x] = tmp;

					INFO[tmp].y = now.y;
					INFO[tmp].x = now.x;
					INFO[i] = { ny, nx, nDir, 1 }; // 위치와 방향 갱신
					break;
				}
			}
		}
	}
}

// 물고기가 이동한 후 상어가 움직인다
void move() {
	// 물고기들이 이동하기 전에 현재의 지도와 물고기 정보를 저장한다
	int TMP[SIZE_N][SIZE_N] = { 0, };
	FISH TMP_FISH[SIZE_F] = { 0, };
	memcpy(TMP, MAP, sizeof(MAP));
	memcpy(TMP_FISH, INFO, sizeof(INFO));

	moveFish(); // 물고기들 이동

	int isMoved = 0; // 이번 턴에 상어가 이동할 칸이 있는가?
	FISH shark = INFO[0]; // 상어의 정보
	for (int i = 1; i <= SIZE_N; i++) { // 현재 방향으로는 몇 칸이든 이동 가능
		int ny = shark.y + ydir[shark.dir] * i;
		int nx = shark.x + xdir[shark.dir] * i;

		if (ny < 0 || nx < 0 || ny >= SIZE_N || nx >= SIZE_N) break; // 격자 밖으로 벗어났다면 더이상 이동 불가
		if (MAP[ny][nx] == 0) continue; // 빈 칸은 이동 불가

		isMoved = 1; // 이번 턴에 상어 이동했다
		int target = MAP[ny][nx]; // 이번에 잡아먹을 물고기 번호

		// 상어가 target번 물고기를 잡아먹는다
		MAP[shark.y][shark.x] = 0;
		MAP[ny][nx] = -1;
		sum += target;
		INFO[target].alive = 0;
		INFO[0] = { ny, nx, INFO[target].dir, 1 };

		move(); // 다음 턴으로 가기

		// 다음 턴 탐색을 마쳤다면 target번 물고기 잡아먹은 정보 원복 - target번 물고기 살리기
		INFO[0] = shark;
		INFO[target].alive = 1;
		sum -= target;
		MAP[ny][nx] = target;
		MAP[shark.y][shark.x] = -1;
	}

	// 맨 위에 물고기들 이동 전에 저장한 정보로 다시 원복하기
	memcpy(MAP, TMP, sizeof(TMP));
	memcpy(INFO, TMP_FISH, sizeof(TMP_FISH));

	// 상어가 이동할 수 있는 칸이 없다면
	if (isMoved == 0) {
		if (sum > ans) ans = sum; // 최대값 갱신 후 종료
		return;
	}
}

int main() {
	// input
	int ia, ib;
	int tmp = 1;
	for (int i = 0; i < SIZE_N; i++) {
		for (int j = 0; j < SIZE_N; j++) {
			cin >> ia >> ib;
			MAP[i][j] = ia;
			INFO[ia] = { i, j, ib - 1, 1 }; // 상어의 정보 저장
		}
	}

	// 0. 상어가 (0,0)의 물고기를 먹으면서 시작한다
	sum += MAP[0][0];
	INFO[MAP[0][0]].alive = 0;
	INFO[0] = { 0, 0, INFO[MAP[0][0]].dir, 1 };
	MAP[0][0] = -1;

	move();

	// output
	cout << ans << "\n";

	return 0;
}