#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int n, k;

// 물품 정보 저장
struct thing {
	int w;
	int val;
};

// 물품들, dp를 선언한다.
// 물품: 무게, 가치
// dp: 각 물품들의 담을 수 있는 무게당 최대 가치를 기록한다.
thing things[102];
int dp[102][100010];
int path[102];

// Top-down 방식
// 마지막 물품부터 탐색했다.
// now_w: 담을 수 있는 무게 공간
// now: 현재 물품 번호 또는 층의 깊이
int dfs(int now, int now_w) {
	// 모든 물품을 본 경우
	if (now < 1) {

		return 0;
	}

	// 해당 물품의 무게를 담지 못할 경우
	if (now_w < things[now].w) {
		return dfs(now - 1, now_w);
	}

	// 이미 최대가치가 기록된 경우
	if (dp[now][now_w] != 0) {
		return dp[now][now_w];
	}

	// 물품을 담는 경우와 담지 않는 경우로 고려한다.
	int max_val = 0;
	int case_val1 = dfs(now - 1, now_w - things[now].w) + things[now].val;
	int case_val2 = dfs(now - 1, now_w);

	max_val = max(case_val1, case_val2);

	// 해당 물품의 무게경우에서 최대가치를 기록한다.
	return dp[now][now_w] = max_val;
};

int main() {
	cin >> n >> k;

	// dp 초기화하기
	for (int r = 0; r < n + 1; r++)
	{
		for (int c = 0; c < 100010; c++)
		{
			dp[r][c] = 0;
		}
	}

	// 물품들의 정보를 입력받기
	// weight: 무게 / value: 가치
	for (int ti = 1; ti < n + 1; ti++)
	{
		int weight, value;
		cin >> weight;
		cin >> value;
		things[ti].w = weight;
		things[ti].val = value;
	}

	// 최대 가치를 구한다.
	int total_max_val = 0;

	total_max_val = dfs(n, k);

	cout << total_max_val << endl;

	return 0;
}