/* 개똥벌레 */
#include <iostream>
using namespace std;

int upper[500001]; // 종유석의 길이
int lower[500001]; // 석순의 길이
int N, H;

int main() {
	cin >> N >> H;

	// 1. 입력값으로 종유석과 석순의 길이를 DAT로 카운팅한다
	// 즉 upper[3]은 길이가 3인 종유석의 개수
	int leng;
	for (int i = 0; i < N; i++) {
		cin >> leng;
		if (i % 2 == 0) lower[leng]++;
		else upper[leng]++;
	}

	// 2. 종유석과 석순 각각의 누적 수를 구한다
	// 즉, 길이가 3인 종유석은 길이가 1, 2인 종유석에 영향을 끼치므로 누적해주기 (높이 기준으로)
	for (int i = 2; i < H; i++) {
		upper[H - i] += upper[H - i + 1];
		lower[H - i] += lower[H - i + 1];
	}

	// 3. 높이 기준으로 종유석/석순 장애물의 개수 - 최소값 구하기
	// 예) 높이 5 -> 2번 높이에서 장애물의 개수는 upper[2] + lower[4]
	int val = 21e8, cnt = 0;
	for (int i = 1; i <= H; i++) {
		int tmp = upper[i] + lower[H - i + 1];

		if (tmp < val) { // 더 작은 값을 구했다면 val, cnt 갱신
			val = upper[i] + lower[H - i + 1];
			cnt = 1;
		}
		else if (tmp == val) cnt++; // 현기준 최소값과 동일한 지점을 찾았다면 cnt 카운팅
	}

	// output
	cout << val << " " << cnt << "\n";

	return 0;
}