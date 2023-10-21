#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>

using namespace std;

// 2-模备 版快

// 1:1 模备
// 促弗 模备 d

int n;
int f_gp[52][52];
unordered_map<string,int> vi;

int dists[52][52];
int max_fn;
int fn;

int main()
{
	cin >> n;
	string f_rel;
	for (int r = 0; r < n; r++)
	{
		cin >> f_rel;
		for (int c = 0; c < n; c++)
		{

			f_gp[r][c] = f_rel[c];

			if (r == c) continue;
			
			if(f_rel[c] == 'Y')
			{
				dists[r][c] = 1;
				continue;
			}
			dists[r][c] = 21e8;
		}
	}

	for (int k = 0; k < n; k++)
	{
		for (int sv = 0; sv < n; sv++)
		{
			for (int ev = 0; ev < n; ev++)
			{
				if (dists[sv][k] != 21e8 && dists[k][ev] != 21e8)
				{
					dists[sv][ev] = min(dists[sv][ev], dists[sv][k] + dists[k][ev]);
				}
			}
		}
	}

	int now_fn = 0;
	for (int v = 0; v < n; v++)
	{
		now_fn = 0;
		for (int to_v = 0; to_v < n; to_v++)
		{
			if (v == to_v) continue;
			if (dists[v][to_v] <= 2)
			{
				now_fn += 1;
			}
		}
		if (now_fn > max_fn)
		{
			max_fn = now_fn;
		}
	}
	
	cout << max_fn << endl;
	return 0;
}