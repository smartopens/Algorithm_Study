#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n, m, k;
int towers[12][12];
int t_vi[12][12];

int a_vi[12][12];
int ap_vi[12][12];
int t_time[12][12];

struct at_no {
	int t_p;
	int r;
	int c;
	int rc_s;
	int a_t;

	bool operator < (at_no now) const {
		if (t_p > now.t_p)
		{
			return true;
		}
		if (t_p < now.t_p)
		{
			return false;
		}
		if (a_t > now.a_t)
		{
			return true;
		}
		if (a_t < now.a_t)
		{
			return false;
		}
		if (rc_s < now.rc_s)
		{
			return true;
		}
		if (rc_s > now.rc_s)
		{
			return false;
		}
		if (c < now.c)
		{
			return true;
		}
		if (c > now.c)
		{
			return false;
		}
		return false;
	}
};

struct tt_no {
	int t_p;
	int r;
	int c;
	int rc_s;
	int a_t;

	bool operator < (tt_no now) const {
		if (t_p < now.t_p)
		{
			return true;
		}
		if (t_p > now.t_p)
		{
			return false;
		}
		if (a_t < now.a_t)
		{
			return true;
		}
		if (a_t > now.a_t)
		{
			return false;
		}
		if (rc_s > now.rc_s)
		{
			return true;
		}
		if (rc_s < now.rc_s)
		{
			return false;
		}
		if (c > now.c)
		{
			return true;
		}
		if (c < now.c)
		{
			return false;
		}
		return false;
	}
};

struct a_no {
	int r;
	int c;
};
struct p_no {
	int r;
	int c;

	vector<a_no> a_p;
};

int dr[8] = { 0,1,0,-1,-1,1,1,-1 };
int dc[8] = { 1,0,-1,0,1,1,-1,-1 };

at_no at1;
tt_no tt1;

void p_attack()
{
	int ar = at1.r;
	int ac = at1.c;
	int er = tt1.r;
	int ec = tt1.c;

	queue<p_no> q;
	vector<a_no> at_p = {};
	q.push({ ar,ac,at_p });

	ap_vi[ar][ac] = 1;
	a_vi[ar][ac] = 1;
	int ap = towers[ar][ac] + n + m;
	int ap_h = ap / 2;

	towers[ar][ac] = ap;
	bool a_ok = false;

	int nr, nc;
	while (!q.empty())
	{
		p_no qv = q.front();
		q.pop();

		vector<a_no> now_a_p = qv.a_p;
		for (int i = 0; i < 4; i++)
		{
			nr = qv.r + dr[i];
			nc = qv.c + dc[i];

			if (0 > nr)
			{
				nr = n - 1;
			}
			if (n - 1 < nr)
			{
				nr = 0;
			}

			if (0 > nc)
			{
				nc = m - 1;
			}
			if (m - 1 < nc)
			{
				nc = 0;
			}

			if (ap_vi[nr][nc] != 0) continue;
			if (towers[nr][nc] == 0) continue;
			now_a_p.push_back({ nr,nc });

			ap_vi[nr][nc] = 1;
			
			if (nr == er && nc == ec)
			{
				towers[nr][nc] -= ap;
				if (towers[nr][nc] < 0) { towers[nr][nc] = 0; }
				now_a_p.pop_back();

				a_vi[er][ec] = 1;
				while (!now_a_p.empty())
				{
					a_no t_v = now_a_p.back();
					towers[t_v.r][t_v.c] -= ap_h;

					if (towers[t_v.r][t_v.c] < 0) { towers[t_v.r][t_v.c] = 0; }
					a_vi[t_v.r][t_v.c] = 1;
					now_a_p.pop_back();
				}
				a_ok = true;
				return;
			}
			q.push({ nr,nc,now_a_p });
			now_a_p.pop_back();
		}
	}

	towers[er][ec] -= ap;
	if (towers[er][ec] < 0) { towers[er][ec] = 0; }
	a_vi[er][ec] = 1;

	for (int i = 0; i < 8; i++)
	{
		nr = er + dr[i];
		nc = ec + dc[i];

		if (0 > nr)
		{
			nr = n - 1;
		}
		if (n - 1 < nr)
		{
			nr = 0;
		}

		if (0 > nc)
		{
			nc = m - 1;
		}
		if (m - 1 < nc)
		{
			nc = 0;
		}

		if (towers[nr][nc] == 0) continue;

		towers[nr][nc] -= ap_h;
		if (towers[nr][nc] < 0) { towers[nr][nc] = 0; }

		a_vi[nr][nc] = 1;
	}

	return;
}

int main()
{
	cin >> n >> m >> k;

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
		{
			cin >> towers[r][c];
			t_time[r][c] = 1;
		}
	}

	priority_queue<at_no> aq;
	priority_queue<tt_no> tq;
	for (int t = 0; t < k; t++)
	{
		aq = {};
		tq = {};

		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < m; c++)
			{
				if (towers[r][c] == 0) continue;
				aq.push({ towers[r][c],r,c,r + c, t_time[r][c]});
				tq.push({ towers[r][c],r,c,r + c, t_time[r][c]});
			}
		}

		if (!aq.empty())
		{
			at1 = aq.top();
		}
		else {
			at1 = { 0,0 };
		}
		if (!tq.empty())
		{
			tt1 = tq.top();
		}
		else {

			tt1 = { 0,0 };
		}

		memset(ap_vi, 0, sizeof(ap_vi));
		memset(a_vi, 0, sizeof(a_vi));

		p_attack();
		
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < m; c++)
			{
				if (towers[r][c] == 0) continue;
				if (a_vi[r][c] != 0) continue;

				towers[r][c] += 1;
			}
		}

		t_time[at1.r][at1.c] = 0;
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < m; c++)
			{
				t_time[r][c] += 1;
			}
		}
	}

	int max_p = 0;

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
		{
			if (towers[r][c] > max_p)
			{
				max_p = towers[r][c];
			}
		}
	}

	cout << max_p << endl;
	return 0;
}