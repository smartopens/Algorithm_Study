#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

// 원판 정보, 최종 원판 수 설정
int n, m, t;
int board[50][50];
int b_nums;

// 회전 후 조건에 따라 원판 정보를 갱신하기
// 인접한 숫자가 있는 경우: board 0으로 갱신
// 인접한 숫자가 없는 경우: mid값에 따라 board 정보 갱신
void board_change() {
	// 인접한 수가 있는지 확인한다.
	// 인접한 경우의 원판 수들은 c_board에 기록하고 이용한다.
	bool one_s = false;
	int c_board[50][50] = { {} };

	// 열 방향 인접한 수 고려하기
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m - 1; c++) {
			if (board[r][c] == 0) continue;
			if (board[r][c] == board[r][c + 1]) {
				one_s = true;
				c_board[r][c] = 1;
				c_board[r][c + 1] = 1;
			}
		}

		if (board[r][m - 1] == board[r][0]) {
			if (board[r][m-1] == 0) continue;
			one_s = true;
			c_board[r][m - 1] = 1;
			c_board[r][0] = 1;
		}

	}

	// 행 방향 인접한 수 고려하기
	for (int c = 0; c < m; c++) {
		for (int r = 0; r < n - 1; r++) {
			if (board[r][c] == 0) continue;
			if (board[r][c] == board[r + 1][c]) {
				one_s = true;
				c_board[r][c] = 1;
				c_board[r + 1][c] = 1;
			}
		}
	}

	// 인접한 수가 있는 경우
	if (one_s == true) {
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < m; c++) {
				if (c_board[r][c] == 0) continue;
				board[r][c] = 0;
			}
		}
	}
	// 인접한 수가 없는 경우
	else if (one_s == false) {
		// 원판에 남은 수에서 평균을 구하기
		float mid = 0;
		int cnt = 0;

		for (int r = 0; r < n; r++) {
			for (int c = 0; c < m; c++) {
				if (board[r][c] == 0) continue;

				mid += board[r][c];
				cnt += 1;
			}
		}

		mid = (float)mid/cnt;

		// 평균 수에 따라서 원판 정보 갱신하기
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < m; c++) {
				if (board[r][c] == 0) continue;
				if (board[r][c] > mid) {
					board[r][c] -= 1;
				}
				else if (board[r][c] < mid) {
					board[r][c] += 1;
				}
			}
		}
	}
};

// 원판 회전
// 반시계 방향일 경우 전체 원판 크기 - k 번 회전한다. --> 시계 방향 회전
// 시계방향일 경우 k번 회전한다.
void cycle(int r, int d, int k) {
	if (d == 1) {
		k = m - k;
	}

	for (int i = 0; i < k; i++) {
		int tmp = board[r][m - 1];
		for (int c = m - 1; c > 0; c--) {
			board[r][c] = board[r][c - 1];
		}
		board[r][0] = tmp;
	}
};

int main() {

	cin >> n >> m >> t;

	// 원판 정보 입력
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			cin >> board[r][c];
		}
	}

	// 회전 정보 입력
	for (int c = 0; c < t; c++) {
		// x배수 만큼, d방향, k번 회전한다.
		int x, d, k;
		cin >> x >> d >> k;
		
		// x의 배수 만큼 회전하기
		for (int i = x; i < n + 1; i += x) {
			cycle(i - 1, d, k);
		}

		// 원판 정보 갱신하기
		board_change();
	}

	// 최종 원판 수 구하기
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			b_nums += board[r][c];
		}
	}

	cout << b_nums << endl;

	return 0;
};
