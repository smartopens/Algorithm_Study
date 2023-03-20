/* 게리맨더링2 */
#include <iostream>
#include <cstring>
using namespace std;
#define MAX_N 20
#define TERR 6

int SECTION[MAX_N][MAX_N]; // 각 칸의 선거구 구분
int MAP[MAX_N][MAX_N]; // 재현시 내 각 구역의 인구 수
int N; // 재현시의 크기

int ans; // (최대 - 최소) 인구 수 차이 중 최소 (답)

// (r, c)칸이 몇 번 선거구인지를 반환
int findGroup(int r, int c, int x, int y, int d1, int d2) {
	if (SECTION[r][c] == 5) return 5;
	else if (r >= 0 && r < x + d1 && c >= 0 && c <= y) return 1;
	else if (r >= 0 && r <= x + d2 && c > y && c < N) return 2;
	else if (r >= x + d1 && r < N && c >= 0 && c < y - d1 + d2) return 3;
	else if (r > x + d2 && r < N && c >= y - d1 + d2 && c < N) return 4;
	else return 5;
}

// 5번 선거구를 표시
void setSection(int x, int y, int d1, int d2) {
	int rdir[] = { 1, 1, -1, -1 }; // 하우, 하좌, 상좌, 상우
	int cdir[] = { 1, -1, -1, 1 };

	// 테두리
	for (int i = 0; i <= d1; i++) {
		SECTION[x + i][y - i] = 5;
	}
	for (int i = 0; i <= d2; i++) {
		SECTION[x + i][y + i] = 5;
	}
	for (int i = 0; i <= d2; i++) {
		SECTION[x + d1 + i][y - d1 + i] = 5;
	}
	for (int i = 0; i <= d1; i++) {
		SECTION[x + d2 + i][y + d2 - i] = 5;
	}

	// 테두리 내부
	bool isOn = false;
	for (int i = x + 1; i < x + d1 + d2; i++) {
		isOn = false;
		for (int j = y - d1; j <= y + d2; j++) {
			if (SECTION[i][j] == 5 && !isOn) isOn = true;
			else if (SECTION[i][j] == 5 && isOn) break;
			else if (isOn) SECTION[i][j] = 5;
		}
	}
}

// 각 지역구별로 인구 수 계산하기
int sumPeople(int x, int y, int d1, int d2) {
	int people[TERR] = { 0, };

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// (i,j)칸의 선거구를 확인하여 인구수 추가
			people[findGroup(i, j, x, y, d1, d2)] += MAP[i][j];
		}
	}

	// 인구수가 최소/최대인 값 구하여 반환
	int minS = 21e8;
	int maxS = -21e8;
	for (int i = 1; i < TERR; i++) {
		if (people[i] < minS) minS = people[i];
		if (people[i] > maxS) maxS = people[i];
	}

	return maxS - minS;
}

// 2. (r,c) 지역을 기점으로 경계선의 길이 구하기 - (d1, d2) 정하기
void findDist(int r, int c) {
	for (int i = 1; i <= c; i++) { // d1
		if (r + i >= N) break;
		for (int j = 1; j < N - c; j++) { //d2
			if (r + i + j >= N) break;

			// 5번 선거구 표시하기
			memset(SECTION, 0, sizeof(SECTION));
			setSection(r, c, i, j);

			// 3. 경계선이 정해졌으니 각 선거구의 인구수를 계산한다
			int diff = sumPeople(r, c, i, j);
			if (diff < ans) { // 차이가 최소라면 갱신
				ans = diff;
			}
		}
	}
}

int main() {
	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	// solve
	ans = 21e8;

	// 1. 각 칸에서 구역을 시작한다 - (x,y) 정하기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			findDist(i, j);
		}
	}

	// output
	cout << ans;

	return 0;
}

/*
7
1 2 3 4 1 6 1
7 8 9 1 4 2 1
2 3 4 1 1 3 1
6 6 6 6 9 4 1
9 1 9 1 9 5 1
1 1 1 1 9 9 1
1 1 1 1 9 9 1
*/