#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct info {
	int part_type;
	int quantity;
};

vector<info> v[110];
int list[110][110];
int degree[110];
int check[110];
int n, m, x, y, k;

void sol() {

	queue<int> q;

	for (int i = 1; i <= n; i++)
	{
		if (!degree[i]) {
			check[i] = 1;
			q.push(i);
			list[i][i] = 1;
		}
	}

	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		for (int i = 0; i < v[now].size(); i++) {
			int next = v[now][i].part_type;
			int cost = v[now][i].quantity;
			for (int j = 1; j <= n; j++) list[next][j] += list[now][j] * cost;
			degree[next]--;

			if (degree[next] == 0) q.push(next);
		}
	}


}

void input() {

	cin >> n; // 1 ~ n-1 : 기본, 중간 부품, n : 완성품
	cin >> m;

	for (int i = 0; i < m; i++) {
		cin >> x >> y >> k; // x를 만드는데 y 가 k 개 필요하다
		v[y].push_back({ x, k });
		degree[x] += 1;
	}

}

int main() {

	input();

	sol();

	// output
	for (int i = 1; i <= n; i++) {
		if (check[i]) {
			cout << i << " " << list[n][i] << "\n";
		}
	}

	int de = 1;

}



