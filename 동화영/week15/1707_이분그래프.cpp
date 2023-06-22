#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> al[20001]; // 인접리스트
int visited[20001]; // 각 노드의 그룹 1:A그룹, -1:B그룹, 0:미방문
int V, E; // V: 노드의 개수, E: 간선의 개수

void init() {
	for (int i = 0; i < 20001; i++) {
		al[i].clear();
		visited[i] = 0;
	}
}

// 1. start 노드부터 탐색 시작 (A그룹을 시작으로 두기)
// 2. now번 노드와 인접한 노드들만 탐색
int bfs(int start) {
	queue<int> q;
	q.push(start);
	visited[start] = 1;

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		int flag = visited[now];

		for (int i = 0; i < al[now].size(); i++) {
			int nxt = al[now][i];

			if (visited[now] == visited[nxt]) return 0; // now와 nxt는 인접한다. 근데 이미 확정된 그룹도 동일하다면 해당 테스트케이스는 이분그래프가 아니다.
			if (visited[nxt] != 0) continue; // now와 nxt는 이미 다른 그룹으로 분류되었다. 그러므로 nxt 노드는 탐색할 필요 X

			q.push(nxt);
			visited[nxt] = flag * -1;
		}
	}

	return 1;
}

int main() {
	int tc;
	cin >> tc;

	int a, b;
	for (int t = 0; t < tc; t++) {
		// init
		init();

		// input
		cin >> V >> E;
		for (int i = 0; i < E; i++) { // 인접리스트로 그래프 저장
			cin >> a >> b;
			al[a].push_back(b);
			al[b].push_back(a);
		}

		// 1. 미방문인 노드부터 bfs 탐색 시작
		// 2. 탐색 결과 0이면 이분그래프를 못만드는 원인을 발견한 것임
		// 3. ans의 값을 0으로 셋팅한 후 탐색 종료
		int ans = 1;
		for (int i = 1; i <= V; i++) {
			if (visited[i] == 0) {
				if (bfs(i) == 0) {
					ans = 0;
					break;
				}
			}
		}

		if (ans == 1) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}