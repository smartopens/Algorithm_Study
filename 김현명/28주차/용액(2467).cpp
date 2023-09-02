#include <iostream>

using namespace std;

int n;
int positions[100002];

int min_v;
int l_v;
int r_v;

// ��׵� �߿��� ���� 0�� ��������� ��츦 ã�´�.
// �� �� n���� ��쿡�� �������� ���ʷ� �ٿ����� ã��.
// ����� ���� 0���� ũ�ٸ� ���� ���̴� ���� �ε����� �����Ѵ�.
// �ݴ��� ���� ���� Ű��� ���� �����Ѵ�.
void z_find()
{
	int l_id = 0;
	int r_id = n - 1;
	int m_id = 0;
	int now_v = 21e8;

	while (l_id < r_id)
	{
		now_v = positions[l_id] + positions[r_id];

		if (abs(min_v) > abs(now_v))
		{
			l_v = positions[l_id];
			r_v = positions[r_id];
			min_v = abs(now_v);
		}

		if (now_v == 0)
		{
			return;
		}
		else if (now_v < 0)
		{
			l_id += 1;
		}
		else if (now_v > 0)
		{
			r_id -= 1;
		}
	}
}

int main()
{
	cin >> n;

	// ��� ���� �Է� �޴´�.
	for (int i = 0; i < n; i++)
	{
		cin >> positions[i];
	}

	// �ּ� ��� ���� ���� �ʱ�ȭ �ϱ�
	// ���������� ����Ѵ�.
	min_v = 21e8;

	// ����� ���� 0�� ��������� ��츦 ã�´�.
	z_find();

	cout << l_v << " ";
	cout << r_v << endl;

	return 0;
}