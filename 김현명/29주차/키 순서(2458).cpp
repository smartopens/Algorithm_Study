#include <iostream>
#include <vector>

using namespace std;

int n, m;

vector<int> taller[502];
vector<int> smaller[502];

int t_vi[502][502];
int s_vi[502][502];

int main()
{
	cin >> n >> m;
	
	// Ű ��� �� �Է¹ޱ�
	int s_n = 0;
	int s_in = 0;
	int b_in = 0;
	for (int i = 0; i < m; i++)
	{
		cin >> s_in >> b_in;
		taller[s_in].push_back(b_in);
		smaller[b_in].push_back(s_in);
		t_vi[s_in][b_in] = 1;
		s_vi[b_in][s_in] = 1;
	}

	// �÷��̵� ���� ������ �ϳ��̴�.
	// ��� ���踦 ������ �ڷᱸ���� �����Ѵ�.
	// ��� ��带 ���鼭 �� ��庸�� ū���, ���� ��� ���
	// Ȯ�����ش�.
	int tr_v = 0;
	int sr_v = 0;
	for (int v = 1; v < n + 1; v++)
	{
		for (int s = 0; s < taller[v].size(); s++)
		{
			tr_v = taller[v][s];
			for (int k = 0; k < taller[tr_v].size(); k++)
			{
				if (t_vi[v][taller[tr_v][k]] != 1)
				{
					taller[v].push_back(taller[tr_v][k]);
					t_vi[v][taller[tr_v][k]] = 1;
				}
			}
		}

		for (int s = 0; s < smaller[v].size(); s++)
		{
			sr_v = smaller[v][s];
			for (int k = 0; k < smaller[sr_v].size(); k++)
			{
				if (s_vi[v][smaller[sr_v][k]] != 1)
				{
					smaller[v].push_back(smaller[sr_v][k]);
					s_vi[v][smaller[sr_v][k]] = 1;
				}
			}
		}
	}

	// ���������� ��帶�� ũ�ų� ���� ��찡 n-1���� Ȯ��
	// �ȴٸ� �ش� ����� ������ �� �� �ִ�.
	for (int v = 1; v < n + 1; v++)
	{
		if (smaller[v].size() + taller[v].size() == n - 1)
		{
			s_n += 1;
		}
	}

	cout << s_n << endl;
	return 0;
}