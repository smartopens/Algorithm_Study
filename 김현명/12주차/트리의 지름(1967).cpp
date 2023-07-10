#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
int max_w;
int t_v;

struct node {
	int to;
	int weight;
};

vector<node> graph[10002];
int vi[10002];

// 특정 노드에서 가장 먼 지점을 찾는다.
// 트리의 그래프적 구조를 고려한다.
// 즉, 여러 경로를 볼 필요가 없다.
void dfs(int v, int w)
{
	for (int i = 0; i < graph[v].size(); i++)
	{
		node now = graph[v][i];
		if (vi[now.to] == 1) continue;

		if (w + now.weight > max_w)
		{
			max_w = w + now.weight;
			t_v = now.to;
		}

		vi[now.to] = 1;
		dfs(now.to, w + now.weight);

	}

	return;
}

int main() {
	cin >> n;

	// 트리 정보를 연결 그래프로 입력받기
	// 양방향이다.
	for (int i = 0; i < n - 1; i++)
	{
		int now, to, w;

		cin >> now >> to >> w;
		now -= 1;
		to -= 1;
		graph[now].push_back({ to, w });
		graph[to].push_back({ now, w });
	}

	// 트리의 성질을 이용한다.
	// 특정 노드에서 가장 먼거리에 있는 노드를 찾는다.
	// 해당 노드는 트리의 가장 바깥 지점이다.
	// 해당 지점으로부터 가장 먼거리를 찾는다.
	vi[0] = 1;
	dfs(0, 0);
	memset(vi, 0, sizeof(vi));

	// 처음 돌린 지점으로부터 가장 먼 노드 찾기
	max_w = 0;
	vi[t_v] = 1;
	dfs(t_v, 0);

	cout << max_w << endl;
	return 0;
}