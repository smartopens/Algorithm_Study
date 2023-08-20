// 1613 ����
#include <iostream>
using namespace std;

int HISTORY[401][401]; // A -> B ���� ���� ���

int main() {
	// �� ������ ��� ����� ���� ó���� ������Ѵ�
	// ���ߴ��� �ð� �ʰ� �߻�,,
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	// input
	int N, K, S;
	cin >> N >> K;

	int prev, nxt;
	for (int i = 0; i < K; i++) {
		cin >> prev >> nxt;

		HISTORY[prev][nxt] = -1; // prev -> nxt �� ��� -1 ���
		HISTORY[nxt][prev] = 1; // �� �ݴ�� 1�� ���
	}

	// Floyd-Warshall
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (HISTORY[i][j] == 0) { // ���� ã�� ���� ��ζ��
					if (HISTORY[i][k] == 1 && HISTORY[k][j] == 1) HISTORY[i][j] = 1; // k�� ���ؼ� �� �� �ִ� ������� �Ǻ� �� ����
					else if (HISTORY[i][k] == -1 && HISTORY[k][j] == -1) HISTORY[i][j] = -1;
				}
			}
		}
	}

	// output
	cin >> S;
	for (int i = 0; i < S; i++) {
		cin >> prev >> nxt;
		cout << HISTORY[prev][nxt] << "\n";
	}

	return 0;
}