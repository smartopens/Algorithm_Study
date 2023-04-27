/* 동전 1 */
#include <iostream>
#include <algorithm>
using namespace std;

int dp[10001]; // 각 금액을 만들 수 있는 경우의 수
int coins[100]; // 주어지는 n개의 동전 금액
int n, k; // n: 동전 개수 k: 목표금액

int main() {
	// input
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> coins[i];
	}
	
	// dp[nxt] = dp[nxt] + dp[nxt - coins[i]]
	// nxt원 만들기 = 기존의 nxt원 가능 수 + 기존의 (nxt-coins[i])원 가능 수
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		int coin = coins[i];
		for (int j = coin; j <= k; j++) {
			if (dp[j - coin] > 0) {
				dp[j] += dp[j - coin];
			}
		}
	}

	cout << dp[k];

	return 0;
}