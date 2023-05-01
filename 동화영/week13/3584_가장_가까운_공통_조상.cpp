/* 가장 가까운 공통 조상 */
// LCA 문제
// 정석적인 풀이는
// 1. ta와 tb의 레벨을 먼저 맞춘다
// 2. 하나씩 위로 올라오면서 공통 조상을 찾는다.
#include <iostream>
#include <cstring>
using namespace std;

int visited[10001];
int parent[10001];
int N;

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// init
		memset(visited, 0, sizeof(visited));
		memset(parent, 0, sizeof(parent));
		int ans = 0;

		// input
		cin >> N;
		int p, c;
		for (int i = 0; i < N - 1; i++) { // 각 노드의 부모 노드 저장하기
			cin >> p >> c;
			parent[c] = p;
		}

		int ta, tb; // ta와 tb의 가장 가까운 공통 조상 찾는게 문제이다
		cin >> ta >> tb;

		// root의 parent는 0이다
		int ca = ta, cb = tb; // ca, cb : ta와 tb 부터 위로 올라가기
		while (visited[ca] == 0 && visited[cb] == 0) { // 두 노드 모두 미방문했다면 다음 레벨 탐색
			if (ca == cb) break; // 동시에 동일한 노드에 도착했다면 탐색 종료

			// ca와 cb 방문 표기
			if(ca != 0) visited[ca] = 1;
			if(cb != 0) visited[cb] = 1;

			// 각 노드의 부모노드로 올라가기
			ca = parent[ca];
			cb = parent[cb];
		}
		
		// 답 구하기
		if (ca == cb) ans = ca; // 동일한 노드에서 종료한 경우
		else if (ca != 0 && visited[ca] != 0) ans = ca; // ta가 ans와 더 가까운 경우
		else if (cb != 0 && visited[cb] != 0) ans = cb; // tb가 ans와 더 가까운 경우

		// output
		cout << ans << "\n";
	}

	return 0;
}