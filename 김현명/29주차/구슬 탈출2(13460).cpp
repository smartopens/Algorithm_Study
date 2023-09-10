#include <iostream>
#include <string>
#include <queue>

using namespace std;

int n, m;
char doll_bd[12][12];


int r_r, r_c;
int b_r, b_c;
int doll_xy[4];

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };
int m_cnt = 21e8;
bool g_com = false;


struct d_no {
	int r_r;
	int r_c;
	int b_r;
	int b_c;
	int cnt;
};

void d_move(int d_o, int di)
{
	if (d_o == 1)
	{
		while (true)
		{
			r_r += dr[di];
			r_c += dc[di];

			if (doll_bd[r_r][r_c] == 'O')
			{
				return;
			}

			if (doll_bd[r_r][r_c] != '.')
			{
				r_r -= dr[di];
				r_c -= dc[di];
				return;
			}
		}
	}
	else {
		while (true)
		{
			b_r += dr[di];
			b_c += dc[di];

			if (doll_bd[b_r][b_c] == 'O')
			{
				return;
			}

			if (doll_bd[b_r][b_c] != '.')
			{
				b_r -= dr[di];
				b_c -= dc[di];
				return;
			}
		}

	}
}

void bfs()
{
	queue<d_no> q;
	q.push({ r_r,r_c, b_r, b_c,0 });

	while (!q.empty())
	{
		d_no dv = q.front();
		q.pop();

		r_r = dv.r_r;
		r_c = dv.r_c;
		b_r = dv.b_r;
		b_c = dv.b_c;

		bool d_o = false;
		for (int di = 0; di < 4; di++)
		{

			r_r = dv.r_r;
			r_c = dv.r_c;
			b_r = dv.b_r;
			b_c = dv.b_c;

			if (dv.cnt >= 10)
			{
				continue;
			}

			// 빨강구슬 선: t, 파랑구슬 선:f
			if (di == 0)
			{
				if (r_r < b_r) { d_o = true; }
				else { d_o = false; }
			}
			else if (di == 1) {
				if (r_c > b_c) { d_o = true; }
				else { d_o = false; }
			}
			else if (di == 2) {
				if (r_r > b_r) { d_o = true; }
				else { d_o = false; }
			}
			else if (di == 3) {
				if (r_c < b_c) { d_o = true; }
				else { d_o = false; }
			}

			d_move(1, di);
			d_move(0, di);

			if (doll_bd[b_r][b_c] == 'O')
			{
				continue;
			}
			if (doll_bd[r_r][r_c] == 'O')
			{
				m_cnt = dv.cnt + 1;
				return;
			}

			if (r_r == b_r && r_c == b_c)
			{
				if (d_o == true){
					b_r -= dr[di];
					b_c -= dc[di];
				}

				else if (d_o == false) {
					r_r -= dr[di];
					r_c -= dc[di];
				}
			}

			q.push({ r_r,r_c,b_r,b_c,dv.cnt + 1 });
		}
	}
	m_cnt = -1;
	return;
}

