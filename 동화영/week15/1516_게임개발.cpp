// 1516 게임 개발
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

queue<int> q;
vector<int> al[501];
int indegree[501];
int times[501];
int ans[501];
int N;

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int prev;
		cin >> times[i];

		while (1) {
			cin >> prev;
			if (prev == -1) break;

			indegree[i]++;
			al[prev].push_back(i);
		}
	}

	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0) {
			q.push(i);
			ans[i] = times[i];
		}
	}

	for (int i = 1; i <= N; i++) {
		if (q.empty()) break;

		int now = q.front();
		q.pop();

		for (int j = 0; j < al[now].size(); j++) {
			int nxt = al[now][j];
			ans[nxt] = max(ans[nxt], ans[now] + times[nxt]);

			indegree[nxt]--;
			if (indegree[nxt] == 0) q.push(nxt);
		}

	}

	for (int i = 1; i <= N; i++) {
		cout << ans[i] << "\n";
	}

	return 0;
}