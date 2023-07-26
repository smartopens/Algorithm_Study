// 11657 타임머신
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const long long INF = 1e10; // INF 값을 생각보다 크게 잡아야함,,

queue<pair<int, int>> q; // { 지점, 경로 }
vector<pair<int, int>> al[501]; // { 도착지점, 경로 }
long long visited[501]; // 초기에 INF값이 들어가므로 long long으로 잡기
int N, M; // N: 도시의 수, M: 버스 노선의 수

int main() {
	int s, e, p; // 버스 노선의 정보 (s:시작점, e:도착점, p:소요시간)

	// input
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		cin >> s >> e >> p;
		al[s].push_back({ e, p }); // s에서 출발하여 e에 도착하는데 p시간 소요
	}

	// init - 각 지점에 도달하는데 소요되는 시간을 최대값으로 초기화
	for (int i = 1; i <= N; i++) {
		visited[i] = INF;
	}

	// 정점이 N개인 그래프에서 1번에서 다른 지점으로 도달하려면
	// 최악의 경우 (N-1)개의 간선을 지나쳐야 한다
	// 그래서 N-1번을 탐색한다
	// 시작점에서부터 시작하되
	// 각 턴마다 queue에 들어가있는 점들에서부터 간선을 이동하고
	// 좀 더 최소 경로를 찾는다면 갱신한다
	// 여기서 문제는 음수값이 포함된 싸이클이다.
	// 특히, 싸이클을 돌 때마다 경로가 더 작아진다면 무한대로 작아질 수가 있다.
	// 이러한 경우 무한히 오래 전으로 되돌아가기 때문에 경우를 잡아줘야 한다.
	// 그 방법은 isCycled 변수로 음수 싸이클의 여부 판별해주기
	// 기존에 (N-1)번 돌던 루프를 N번 돌게한다.
	// N번 루프에서 더 최소의 경로를 찾았다면 그것은 무한히 오래 전으로 돌아가는 케이스이다.
	// 따라서 이런 경우 변수를 true로 갱신해주면 된다.

	bool isCycled = false; // 무한히 작아지는 싸이클의 존재 여부
	visited[1] = 0; // 1번 지점에서 시작
	q.push({ 1, 0 });
	for (int i = 1; i <= N; i++) {
		// i번째 턴에서는 현재 기준 queue에 있는 모든 지점에서부터 간선을 이동한다.
		int sz = q.size();
		for (int j = 0; j < sz; j++) {
			pair<int, int> curr = q.front();
			q.pop();

			int tsz = al[curr.first].size(); // curr.first와 연결된 간선 탐색
			for (int k = 0; k < tsz; k++) {
				pair<int, int> nxt = al[curr.first][k];
				
				if (visited[nxt.first] <= visited[curr.first] + nxt.second) continue; // 이미 더 작은 경로를 저장하고 있다면 무시
				if (i == N) isCycled = true; // N번째 루프인데 더 작은 경로를 발견했다면 무한히 작아지는 케이스이므로 변수 갱신

				visited[nxt.first] = visited[curr.first] + nxt.second; // 다음에 탐색 예정
				q.push({ nxt.first, visited[nxt.first] });
			}
		}
	}

	if (isCycled) { // 무한히 작아지는 싸이클이 존재한다면 -1 출력
		cout << -1 << "\n";
	}
	else {
		for (int i = 2; i <= N; i++) {
			if (visited[i] == INF) cout << "-1\n"; // i번 지점에 한 번에 도달하지 못했다면 -1 출력
			else cout << visited[i] << "\n";
		}
	}

	return 0;
}