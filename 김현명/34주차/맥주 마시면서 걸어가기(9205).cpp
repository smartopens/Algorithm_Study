#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

// 3sqrt2*10^5 *(3*10^5)
// 출발지 sr, sc
// 도착지 er, ec
// 편의점 store[102]

int t;
int n;
int sr, sc;
int er, ec;

struct node
{
	int pr;
	int pc;
};

node stores[102];
int vi[102];
bool can_go;

void go_concert()
{
	queue<node> q;
	q.push({ sr, sc });

	while (!q.empty())
	{
		node now = q.front();
		q.pop();

		int now_r = now.pr;
		int now_c = now.pc;
		if (abs(now_r - er) + abs(now_c - ec) <= 1000)
		{
			can_go = true;
			return;
		}

		int to_r, to_c;
		for (int i = 0; i < n; i++)
		{
			to_r = stores[i].pr;
			to_c = stores[i].pc;

			if (abs(to_r - now_r) + abs(to_c - now_c) <= 1000)
			{
				if (vi[i] != 0) continue;

				vi[i] = 1;
				q.push({ to_r,to_c });
			}
		}

	}
	return;
}

int main()
{
	cin >> t;
	
	for (int tc = 0; tc < t; tc++)
	{
		cin >> n;
		cin >> sr >> sc;

		can_go = false;
		memset(vi, 0, sizeof(vi));

		int pr, pc;
		for (int sv = 0; sv < n; sv++)
		{
			cin >> pr >> pc;
			stores[sv] = { pr,pc };
		}

		cin >> er >> ec;

		go_concert();

		if (can_go == false)
		{
			cout << "sad" << endl;
		}
		else
		{
			cout << "happy" << endl;
		}

	}
	return 0;
}