void dfs(int mn)
{
	if (mn > 10)
	{
		return ;
	}

	int or_r = r_r;
	int or_c = r_c;
	int ob_r = b_r;
	int ob_c = b_c;

	bool d_o = false;

	/*cout << mn << endl;
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
		{
			cout << doll_bd[r][c] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	for (int di = 0; di < 4; di++)
	{
		r_r = or_r;
		r_c = or_c;
		b_r = ob_r;
		b_c = ob_c;

		// 빨강구슬 선: t, 파랑구슬 선:f
		if (di == 0)
		{
			if (r_r < b_r){ d_o = true; }
			else { d_o = false; }
		}
		else if (di == 1) {
			if (r_c > b_c) {d_o = true;}
			else {d_o = false;}
		}
		else if (di == 2) {
			if (r_r > b_r) { d_o = true; }
			else { d_o = false; }
		}
		else if (di == 3) {
			if (r_c < b_c) { d_o = true; }
			else { d_o = false; }
		}

		// blue
		if (d_o == false)
		{
			d_move(0,di);

			if (doll_bd[b_r][b_c] == 'O')
			{
				continue;
			}
			else {
				if (!(b_r == ob_r && b_c == ob_c))
				{
					doll_bd[b_r][b_c] = 'B';
					doll_bd[ob_r][ob_c] = '.';
				}
			}

			d_move(1, di);
			if (doll_bd[r_r][r_c] == 'O')
			{
				if (mn < m_cnt)
				{
					m_cnt = mn;
					g_com = true;
					/*cout << mn << endl;
					for (int r = 0; r < n; r++)
					{
						for (int c = 0; c < m; c++)
						{
							cout << doll_bd[r][c] << " ";
						}
						cout << endl;
					}
					cout << endl;*/
				}

				if (!(b_r == ob_r && b_c == ob_c))
				{
					doll_bd[b_r][b_c] = '.';
					doll_bd[ob_r][ob_c] = 'B';
				}
				if (!(r_r == or_r && r_c == or_c))
				{
					doll_bd[r_r][r_c] = '.';
					doll_bd[or_r][or_c] = 'R';
				}
				continue;
			}
			else {
				if (!(r_r == or_r && r_c == or_c))
				{
					doll_bd[r_r][r_c] = 'R';
					doll_bd[or_r][or_c] = '.';
				}
			}
		}
		// red
		else if (d_o == true)
		{
			d_move(1,di);
			if (doll_bd[r_r][r_c] != 'O')
			{
				if (!(r_r == or_r && r_c == or_c))
				{
					doll_bd[r_r][r_c] = 'R';
					doll_bd[or_r][or_c] = '.';
				}
			}

			d_move(0, di);
			// 파란구슬 도착
			if (doll_bd[b_r][b_c] == 'O')
			{
				if (!(r_r == or_r && r_c == or_c))
				{
					doll_bd[r_r][r_c] = '.';
					doll_bd[or_r][or_c] = 'R';
				}

				if (!(b_r == ob_r && b_c == ob_c))
				{
					doll_bd[b_r][b_c] = '.';
					doll_bd[ob_r][ob_c] = 'B';
				}
				if (!(r_r == or_r && r_c == or_c))
				{
					doll_bd[r_r][r_c] = '.';
					doll_bd[or_r][or_c] = 'R';
				}

				continue;
			}

			// 빨간구슬 도착
			if (doll_bd[r_r][r_c] == 'O')
			{
				if (mn < m_cnt)
				{
					m_cnt = mn;
					g_com = true;
				}
				/*cout << mn << endl;
				for (int r = 0; r < n; r++)
				{
					for (int c = 0; c < m; c++)
					{
						cout << doll_bd[r][c] << " ";
					}
					cout << endl;
				}
				cout << endl;*/


				if (!(b_r == ob_r && b_c == ob_c))
				{
					doll_bd[b_r][b_c] = '.';
					doll_bd[ob_r][ob_c] = 'B';
				}
				if (!(r_r == or_r && r_c == or_c))
				{
					doll_bd[r_r][r_c] = '.';
					doll_bd[or_r][or_c] = 'R';
				}
				continue;
			}

			// 파란구슬 기록
			if (!(b_r == ob_r && b_c == ob_c))
			{
				doll_bd[b_r][b_c] = 'B';
				doll_bd[ob_r][ob_c] = '.';
			}
		}
		/*cout << mn << " " << di << " " << endl;
			for (int r = 0; r < n; r++)
			{
				for (int c = 0; c < m; c++)
				{
					cout << doll_bd[r][c] << " ";
				}
				cout << endl;
			}
			cout << endl;*/

		dfs(mn + 1);
		if (!(b_r == ob_r && b_c == ob_c))
		{
			doll_bd[b_r][b_c] = '.';
			doll_bd[ob_r][ob_c] = 'B';
		}
		if (!(r_r == or_r && r_c == or_c))
		{
			doll_bd[r_r][r_c] = '.';
			doll_bd[or_r][or_c] = 'R';
		}

		r_r = or_r;
		r_c = or_c;
		b_r = ob_r;
		b_c = ob_c;
	}
}

int main()
{
	cin >> n >> m;

	string in_mc = "";
	for (int r = 0; r < n; r++)
	{
		cin >> in_mc;
		for (int c = 0; c < m; c++)
		{
			doll_bd[r][c] = in_mc[c];
			if (doll_bd[r][c] == 'R')
			{
				r_r = r;
				r_c = c;
				doll_bd[r][c] = '.';
			}
			else if (doll_bd[r][c] == 'B')
			{
				b_r = r;
				b_c = c;
				doll_bd[r][c] = '.';
			}
		}
	}

	bfs();

	cout << m_cnt << endl;
	
	return 0;
}