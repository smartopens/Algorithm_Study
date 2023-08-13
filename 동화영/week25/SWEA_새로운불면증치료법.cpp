// SWEA 새로운 불면증 치료법
#include <iostream>
using namespace std;

// 나는 처음에 배열을 만들 생각을 했다
// 근데, 굳이 배열을 만들 필요없이 비트 연산하자
// 배열은 전체 다 등장했는지 확인할 때도 for문 돌아야 하지만,
// 비트 연산은 한 번의 비교로 가능
//bool visited[10];

int main() {
	int T;
	cin >> T;
	int total = (1 << 10) - 1; // 0~9까지의 자릿수가 모두 1인 비트

	for (int tc = 1; tc <= T; tc++) {
		int ans = 0, N = 0, visited = 0;
		cin >> N;

		while(true) {
			int tmp = N * (++ans); // 이번에 탐색할 숫자

			while (tmp > 0) { // 각 자릿수를 볼거다
				int one = tmp % 10; // 일의 자릿수
				visited = (1 << one) | visited; // one이 가리키는 숫자의 비트를 1로 켜주기
				tmp /= 10; // 다음 자릿수 탐색하러 가기
			}

			if (visited == total) break; // 0~9 범위가 모두 1로 켜졌다면 탐색 종료
		}

		// output
		cout << "#" << tc << " " << ans * N << "\n";
	}

	return 0;
}