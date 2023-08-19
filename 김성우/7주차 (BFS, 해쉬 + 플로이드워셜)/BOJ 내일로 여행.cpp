#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<algorithm>
using namespace std;

const int INF = 21e8;

int n, r, m, k;
unordered_map<string, int> city;
vector<string> will_visit;
double cost[110][110]; // 그냥 비용
double n_cost[110][110]; // 내일로 비용
double total_cost, total_n_cost;


// 모든 경로를 확인하기 위해서 플로이드 - 와샬을 사용해야 하는데
// 플로이드 와샬은 string type이 아닌 숫자 타입이 필요하므로
// string - int를 이어주는 map이 필요하다.
// 그러므로 unordered map을 차용한다.

void sol() {

	for (int mid = 0; mid < n; mid++) {
		for (int start = 0; start < n; start++) {
			for (int end = 0; end < n; end++) {
				if (cost[start][end] > cost[start][mid] + cost[mid][end]) {
					cost[start][end] = cost[start][mid] + cost[mid][end];
				}
				if (n_cost[start][end] > n_cost[start][mid] + n_cost[mid][end]) {
					n_cost[start][end] = n_cost[start][mid] + n_cost[mid][end];
				}
			}
		}
	}

	for (int i = 1; i < m; i++) {

		int start = city[will_visit[i - 1]];
		int end = city[will_visit[i]];
		total_cost += cost[start][end];
		total_n_cost += n_cost[start][end];
	}
	total_n_cost += r;
}

void input() {

	cin >> n >> r; // 도시, 가격
	for (int i = 0; i < n; i++) {
		string city_name;
		cin >> city_name;
		city[city_name] = i;
	}
	cin >> m; // 여행할 도시의 수
	for (int i = 0; i < m; i++) {
		string city_name;
		cin >> city_name;
		will_visit.push_back(city_name);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			cost[i][j] = INF;
			n_cost[i][j] = INF;
		}
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		string type, s, e;
		double fee;
		cin >> type >> s >> e >> fee;
		int start = city[s];
		int end = city[e];

		cost[start][end] = min(cost[start][end], fee);
		cost[end][start] = min(cost[end][start], fee);

		if ((type == "Mugunghwa") || (type == "ITX-Saemaeul") || (type == "ITX-Cheongchun")) {
			n_cost[start][end] = min(n_cost[start][end], (double)0);
			n_cost[end][start] = min(n_cost[end][start], (double)0);
		}

		else if ((type == "S-Train") || (type == "V-Train")) {
			n_cost[start][end] = min(n_cost[start][end], fee / 2);
			n_cost[end][start] = min(n_cost[end][start], fee / 2);
		}

		else {
			n_cost[start][end] = min(n_cost[start][end], fee);
			n_cost[end][start] = min(n_cost[end][start], fee);
		}
	}
}

int main() {

	input();

	sol();

	if (total_cost > total_n_cost) {
		cout << "Yes" << "\n";
	}
	else
		cout << "No" << "\n";

}