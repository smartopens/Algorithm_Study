// SWEA ���ο� �Ҹ��� ġ���
#include <iostream>
using namespace std;

// ���� ó���� �迭�� ���� ������ �ߴ�
// �ٵ�, ���� �迭�� ���� �ʿ���� ��Ʈ ��������
// �迭�� ��ü �� �����ߴ��� Ȯ���� ���� for�� ���ƾ� ������,
// ��Ʈ ������ �� ���� �񱳷� ����
//bool visited[10];

int main() {
	int T;
	cin >> T;
	int total = (1 << 10) - 1; // 0~9������ �ڸ����� ��� 1�� ��Ʈ

	for (int tc = 1; tc <= T; tc++) {
		int ans = 0, N = 0, visited = 0;
		cin >> N;

		while(true) {
			int tmp = N * (++ans); // �̹��� Ž���� ����

			while (tmp > 0) { // �� �ڸ����� ���Ŵ�
				int one = tmp % 10; // ���� �ڸ���
				visited = (1 << one) | visited; // one�� ����Ű�� ������ ��Ʈ�� 1�� ���ֱ�
				tmp /= 10; // ���� �ڸ��� Ž���Ϸ� ����
			}

			if (visited == total) break; // 0~9 ������ ��� 1�� �����ٸ� Ž�� ����
		}

		// output
		cout << "#" << tc << " " << ans * N << "\n";
	}

	return 0;
}