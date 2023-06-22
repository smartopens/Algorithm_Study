/* 트리의 지름 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	int num; // 노드 번호
	int cost; // num 노드번호 
};

int used[10001]; // leaf 노드를 찾기 위한 배열
vector<Node> el[10001]; // 각 노드별 인접리스트
vector<int> ch; // leaf 노드
int n; // 노드의 수

// 각 leaf 노드에서부터 다른 leef 노드까지의 거리 구하기
int bfs(int ind) {
	int st = ch[ind]; // 이번에 탐색 시작할 노드 번호

	// bfs 탐색 준비
	queue<int> q;
	int visited[10001] = { 0, };

	q.push(st);
	visited[st] = 1;

	// bfs 탐색
	while (!q.empty()) {
		int now = q.front();
		q.pop();

		int sz = el[now].size();
		for (int i = 0; i < sz; i++) {
			int nxt = el[now][i].num;
			int cst = el[now][i].cost;

			if (visited[nxt] > 0) continue;
			q.push(nxt);
			visited[nxt] = visited[now] + cst; // 거리값은 cost 만큼 더해주기
		}
	}

	// leaf 노드만 도착지점으로 판단하여 최대값 구하기
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (visited[i] > ret) ret = visited[i];
	}

	// 시작점을 1로 뒀기 때문에 -1 해주기
	return ret - 1;
}

int main() {
	// input
	int a, b, c;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b >> c;
		// 노드 a와 b 사이의 cost값 c를 저장 (인접리스트)
		el[a].push_back({ b, c });
		el[b].push_back({ a, c });
		used[a] = 1; // 노드 a는 자식 노드가 있다를 표기
	}

	// leaf 노드들 구하기
	for (int i = 1; i < 10001; i++) {
		if (el[i].size() > 0 && used[i] == 0) ch.push_back(i);
	}

	// leaf 노드들을 순회하며
	// 각 노드에서 다른 leaf 노드들까지의 거리 중 최대값 구하기
	int maxi = 0;
	for (int i = 0; i < ch.size(); i++) {
		int cost = bfs(i);
		if (cost > maxi) maxi = cost; // 값 갱신
	}

	// output
	cout << maxi;

	return 0;
}