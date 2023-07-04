// 16926 배열 돌리기1
#include <iostream>
using namespace std;

int MAP[300][300]; // 배열
int N, M; // 배열의 사이즈 N*M

// 회전
void Rotate() {
	int cnt = N > M ? M / 2 : N / 2; // 배열 내 회전이 일어나는 사각형의 개수

	// 각 사각형마다 회전 적용
	for (int i = 0; i < cnt; i++) {
		int tmp = MAP[i][i]; // 시작점의 값은 별도 저장

		// upper side
		for (int j = i; j < M - 1 - i; j++) {
			MAP[i][j] = MAP[i][j + 1];
		}

		// right side
		for (int j = i; j < N - 1 - i; j++) {
			MAP[j][M - 1 - i] = MAP[j + 1][M - 1 - i];
		}

		// lower side
		for (int j = M - 1 - i; j > i; j--) {
			MAP[N - 1 - i][j] = MAP[N - 1 - i][j - 1];
		}

		// left side
		for (int j = N - 1 - i; j > i; j--) {
			MAP[j][i] = MAP[j - 1][i];
		}

		MAP[i + 1][i] = tmp; // 저장해둔 시작점까지 회전 완료
	}
}

int main() {
	// input
	int R;
	cin >> N >> M >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	// R번의 회전 실행
	for (int i = 0; i < R; i++) Rotate();

	// output
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << MAP[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}