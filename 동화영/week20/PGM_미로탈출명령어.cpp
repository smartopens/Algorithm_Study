// PGM - 미로 탈출 명령어
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

char dir[5] = "dlru";
int dr[4] = { 1, 0, 0, -1 }; // dlru 순
int dc[4] = { 0, -1, 1, 0 };
bool flag = false; // 현재 기준 답을 찾았는가를 저장
string answer; // 반환할 답
int n, m, x, y, r, c, k; // n*m 격자, 시작점(x,y), 도착점(r,c), 최대 k 길이

// 현재 (curr, curc)에 위치하며 cnt번 이동한 상태이다
void dfs(int curr, int curc, int cnt) {
	// 답 찾았다면 더이상 탐색 X
	// 이미 사전 순으로 탐색하였기에 답을 한 번 찾았다면 그게 사전순 가장 먼저이다
	//if (flag) return;

	// (더 이동 가능한 횟수) - (현재 위치에서 도착 지점까지 남은 거리)
	int remain = (k - cnt) - (abs(curr - r) + abs(curc - c));
	if (remain < 0) return; // 이동 가능한 횟수가 안남았다면 불가
	if (remain % 2 != 0) return; // 홀수 번 이상 남았다면 이동 불가 - 왔다갔다 하려면 짝수번 이동 필요

	// 도착지점까지 k번 걸려서 왔다면 flag 변경 및 종료
	if (curr == r && curc == c && cnt == k) {
		flag = true;
		return;
	}

	// 4방향 탐색
	for (int i = 0; i < 4; i++) {
		int nr = curr + dr[i];
		int nc = curc + dc[i];

		if (nr <= 0 || nc <= 0 || nr > n || nc > m) continue; // 격자 밖은 이동 불가

		answer += dir[i]; // 탐색 전 answer 방향 추가
		dfs(nr, nc, cnt + 1); // 다음 지점으로 탐색
		if (flag) return; // 답을 찾았다면 바로 종료 - 종료하지 않으면 마지막 경로를 pop_back 하여서 안됨
		answer.pop_back(); // 탐색 후 answer 방향 제거
	}
}

string solution(int _n, int _m, int _x, int _y, int _r, int _c, int _k) {
	// input
	// 입력값을 전역변수로 저장
	n = _n, m = _m, x = _x, y = _y, r = _r, c = _c, k = _k;

	// solve
	dfs(x, y, 0);

	// return
	if (answer == "") return "impossible"; // 답을 못찾았다면 impossible 반환
	return answer;
}

//int main() {
//	cout << solution(3, 4, 2, 3, 3, 1, 5) << "\n";
//
//	return 0;
//}