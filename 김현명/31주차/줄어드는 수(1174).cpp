#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n;
typedef long long ll;

vector<ll> l_nums;
void dfs(int a, ll now_sv, ll p_v)
{
	if (a > 9)
	{
		return;
	}

	ll to_sv;
	for (int v = 0; v < 10; v++)
	{
		if (a == 0 && v == 0) continue;
		if (p_v > v)
		{
			to_sv = 10 * now_sv + v;
			l_nums.push_back(to_sv);
			dfs(a + 1, to_sv, v);
		}
	}
}

int main()
{

	cin >> n;
	l_nums.push_back(0);
	l_nums.push_back(0);

	dfs(0, 0, 10);
	sort(l_nums.begin(), l_nums.end());

	//ex)  n=4 : 0,0,1,2,3,4
	if (n > l_nums.size() - 1)
	{
		cout << -1 << endl;
	}
	else
	{
		cout << l_nums[n] << endl;;
	}
	return 0;
}