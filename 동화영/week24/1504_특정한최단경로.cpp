// 1504 특정한 최단 경로
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 213456789;

vector<pair<int, int>> al[801]; // 각 정점에 연결된 간선 리스트
int cRoute; // v1과 v2 사이의 거리
int N, E; // N: 정점의 개수, E: 간선의 개수
int v1, v2; // 필수 통과 정점

pair<int, int> minDist(int st) {
	// st 지점부터 탐색 시작할 준비
	int visited[801];
	for (int i = 1; i <= N; i++) visited[i] = INF;
	queue<int> q;
	q.push(st);
	visited[st] = 0;

	while (!q.empty()) {
		int curr = q.front();
		q.pop();

		int sz = al[curr].size(); // curr와 연결된 간선들 탐색
		for (int i = 0; i < sz; i++) {
			int nxt = al[curr][i].first; // 연결된 정점인 nxt
			int amt = visited[curr] + al[curr][i].second; // 현재 curr까지의 거리 + curr와 nxt 사이 간선의 거리

			if (visited[nxt] <= amt) continue; // 이미 찾은 경로보다 최적이 아니면 무시

			q.push(nxt); // 다음에 탐색할 예정
			visited[nxt] = amt;
		}
	}

	// 간선이 모두 양방향이라 v1->v2와 v2->v1은 동일
	// 따라서 한 번만 저장하면 된다
	if (st == v1) cRoute = visited[v2]; // v1과 v2 사이의 거리

	return { visited[1], visited[N] }; // 1번, N번 정점까지의 거리를 반환
}

int main() {
	int a, b, c;

	// input
	cin >> N >> E;
	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		al[a].push_back({ b, c }); // 양방향 처리
		al[b].push_back({ a, c });
	}
	cin >> v1 >> v2; // 필수 코스인 2개의 지점

	// 1 -> v1 -> v2 -> N (1번 경로)
	// 1 -> v2 -> v1 -> N (2번 경로)
	// 위의 2가지 경로를 구하여 더 작은 값을 출력하면 된다
	// 간선이 모두 양방향이므로 각 정점 사이의 거리만을 구하면 된다
	// 즉, v1에서부터 1과 N 까지의 거리
	//     v2에서부터 1과 N 까지의 거리
	//     v1과 v2의 거리
	pair<int, int> dist1 = minDist(v1); // v1에서 1과 N 까지의 거리
	pair<int, int> dist2 = minDist(v2); // v2에서 1과 N 까지의 거리

	// cRoute 는 v1과 v2 사이의 거리
	int route1 = dist1.first + cRoute + dist2.second; // 1번 경로
	int route2 = dist1.second + cRoute + dist2.first; // 2번 경로

	// 더 작은 값을 출력 output
	if (route1 >= INF && route2 >= INF) cout << "-1\n"; // 2가지 모두 도달하지 못한 경우
	else if (route1 < route2) cout << route1 << "\n";
	else cout << route2 << "\n";

	return 0;
}