// 9251 LCS
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Longest Common Subsequence 최장 공통 부분 수열
// 주어진 두 수열 모두에 포함되는 부분 수열 중 가장 긴 수열 찾기
// 연속되는 문자열이 아니다

int dp[1010][1010];

int main() {
	// input
	string a, b;
	int n, m;

	cin >> a >> b;
	n = a.size();
	m = b.size();

	// a[i] == b[j] 인 경우, dp[i-1][j-1] 보다 1 증가
	// a[i] != b[j] 인 경우, dp[i][j-1] 과 dp[i-1][j] 중 더 큰 값을 선택
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	// output
	cout << dp[n][m] << "\n";

	return 0;
}