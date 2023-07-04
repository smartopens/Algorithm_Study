// 1229 육각수
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 213456789;
int dp[1000000];
vector<int> nums;

// 육각수의 수 계산 및 저장
void calcCnt(int N) {
	nums.push_back(0);
	int sum = 1, prev = 0, ind = 2;

	while (sum <= N) {
		prev = sum;
		nums.push_back(prev);
		dp[prev] = 1;

		// 겹치는 부분 제외하고 새로 추가되는 육각수의 점의 개수는
		// (ind - 1) * 4 + 1 개이다
		sum += (ind - 1) * 4 + 1;
		ind++;
	}
}

int main() {
	// input
	int N;
	cin >> N;

	// 육각수의 수 계산
	calcCnt(N);

	int sz = nums.size();
	dp[1] = 1;
	for (int i = 2; i <= N; ++i) { // 2부터 N까지
		if(dp[i] == 0) dp[i] = INF;
		else continue;

		// 육각수의 수 기준으로 필요한 개수 + 1 과
		// 현재의 값을 비교하여 min값으로 갱신
		for (int j = 1; j < sz; ++j) {
			if (nums[j] > i) break;
			dp[i] = min(dp[i - nums[j]] + 1, dp[i]);
		}
	}

	// output
	cout << dp[N] << "\n";

	return 0;
}