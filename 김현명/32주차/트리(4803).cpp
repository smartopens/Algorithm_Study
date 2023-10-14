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

// �� �������� �׷����� Ž���Ѵ�.
// �� ��, ���� ��带 �湮�� ��츦 �����ϰ� �� �� �ִ°��� �湮��
// ����� ����Ŭ�� �����Ѵٰ� �� �� �ִ�.
// ��� �ش� ��찡 �ƴ϶�� Ʈ����� �����ϰ� ������ Ǭ��.

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
	// �׽�Ʈ ���̽� 
	while (true)
	{
		cin >> n >> m;

		if (n == 0 && m == 0) break;

		memset(c_gp, 0, sizeof(c_gp));
		memset(vi, 0, sizeof(vi));

		// �׷��� ���� �Է¹ޱ�
		t_cnt = 0;
		int cv, to_cv;
		for (int i = 0; i < m; i++)
		{
			cin >> cv >> to_cv;
			c_gp[cv].push_back(to_cv);
			c_gp[to_cv].push_back(cv);
		}

		// ��� �������� Ʈ���� �����ϴ� ��츦 ����Ѵ�.
		for (int sv = 1; sv < n + 1; sv++)
		{
			if (vi[sv] == 0)
			{
				vi[sv] = 1;
				t_count(sv);
			}
		}

		// ���� ���
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