// 14938 서강그라운드
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 213456789;

vector<pair<int, int>> al[101]; // 연결 지점 인접리스트
int items[101]; // 각 지점에 있는 아이템의 수
int n, m, r; // n: 지점의 수, m: 도달 가능한 거리, r: 간선의 수, 

// spot 지점에서 시작하여 얻을 수 있는 아이템의 수 구하기
int playGround(int spot) {
	int sum = 0; // 구할 수 있는 아이템의 수
	int visited[101]; // 각 지점까지의 거리
	for (int i = 1; i <= n; i++) visited[i] = INF;

	queue<int> q;
	q.push(spot); // spot에서 시작
	visited[spot] = 0;
	sum += items[spot];
	
	while (!q.empty()) {
		int now = q.front();
		q.pop();

		// now 지점과 연결된 지점들을 탐색
		for (int i = 0; i < al[now].size(); i++) {
			int nxt = al[now][i].first;
			int dist = visited[now] + al[now][i].second;

			if (dist > m) continue; // m보다 먼 거리는 도달 불가
			if (dist >= visited[nxt]) continue; // 이미 최적의 거리를 찾았다면 무시

			if (visited[nxt] == INF) sum += items[nxt]; // 최초 도달 시 아이템의 수 추가
			q.push(nxt); // nxt 지점 탐색 예정
			visited[nxt] = dist;
		}
	}

	return sum; // spot 지점에서 시작하여 얻을 수 있는 아이템의 수를 반환
}

int main() {
	// input
	int a, b, c;

	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++) cin >> items[i];
	for (int i = 0; i < r; i++) {
		cin >> a >> b >> c;
		al[a].push_back({ b, c });
		al[b].push_back({ a, c });
	}

	// solve
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int ret = playGround(i); // 각 지점에서 게임시작을 시뮬레이션 진행
		if (ret > ans) ans = ret; // 최대값 갱신
	}

	// output
	cout << ans << "\n";

	return 0;
}