// 1613 역사
#include <iostream>
using namespace std;

int HISTORY[401][401]; // A -> B 역사 순서 기록

int main() {
	// 이 문제의 경우 입출력 단축 처리를 해줘야한다
	// 안했더니 시간 초과 발생,,
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	// input
	int N, K, S;
	cin >> N >> K;

	int prev, nxt;
	for (int i = 0; i < K; i++) {
		cin >> prev >> nxt;

		HISTORY[prev][nxt] = -1; // prev -> nxt 의 경우 -1 기록
		HISTORY[nxt][prev] = 1; // 이 반대는 1을 기록
	}

	// Floyd-Warshall
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (HISTORY[i][j] == 0) { // 아직 찾지 못한 경로라면
					if (HISTORY[i][k] == 1 && HISTORY[k][j] == 1) HISTORY[i][j] = 1; // k를 통해서 갈 수 있는 경로인지 판별 후 갱신
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