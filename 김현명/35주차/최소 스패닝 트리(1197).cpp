#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;

vector<pair<int, int>>gp[10002];
vector<pair<int, pair<int, int>>> edges;

int parent[10002];

int Find(int a)
{
	if (a == parent[a])
	{
		return a;
	}

	return parent[a] = Find(parent[a]);
}

void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb)
	{
		return;
	}

	parent[pb] = pa;
}

int min_co;

int main()
{
	int a, b, co;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> co;
		gp[a].push_back({ make_pair(co,b) });
		gp[b].push_back({ make_pair(co,a) });
		edges.push_back(make_pair(co, make_pair(a, b)));
	}

	sort(edges.begin(), edges.end());

	for (int i = 1; i < n + 1; i++)
	{
		parent[i] = i;
	}

	int v, to_v;
	for (int i = 0; i < m; i++)
	{
		v = edges[i].second.first;
		to_v = edges[i].second.second;
		co = edges[i].first;

		if (Find(v) != Find(to_v))
		{
			Union(v, to_v);
			min_co += co;
		}
	}

	cout << min_co << endl;
	return 0;
}