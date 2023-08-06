// 1865 웜홀
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 213456789;

int MAP[501][501]; // 각 정점 사이에 거리 (최소값)
int visited[501]; // 정점에 방문 여부
int N; // 정점의 수

// 벨만포드 알고리즘
// 음의 경로를 폼함한 그래프에서 경로 탐색하는 알고리즘
bool BellmanFord(int st) {
	// st 시작지점에서부터 시작!
	queue<pair<int, int>> q;
	q.push({ 0, st });
	visited[st] = 0;

	// N-1 번 돌면 모든 지점을 방문만 하는 것이다
	// N 번 돌면 (N-1)번째와 비교하여 음의 싸이클이 존재하는지를 판단한다
	for (int i = 1; i <= N; i++) {
		int sz = q.size(); // 이번에는 queue에 담겨있는 정점들만 고려한다
		for (int j = 0; j < sz; j++) {
			pair<int, int> curr = q.front();
			q.pop();

			for (int k = 1; k <= N; k++) {
				int amt = curr.first + MAP[curr.second][k]; // curr점에서 k점까지 도달하는데 걸리는 총 소요시간

				if (MAP[curr.second][k] == 0) continue; // 간선 연결 X라면 무시
				if (visited[k] <= amt) continue; // 이미 더 작은 경로를 찾은 k지점이라면 무시
				if (i == N) return true; // N번째 턴에 더 작은 경로를 찾았다면 음의 싸이클이 존재한다고 판단

				// k 지점에 방문 예정
				q.push({ amt, k });
				visited[k] = amt;
			}
		}
	}
	
	return false; // 여기까지 왔다는 것은 음의 싸이클을 못찾았다는 뜻
}

int main() {
	int tc;
	cin >> tc;
	
	for (int t = 1; t <= tc; t++) {
		// init
		memset(MAP, 0, sizeof(MAP));

		// input
		int M, W;
		int S, E, T;
		cin >> N >> M >> W;

		// 문제에서 간선은 중복이 가능하다고 나온다
		// 하지만 풀이를 위해서는 결국 각 경로에서 최소의 길이만 필요하다
		// 따라서 각 경로당 가장 작은 값의 거리만을 저장한다

		// 기본 간선 - 양방향
		for (int i = 0; i < M; i++) {
			cin >> S >> E >> T;
			if (MAP[S][E] == 0 || MAP[S][E] > T) MAP[S][E] = T;
			if (MAP[E][S] == 0 || MAP[E][S] > T) MAP[E][S] = T;
		}

		// 웜홀 - 단방향, 음수
		for (int i = 0; i < W; i++) {
			cin >> S >> E >> T;
			if (MAP[S][E] == 0 || MAP[S][E] > -T) MAP[S][E] = -T;
		}

		// 각 지점에 도달하는데 걸리는 거리는 INF로 초기화
		for (int i = 1; i <= N; i++) {
			visited[i] = INF;
		}

		// 어느 한 지점에서 시작하여 그 지점으로 돌아오는데 음수의 시간이 걸린다
		// 즉, 음의 싸이클이 존재하는가를 찾는 문제이다
		// 모든 지점에서부터 시작하는 탐색을 하면 시간초과가 발생한다
		// 따라서 1번 정점부터 벨만포드를 돌리고, 이후에는 미방문한 정점들만을 시작점으로 하여 벨만포드 돌리기
		// 단 한번이라도 음의 싸이클을 찾았다면 YES를 출력한다
		bool isPossible = false;
		for (int i = 1; i <= N; i++) {
			if (visited[i] == INF) {
				if (BellmanFord(i)) {
					isPossible = true; // 음의 싸이클 찾았다
					break;
				}
			}
		}
		
		// output
		if(isPossible) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}