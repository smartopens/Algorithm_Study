#include <iostream>

using namespace std;

// bfs 시간복잡도
// n*m : 4*10, per di:5

int n, m;
int new_p[1002][1002];
int costs[1002][1002];

int dr[3] = { 0,1,0 };
int dc[3] = { 1,0,-1 };
int max_r;

int r_search(int now_r, int now_c)
{
	if (now_r == n - 1 && now_c == m - 1)
	{
		return 0;
	}

	if (costs[now_r][now_c] != -3e8)
	{
		return costs[now_r][now_c];
	}

	costs[now_r][now_c] = -2e8;
	
	int to_r = 0;
	int to_c = 0;
	int max_c = -2e8;
	for (int i = 0; i < 3; i++)
	{
		to_r = now_r + dr[i];
		to_c = now_c + dc[i];
		if (0 > to_r || n-1 < to_r || 0 > to_c || m-1 < to_c) continue;

		max_c = max(costs[now_r][now_c], r_search(to_r, to_c) + new_p[to_r][to_c]);
	}

	return costs[now_r][now_c] = max_c;
}

int main()
{
	cin >> n >> m;
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
		{
			cin >> new_p[r][c];
		}
	}

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
		{
			costs[r][c] = -3e8;
		}
	}

	max_r = 0;
	max_r += new_p[0][0];
	max_r += r_search(0,0);

	cout << max_r << endl;
	return 0;
}