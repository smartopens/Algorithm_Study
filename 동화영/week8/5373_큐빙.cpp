#include <iostream>
#include <cstring>
using namespace std;

// 0: 위
// 1: 아래
// 2: 앞
// 3: 오른쪽
// 4: 뒤
// 5: 왼쪽
char cube[6][3][3];
char colors[7] = "wyrbog"; // 흰 노랑 빨강 파랑 오렌지 초록
char pages[7] = "UDFRBL"; // 위 아래 앞 오른 뒤 왼
// 6면에 대해 2가지(+,-) 방향으로 돌릴 때
// 영향이 가는 옆에 4면
int target[6][2][4] = {
	{{4, 5, 2, 3}, {4, 3, 2, 5}},
	{{2, 5, 4, 3}, {2, 3, 4, 5}},
	{{0, 5, 1, 3}, {0, 3, 1, 5}},
	{{0, 2, 1, 4}, {0, 4, 1, 2}},
	{{0, 3, 1, 5}, {0, 5, 1, 3}},
	{{0, 4, 1, 2}, {0, 2, 1, 4}}
};

char ans[100][3][3];

void init() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cube[i][j][k] = colors[i];
			}
		}
	}
}

// ind번째 면 자체를 dir방향으로 돌린다
void rFront(int ind, char dir) {
	char temp[3][3] = { 0, };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (dir == '+') temp[j][2-i] = cube[ind][i][j];
			else temp[2-j][i] = cube[ind][i][j];
		}
	}

	memcpy(cube[ind], temp, sizeof(temp));
}

