#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct NODE {
	int num;
	int dist;

	// 거리 오름차순
	bool operator < (NODE nxt) const {
		if (dist > nxt.dist) return true;
		if (dist < nxt.dist) return false;
		return false;
	}
};

vector<NODE> al[1001]; // 인접 리스트
vector<NODE> copied[1001]; // 단방향 간선의 방향을 돌려서 dijkstra를 한 번 더 동작하기 위해 간선 정보 저장용
int visited[2][1001]; // 0: 주어진 간선 방향 기준, 1: 반대로 돌린 간선 기준
int N, M, X; // N: 노드의 개수, M: 간선의 개수, X: 모임 장소의 노드 번호

// 1. X번 노드에서부터 다른 노드들까지의 최단 거리를 구한다.
// 2. 모든 단방향 간선을 반대방향으로 돌린다.
// 3. 이 상태에서 1번을 한 번 더 동작한다.
// 4. 1번과 3번의 결과 visited의 합으로 왕복 거리를 구한다.
void dijkstra(int st, int flag) {
	priority_queue<NODE> q;
	q.push({ st, 0 });

	while (!q.empty()) {
		NODE now = q.top();
		q.pop();

		// now번 노드까지의 도달 거리가 이미 최소라면 저장과 탐색은 X
		if (visited[flag][now.num] <= now.dist) continue;
		visited[flag][now.num] = now.dist;

		for (int i = 0; i < al[now.num].size(); i++) {
			NODE nxt = al[now.num][i];
			int ndist = now.dist + nxt.dist; // 현재 now까지의 거리 + (now~nxt)사이의 거리

			if (ndist >= visited[flag][nxt.num]) continue; // 이미 더 작은 값이 저장되어 있다면 탐색 X
			q.push({ nxt.num, ndist });
		}
	}
}

int main() {
	cin >> N >> M >> X;

	// init
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 2; j++) {
			visited[j][i] = 21e8;
		}
	}

	// input
	int a, b, c;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		al[a].push_back({ b, c });
		copied[a].push_back({ b,c });
	}

	// 1. 주어진 간선 기준 - X번 노드로부터 각 노드까지의 최단 거리 구하기
	dijkstra(X, 0);

	// 2. 간선의 방향 바꾸기
	for (int i = 1; i <= N; i++) {
		al[i].clear();
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < copied[i].size(); j++) {
			NODE tmp = copied[i][j];
			al[tmp.num].push_back({ i, tmp.dist });
		}
	}

	// 3. 반대로 변경한 간선 기준 - X번 노드로부터 각 노드까지의 최단 거리 구하기
	dijkstra(X, 1);

	// 4. 1번과 3번의 결과로 왕복 최단 거리 중 최대값 구하기
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		if (visited[0][i] + visited[1][i] > ans) ans = visited[0][i] + visited[1][i];
	}

	// output
	cout << ans << "\n";

	return 0;
}