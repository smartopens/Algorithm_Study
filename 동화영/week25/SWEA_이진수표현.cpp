// SWEA ������ ǥ��
#include <iostream>
using namespace std;

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, M;
		cin >> N >> M; // ���� M�� ������ N���� ��Ʈ�� ��� 1�� ��츦 ���϶�

		int lastNBit = (1 << N) - 1; // ������ N���� bit�� ��� 1�� ����

		// ������ N���� ��Ʈ�� 1, �ܴ̿� 0���� �̷���� lastNBit
		// lastNBit�� & ������ �ϰ� �Ǹ� ���� ��� 0�� �� ���̴�
		// �׸��� ������ N ��Ʈ�� 1�̸� & ������ ����� 1�̰�, 0�̸� ���� ��� ���� 0 �ϰ��̴�
		// ��, lastNBit�� M�� & ���� ����� lastNBit�� �����ϸ� ������ N���� ��Ʈ�� 1�� �����̴�

		// (lastNBit | M) == M �� ����
		if ((lastNBit & M) == lastNBit) cout << "#" << tc << " ON\n";
		else cout << "#" << tc << " OFF\n";
	}

	return 0;
}