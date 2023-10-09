#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

int n, m;
vector<int> c_gp[502];
int vi[502];
int t_cnt;

struct t_no {
	int p_tv;
	int tv;
};

// 각 정점에서 그래프를 탐색한다.
// 이 때, 이전 노드를 방문한 경우를 제외하고 갈 수 있는곳이 방문한
// 노드라면 사이클이 존재한다고 볼 수 있다.
// 고로 해당 경우가 아니라면 트리라고 가정하고 문제를 푼다.

void t_count(int sv)
{
	queue<t_no> q;
	q.push({ sv,sv });
	bool is_t = true;

	while (!q.empty())
	{
		t_no now_v = q.front();
		q.pop();

		int to_tv;
		int go_cnt = 0;
		bool m_sv = false;
		for (int s = 0; s < c_gp[now_v.tv].size(); s++)
		{
			to_tv = c_gp[now_v.tv][s];

			if (to_tv != now_v.p_tv && vi[to_tv] != 0)
			{
				is_t = false;
				
			}
			if (vi[to_tv] != 0) continue;

			go_cnt += 1;
			vi[to_tv] = 1;

			q.push({ now_v.tv, to_tv });
		}
	}
	if (is_t)
	{
		t_cnt += 1;
	}
	return;
}

int main() {
	int tn = 1;
	// 테스트 케이스 
	while (true)
	{
		cin >> n >> m;

		if (n == 0 && m == 0) break;

		memset(c_gp, 0, sizeof(c_gp));
		memset(vi, 0, sizeof(vi));

		// 그래프 정보 입력받기
		t_cnt = 0;
		int cv, to_cv;
		for (int i = 0; i < m; i++)
		{
			cin >> cv >> to_cv;
			c_gp[cv].push_back(to_cv);
			c_gp[to_cv].push_back(cv);
		}

		// 모든 정점에서 트리가 존재하는 경우를 고려한다.
		for (int sv = 1; sv < n + 1; sv++)
		{
			if (vi[sv] == 0)
			{
				vi[sv] = 1;
				t_count(sv);
			}
		}

		// 정답 출력
		if (t_cnt == 0)
		{
			cout << "Case " << tn<< ": " << "No trees.\n";
		}
		else if (t_cnt == 1)
		{
			cout << "Case " << tn << ": " << "There is one tree.\n";

		}
		else if (t_cnt >= 2)
		{
			cout << "Case " << tn << ": " << "A forest of " << t_cnt << " trees.\n";

		}
		tn += 1;
	}
	return 0;
}