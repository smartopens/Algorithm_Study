// SWEA 이진수 표현
#include <iostream>
using namespace std;

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N, M;
		cin >> N >> M; // 숫자 M의 마지막 N개의 비트가 모두 1인 경우를 구하라

		int lastNBit = (1 << N) - 1; // 마지막 N개의 bit가 모두 1인 숫자

		// 마지막 N개의 비트는 1, 이외는 0으로 이루어진 lastNBit
		// lastNBit와 & 연산을 하게 되면 앞은 모두 0이 될 것이다
		// 그리고 마지막 N 비트는 1이면 & 연산의 결과가 1이고, 0이면 연산 결과 또한 0 일것이다
		// 즉, lastNBit와 M의 & 연산 결과가 lastNBit와 동일하면 마지막 N개의 비트가 1인 숫자이다

		// (lastNBit | M) == M 과 동일
		if ((lastNBit & M) == lastNBit) cout << "#" << tc << " ON\n";
		else cout << "#" << tc << " OFF\n";
	}

	return 0;
}