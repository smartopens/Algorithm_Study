#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

// ������ ������ ���
int n, h;
int top[500002];
int bottom[500002];

int main() {
	// ���̿� ���� �Է¹ޱ�
	cin >> n >> h;

	// ��ֹ��� �ּҷ� ������ ����
	// ���� ����� ���� ����Ѵ�.
	int min_val = 21e8;
	int cnt = 0;

	// ¦�������� ������, Ȧ�������� �������� ����Ѵ�.
	// �� ��, �� ���ǵ��� ������ ��ġ�� ��츦 �����Ѵ�.
	// ������ �� ��� ���̿� ���̰� �ʹ� ũ�� ������ �ð��� �����ϴ�.
	// ���, �� ������ ������ �������� ����Ѵ�.
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;

		if (i % 2 == 0) {
			bottom[num] += 1;
		}
		else if (i % 2 == 1) {
			top[h - num + 1] += 1;
		}
	}

	// ������ ������ �������� ������ ������ �����ش�.
	// �̷��� �ϸ� �� �������� ���븦 ������ ��츦 �� �� �ִ�.
	// ���� ��ü�� �������̶�� �Ѵ�.

	// ����
	for (int i = h; i > 1; i--)
	{
		bottom[i - 1] += bottom[i];
	}

	// ������
	for (int i = 1; i < h; i++)
	{
		top[i + 1] += top[i];
	}

	// �� �������� �ּ� ����� ���� ����Ѵ�.
	// �̶� ���ڵ� ���� ����.
	for (int i = 1; i < h + 1; i++)
	{
		if (bottom[i] + top[i] < min_val)
		{
			min_val = bottom[i] + top[i];
			cnt = 1;
		}
		else if (bottom[i] + top[i] == min_val)
		{
			cnt += 1;
		}
	}

	// �ּ� ���, �ش� ����� �� ���
	cout << min_val << " " << cnt << endl;
	return 0;
}