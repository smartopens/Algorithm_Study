/* 이차원 배열과 연산 */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define MAX_N 101

struct numSet {
	int num; // 숫자
	int cnt; // 등장 횟수

	// 등장횟수 -> 숫자 순으로 오름차순
	bool operator < (numSet nxt) const {
		if (cnt < nxt.cnt) return false;
		if (cnt > nxt.cnt) return true;
		if (num < nxt.num) return false;
		if (num > nxt.num) return true;
		return false;
	}
};

priority_queue<numSet> pq;
int MAP[MAX_N][MAX_N]; // 배열

int rLen, cLen;

// R연산 : 행에 대한 정렬
void sortRow() {
	// * 행에 대한 정렬 -> 열의 개수가 변한다
	int colCnt = 0;
	for (int i = 1; i <= rLen; i++) { // 각 행마다 정렬 진행
		// 숫자의 등장횟수를 카운팅할 DAT
		int DAT[MAX_N] = { 0, };
		for (int j = 1; j < MAX_N; j++) {
			if (MAP[i][j] != 0) DAT[MAP[i][j]]++;
		}

		// 등장을 한 번이라도 한 숫자에 한해
		// (숫자, 등장횟수)를 pq에 push한다 -> 정렬
		for (int j = 1; j < MAX_N; j++) {
			if (DAT[j] != 0) pq.push({ j, DAT[j] });
		}

		// i번째 행을 0으로 초기화 -> 길이가 가장 길어진 행의 길이(열)에 맞추기 위해
		for (int j = 1; j < MAX_N; j++) {
			MAP[i][j] = 0;
		}

		// pq를 돌면서 정렬 결과를 기록
		int ind = 1;
		while (!pq.empty()) {
			// 배열에 정렬시 최대 100개만 저장
			if (ind > 100) {
				while (!pq.empty()) pq.pop();
				break;
			}

			numSet now = pq.top();
			pq.pop();

			// 저장은 (숫자, 횟수) 순서로
			MAP[i][ind] = now.num;
			MAP[i][ind + 1] = now.cnt;

			ind += 2;
		}
		
		// i번째 행 정렬 결과의 길이
		if (ind - 1 > colCnt) colCnt = ind - 1;
	}

	// 행들 중 가장 긴 길이(열)를 갱신
	cLen = colCnt;
}

// 동작은 R연산과 동일하나 인덱스의 차이
// C연산 : 열에 대한 정렬
void sortCol() {
	int rowCnt = 0;
	for (int i = 1; i <= cLen; i++) {
		int DAT[MAX_N] = { 0, };
		for (int j = 1; j < MAX_N; j++) {
			if (MAP[j][i] != 0) DAT[MAP[j][i]]++;
		}

		for (int j = 1; j < MAX_N; j++) {
			if (DAT[j] != 0) pq.push({ j, DAT[j] });
		}

		// i번째 열을 0으로 초기화
		for (int j = 1; j < MAX_N; j++) {
			MAP[j][i] = 0;
		}

		int ind = 1;
		while (!pq.empty()) {
			if (ind > 100) {
				while (!pq.empty()) pq.pop();
				break;
			}

			numSet now = pq.top();
			pq.pop();

			MAP[ind][i] = now.num;
			MAP[ind + 1][i] = now.cnt;

			ind += 2;
		}

		if (ind - 1 > rowCnt) rowCnt = ind - 1;
	}

	rLen = rowCnt;
}

int main() {
	// input
	int r, c, k;
	cin >> r >> c >> k;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> MAP[i][j];
		}
	}

	// 초기 배열의 사이즈 = 3*3
	rLen = 3, cLen = 3;

	int ans = 0; // 연산 시간
	while (MAP[r][c] != k) {
		// 연산 시간이 100초가 지났다면 -1 출력
		if (ans == 100) {
			ans = -1;
			break;
		}

		// (행의 개수 >= 열의 개수) - 행에 대해 정렬
		if (rLen >= cLen) {
			sortRow();
		}
		// (행의 개수 < 열의 개수) - 열에 대해 정렬
		else {
			sortCol();
		}

		ans++; // 연산시간 증가
	}

	// output
	cout << ans;

	return 0;
}