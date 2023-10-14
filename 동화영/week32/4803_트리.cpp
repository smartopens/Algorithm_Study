// 4803 트리
#include <iostream>
#include <vector>
using namespace std;

vector<int> al[501]; //간선의 정보
int visited[501]; //정점의 방문 여부

//before정점을 타고 들어온 ind정점에서 탐색 시작
bool dfs(int ind, int before) {
	visited[ind] = 1; //방문 표기

	for (int i = 0; i < al[ind].size(); i++) { //ind와 연결된 간선들을 탐색
		int nxt = al[ind][i];
		if (nxt == before) continue; //이미 before을 통해서 ind에 들어왔으므로 무시

		if (visited[nxt] != 0) return false; //기방문 지점에 도달했다면 사이클 존재 - 트리가 아님
		if (!dfs(nxt, ind)) return false; //nxt지점부터 dfs 탐색
	}

	return true; //정상 종료 및 트리 발견
}

int main() {
	int tc = 0;
	int n, m;
	while (1) {
		//init
		tc++;
		for (int i = 0; i < 501; i++) {
			al[i].clear();
			visited[i] = 0;
		}

		//input
		cin >> n >> m;

		//종료조건
		if (n == 0 && m == 0) break;

		int a, b;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			al[a].push_back(b); //간선 정보
			al[b].push_back(a);
		}

		int cnt = 0; //트리의 수
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0) { //미방문 정점만을 탐색
				if (dfs(i, 0)) cnt++; //dfs 탐색이 true인 경우에만 트리로 인정(false이면 사이클 존재하여 트리가 아님)
			}
		}

		//output
		if (cnt == 0) cout << "Case " << tc << ": No trees.\n";
		else if (cnt == 1) cout << "Case " << tc << ": There is one tree.\n";
		else cout << "Case " << tc << ": A forest of " << cnt << " trees.\n";
	}

	return 0;
}