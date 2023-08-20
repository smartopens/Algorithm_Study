#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
int k, s;
int h_gp[402][402];
int vi[402];

int main()
{
	cin >> n >> k;
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	
	// 정방향: 1로 저장
	// 역방향: -1로 저장
	int in_v, to_in_v;
	for (int i = 0; i < k; i++)
	{
		cin >> in_v >> to_in_v;
		h_gp[in_v][to_in_v] = 1;
		h_gp[to_in_v][in_v] = -1;
	}

	// 플로이드 워셜 알고리즘
	// 모든 정점 사이의 관계를 본다.
	// 선-후의 관계면 1, 후-선의 관계면 -1로 저장되게 했다.
	for (int m = 1; m < n + 1; m++)
	{
		for (int v = 1; v < n + 1; v++)
		{
			for (int ev = 1; ev < n + 1; ev++)
			{
				if (h_gp[v][m] == 1 && h_gp[m][ev] == 1)
				{
					h_gp[v][ev] = 1;
				}
				else if (h_gp[v][m] == -1 && h_gp[m][ev] == -1)
				{
					h_gp[v][ev] = -1;
				}
			}
		}
	}

	// 선-후의 관계면 1 출력
	// 후-선의 관계면 -1 출력
	// 모른다면 0을 출력한다.
	cin >> s;
	int v, to_v;
	for (int i = 0; i < s; i++)
	{
		cin >> v >> to_v;

		if (h_gp[v][to_v] == 1)
		{
			cout << -1 << "\n";
		}
		else if (h_gp[v][to_v] == -1)
		{
			cout << 1 << "\n";
		}
		else {
			cout << 0 << "\n";
		}
	}
	return 0;
}