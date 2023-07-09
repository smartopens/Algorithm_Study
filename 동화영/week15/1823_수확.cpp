// 1823 수확
#include <iostream>
#include <algorithm>
using namespace std;

// DP 문제 - 솔직히 다른 사람의 풀이를 보았다..
// 

int dp[2001][2001]; // [left, right] 영역 내에서 낼 수 있는 최대 점수
int values[2001]; // 각 칸의 벼의 가치
int N; // 밭의 사이즈

int agriculture(int st, int en, int point) {
	if (st > en) return 0; // 인덱스 범위 초과시 0 반환

	if (dp[st][en] > 0) return dp[st][en]; // 이미 구한 값이 있다면 해당 값 반환

	// 아직 값이 없다면 구해오기
	// [st, en] 영역 내에서 현재 (left를 선택한 결과)와 (right를 선택한 결과) 중 큰 값 가져오기
	return dp[st][en] = max(agriculture(st + 1, en, point + 1) + values[st] * point,
							agriculture(st, en - 1, point + 1) + values[en] * point);
}

int main() {
	// input
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> values[i];

	// solve & output
	cout << agriculture(1, N, 1);

	return 0;
}