// ind번째 면이 옆면들을 dir방향으로 돌린다
void rBeside(int ind, char dir) {
	int d = dir == '+' ? 0 : 1;
	int temp[3] = { 0 };

	if (ind == 0) {
		for (int i = 0; i < 3; i++)
			temp[i] = cube[4][0][i];
		if (d == 0) { // 시계
			for (int i = 0; i < 3; i++)
				cube[4][0][i] = cube[5][0][i];
			for (int i = 0; i < 3; i++)
				cube[5][0][i] = cube[2][0][i];
			for (int i = 0; i < 3; i++)
				cube[2][0][i] = cube[3][0][i];
			for (int i = 0; i < 3; i++)
				cube[3][0][i] = temp[i];
		}
		else { // 반시계
			for (int i = 0; i < 3; i++)
				cube[4][0][i] = cube[3][0][i];
			for (int i = 0; i < 3; i++)
				cube[3][0][i] = cube[2][0][i];
			for (int i = 0; i < 3; i++)
				cube[2][0][i] = cube[5][0][i];
			for (int i = 0; i < 3; i++)
				cube[5][0][i] = temp[i];
		}
	}
	else if (ind == 1) {
		for (int i = 0; i < 3; i++)
			temp[i] = cube[2][2][i];
		if (d == 0) { // 시계
			for (int i = 0; i < 3; i++)
				cube[2][2][i] = cube[5][2][i];
			for (int i = 0; i < 3; i++)
				cube[5][2][i] = cube[4][2][i];
			for (int i = 0; i < 3; i++)
				cube[4][2][i] = cube[3][2][i];
			for (int i = 0; i < 3; i++)
				cube[3][2][i] = temp[i];
		}
		else { // 반시계
			for (int i = 0; i < 3; i++)
				cube[2][2][i] = cube[3][2][i];
			for (int i = 0; i < 3; i++)
				cube[3][2][i] = cube[4][2][i];
			for (int i = 0; i < 3; i++)
				cube[4][2][i] = cube[5][2][i];
			for (int i = 0; i < 3; i++)
				cube[5][2][i] = temp[i];
		}
	}
	else if (ind == 2) { // 앞
		for (int i = 0; i < 3; i++)
			temp[i] = cube[0][2][i];
		if (d == 0) { // 시계
			for (int i = 0; i < 3; i++)
				cube[0][2][i] = cube[5][2 - i][2];
			for (int i = 0; i < 3; i++)
				cube[5][i][2] = cube[1][0][i];
			for (int i = 0; i < 3; i++)
				cube[1][0][i] = cube[3][2-i][0];
			for (int i = 0; i < 3; i++)
				cube[3][i][0] = temp[i];
		}
		else { // 반시계
			for (int i = 0; i < 3; i++)
				cube[0][2][i] = cube[3][i][0];
			for (int i = 0; i < 3; i++)
				cube[3][i][0] = cube[1][0][2-i];
			for (int i = 0; i < 3; i++)
				cube[1][0][i] = cube[5][i][2];
			for (int i = 0; i < 3; i++)
				cube[5][i][2] = temp[2 - i];
		}
	}
	else if (ind == 3) { // 오른
		for (int i = 0; i < 3; i++)
			temp[i] = cube[0][i][2];
		if (d == 0) { // 시계
			for (int i = 0; i < 3; i++)
				cube[0][i][2] = cube[2][i][2];
			for (int i = 0; i < 3; i++)
				cube[2][i][2] = cube[1][i][2];
			for (int i = 0; i < 3; i++)
				cube[1][i][2] = cube[4][2 - i][0];
			for (int i = 0; i < 3; i++)
				cube[4][i][0] = temp[2 - i];
		}
		else { // 반시계
			for (int i = 0; i < 3; i++)
				cube[0][i][2] = cube[4][2 - i][0];
			for (int i = 0; i < 3; i++)
				cube[4][i][0] = cube[1][2 - i][2];
			for (int i = 0; i < 3; i++)
				cube[1][i][2] = cube[2][i][2];
			for (int i = 0; i < 3; i++)
				cube[2][i][2] = temp[i];
		}
	}
	else if (ind == 4) { // 뒤
		for (int i = 0; i < 3; i++)
			temp[i] = cube[0][0][2 - i];
		if (d == 0) {
			for (int i = 0; i < 3; i++)
				cube[0][0][i] = cube[3][i][2];
			for (int i = 0; i < 3; i++)
				cube[3][i][2] = cube[1][2][2 - i];
			for (int i = 0; i < 3; i++)
				cube[1][2][i] = cube[5][i][0];
			for (int i = 0; i < 3; i++)
				cube[5][i][0] = temp[i];
		}
		else {
			for (int i = 0; i < 3; i++)
				cube[0][0][i] = cube[5][i][0];
			for (int i = 0; i < 3; i++)
				cube[5][i][0] = cube[1][2][i];
			for (int i = 0; i < 3; i++)
				cube[1][2][i] = cube[3][2-i][2];
			for (int i = 0; i < 3; i++)
				cube[3][i][2] = temp[2-i];
		}
	}
	else if (ind == 5) { // 왼
		for (int i = 0; i < 3; i++)
			temp[i] = cube[0][i][0];
		if (d == 0) {
			for (int i = 0; i < 3; i++)
				cube[0][i][0] = cube[4][2 - i][2];
			for (int i = 0; i < 3; i++)
				cube[4][i][2] = cube[1][2 - i][0];
			for (int i = 0; i < 3; i++)
				cube[1][i][0] = cube[2][i][0];
			for (int i = 0; i < 3; i++)
				cube[2][i][0] = temp[i];
		}
		else {
			for (int i = 0; i < 3; i++)
				cube[0][i][0] = cube[2][i][0];
			for (int i = 0; i < 3; i++)
				cube[2][i][0] = cube[1][i][0];
			for (int i = 0; i < 3; i++)
				cube[1][i][0] = cube[4][2-i][2];
			for (int i = 0; i < 3; i++)
				cube[4][i][2] = temp[2-i];
		}
	}
}

void rotate(char page, char dir) {
	for (int i = 0; i < 6; i++) {
		if (pages[i] == page) {
			rFront(i, dir);
			rBeside(i, dir);
		}
	}
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		init();

		int n;
		cin >> n;

		char page, dir;
		for (int i = 0; i < n; i++) {
			cin >> page >> dir;

			rotate(page, dir);
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				ans[tc - 1][i][j] = cube[0][i][j];
				//cout << cube[0][i][j];
			}
			//cout << '\n';
		}
	}

	for (int i = 0; i < T; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cout << ans[i][j][k];
			}
			cout << '\n';
		}
	}

	return 0;
}

/*
1
24
L+ L- L- L+ R- R+ R+ R- F+ F- F- F+ D- D+ D+ D- U+ U- U- U+ B- B+ B+ B-
*/