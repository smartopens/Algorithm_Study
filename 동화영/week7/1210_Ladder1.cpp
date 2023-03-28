/* Ladder 1 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
const int SIZE_N = 100;

struct NODE {
	int y;
	int x;
};

int ydir[] = { 0, 0, -1 }; // 0좌 1우 2상
int xdir[] = { -1, 1, 0 };

int MAP[SIZE_N][SIZE_N]; // 사디리타기 게임판
NODE target; // 도착지점

// 도착지점(2)을 시작으로 시작지점을 찾으러 간다
// 1. 현재 가는 방향이 상이다 -> 좌우칸을 만날 때까지 쭉 올라간다
// 2. 현재 가는 방향이 좌우이다 -> 게임판의 끝 | 0을 만날 때까지 쭉 옆으로 간다
int bfs() {
	int ndir = 2; // 초기방향을 위
	NODE now = { target.y, target.x }; // 도착지점을 시작으로 한다

	// 0번째 행에 도착할 때까지 탐색한다
	while (now.y != 0) {
		if (ndir == 2) { // 상
			// 현재의 행부터 위로 쭉 올라가다가
			for (int i = now.y; i >= 0; i--) {
				if (i == 0) { // 0번째 행에 도착하면 좌표 저장 및 나가기
					now = { i, now.x };
					break;
				}

				if (now.x > 0 && MAP[i][now.x - 1] == 1) { // 왼쪽에 길이 있다면
					// 방향 전환 및 좌표 저장 후 나가기
					ndir = 0;
					now = { i, now.x - 1 };
					break;
				}
				else if (now.x < SIZE_N - 1 && MAP[i][now.x + 1] == 1) { // 오른쪽에 길이 있다면
					// 방향 전환 및 좌표 저장 후 나가기
					ndir = 1;
					now = { i, now.x + 1 };
					break;
				}
			}
		}
		else if (ndir == 1) { // 우
			// 현재의 열부터 오른쪽으로 쭉 가다가
			for (int i = now.x; i <= SIZE_N; i++) {
				// 게임판을 벗어나거나 0을 만나면
				if (i == SIZE_N || MAP[now.y][i] == 0) {
					// 방향을 상으로 전환 및 좌표 저장
					ndir = 2;
					// now.y - 1로 저장을 해야 왔던 길 되돌아가지 않는다 -> now.y로 저장하면 온 길로 다시 되돌아간다.. (왼쪽 방향도 동일)
					now = { now.y - 1, i - 1 }; // 0을 만났을 때 if문 안에 들어왔으므로 i-1로 지정
					break;
				}
			}
		}
		else if (ndir == 0) { // 좌
			// 현재의 열부터 왼쪽으로 쭉 가다가
			for (int i = now.x; i >= -1; i--) {
				// 게임판을 벗어나거나 0을 만나면
				if (i == -1 || MAP[now.y][i] == 0) {
					// 방향을 상으로 전환 및 좌표 저장
					ndir = 2;
					now = { now.y - 1, i + 1 }; // 0을 만났을 때 if문 안에 들어왔으므로 i+1로 저장
					break;
				}
			}
		}

		//cout << now.y << " " << now.x << "\n";
	}

	return now.x;
}

int main() {
	//freopen("input_1210.txt", "r", stdin);

	int T = 10;
	for (int tc = 1; tc <= T; tc++) {
		// input
		int num;
		cin >> num;

		for (int i = 0; i < SIZE_N; i++) {
			for (int j = 0; j < SIZE_N; j++) {
				cin >> MAP[i][j];
				if (i == SIZE_N - 1 && MAP[i][j] == 2) {
					target = { i,j }; // 도착지점을 저장
				}
			}
		}

		// solve & output
		cout << "#" << num << " " << bfs() << "\n";
	}

	return 0;
}