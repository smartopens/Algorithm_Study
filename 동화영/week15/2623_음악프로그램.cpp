// 2623 음악프로그램
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 위상정렬
// DAG(Directed Acyclic Graph)의 그래프에서 적용 가능

queue<int> q;
vector<int> ans; // 가능한 순서 (역순으로 저장)
vector<int> orders[1001]; // 간선 (순서의 역순을 저장)
int indegree[1001]; // 각 정점의 indegree (나가는 화살표의 수)
int N, M; // N: 가수의 수, M: 보조PD의 수

int main() {
	// input
	int cnt, prev, nxt;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> cnt;

		cin >> prev;
		for (int j = 1; j < cnt; j++) {
			cin >> nxt;
			orders[nxt].push_back(prev); // nxt 완료 후 prev의 indegree를 감소시키기 위해 역수으로 저장
			indegree[prev]++; // prev에서 나가는 화살표의 수 증가
			prev = nxt;
		}
	}

	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0) q.push(i); // indegree가 0인 지점 queue에 넣기
	}

	// N번 반복하면서 하나의 지점씩 ans에 넣기
	for (int i = 1; i <= N; i++) {
		// N번 반복되기 전에 queue가 비었다면 더이상 방문 가능한 지점이 없다
		// 즉, 싸이클이 존재
		if (q.empty()) break;

		int now = q.front();
		q.pop();
		ans.push_back(now);

		// now 지점보다 먼저 방문해야 하는 nxt 지점의 indegree 감소 처리
		for (int j = 0; j < orders[now].size(); j++) {
			int nxt = orders[now][j];
			indegree[nxt]--;
			if (indegree[nxt] == 0) q.push(nxt); //indegree가 0이 된다면 queue에 넣기
		}
	}

	// 싸이클 존재 시 0 출력 후 종료
	if (ans.size() < N) {
		cout << 0 << "\n";
		return 0;
	}

	// output
	for (int i = 1; i <= N; i++) {
		cout << ans[N - i] << "\n";
	}

	return 0;
}