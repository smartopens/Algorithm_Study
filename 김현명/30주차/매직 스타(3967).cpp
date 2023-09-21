#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n, m;
char s_map[5][9];

int vi[14];
vector<string> ans;
int max_a;

struct s_no {
	int r;
	int c;
};

// �˻� ����
s_no s_ch[6][4] =
{
	{{0,4},{1,3},{2,2},{3,1}},
	{{0,4},{1,5},{2,6},{3,7}},
	{{1,1},{1,3},{1,5},{1,7}},
	{{3,1},{3,3},{3,5},{3,7}},
	{{4,4},{3,3},{2,2},{1,1}},
	{{4,4},{3,5},{3,6},{3,7}}
};

bool p_ok(int sn)
{
	int t_cn = 0;
	int t_sn = 0;
	int sr = 0;
	int sc = 0;

	bool is_ok = false;
	for (int r = 0; r < 6; r++)
	{
		t_cn = 0;
		t_sn = 0;
		for (int c = 0; c < 4; c++)
		{
			sr = s_ch[r][c].r;
			sc = s_ch[r][c].c;

			if (s_map[sr][sc] != '.')
			{
				if (s_map[sr][sc] != 'x')
				{
					t_sn += ((int)(s_map[sr][sc] - 'A') + 1);
					t_cn += 1;
				}
			}
		}

		if (t_cn == 4)
		{
			if (t_sn != 26)
			{
				return false;
			}
		}
	}
	return true;
}

// ó������ ä���ߵǴ� ����� ���� ����Ѵ�.
// �׸��� ���ܰ躰�� �ش� ������ ����� �� �ִ����� ����.
// �̷��� �� ��� �б����� �پ��� �������� ���� ã����
// Ž���� �����.
bool dfs(int pr, int pc, int a)
{
	if (a >= max_a)
	{
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < m; c++)
			{
				cout << s_map[r][c];
			}
			cout << endl;
		}
		return true;
	}

	bool is_ok = false;
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
		{
			if (s_map[r][c] == 'x')
			{
				for (int v = 1; v < 13; v++)
				{
					if (vi[v] != 1)
					{
						vi[v] = 1;
						s_map[r][c] = (char)('A' + v - 1);
						if (p_ok(v) == false)
						{
							s_map[r][c] = 'x';
							vi[v] = 0;
							continue;
						}
						if (dfs(pr, pc + 1, a + 1) == true)
						{
							return true;
						}
						vi[v] = 0;
						s_map[r][c] = 'x';
					}
				}
				is_ok = true;
				break;
			}
		}
		if (is_ok) break;
	}
	return false;
}

int main()
{
	// ���ڸ� �� ������
	n = 5;
	m = 9;

	// �� ���� �Է¹ޱ�
	string in_sm;
	for (int r = 0; r < n; r++)
	{
		cin >> in_sm;
		for (int c = 0; c < m; c++)
		{
			s_map[r][c] = in_sm[c];

			// ��ü ���� 1���� 12���� ���� ����.
			if (s_map[r][c] != '.' && s_map[r][c] != 'x')
			{
				vi[int(s_map[r][c] - 'A') + 1] = 1;
			}

			// ä���ߵǴ� ��� �� ����
			if (s_map[r][c] == 'x')
			{
				max_a += 1;
			}
		}
	}

	bool t_ok = dfs(0,0,0);

	return 0;
}