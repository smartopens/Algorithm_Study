/* 저울 */
#include <iostream>
#include <algorithm>
using namespace std;

// 1. 주어진 저울추의 무게를 오름차순으로 정렬한다.
// 2. 앞에서부터 더해가면서 만들 수 있는 최대 무게를 구한다.
// 3. 다음번 저울추의 무게와 비교한다. -> 바로 이어질 수 있는가?

int SCALE[1001]; // 각 저울추의 무게
int N; // 저울추의 총 개수

int main() {
	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> SCALE[i];
	}

	// 저울추의 무게를 오름차순으로 정렬
	sort(SCALE, SCALE + N);

	// 예외) 무게가 1인 저울추가 없다면 답은 1
	if (SCALE[0] != 1) {
		cout << 1 << "\n";
		return 0;
	}

	// solve
	// 무게 1부터 시작
	int prev = 1; // 이전까지 만들어 온 최대 무게
	for (int i = 1; i < N; i++) {
		// 이전까지의 무게 + i번째 저울추의 무게 ==> 지금까지 만들 수 있는 최대 무게
		// 이 최대 무게가 i+1 번째 저울추의 무게보다 작다면 다음번으로 도달 불가
		// +1 은 i번째까지 만든 최대 무게 바로 다음 무게가 i+1번 저울추의 무게인 경우를 고려
		if (prev + SCALE[i] + 1 >= SCALE[i+1]) {
			prev += SCALE[i]; // i번까지 만들 수 있는 최대 무게
		}
		else { // i+1번 저울추까지 도달 불가시 탐색 종료
			prev += SCALE[i];
			break;
		}
	}

	// output
	// 최종 prev의 값은 만들 수 있는 최대값이기 때문에
	// 만들 수 없는 최소값은 +1 해줘야 한다 (답)
	cout << (prev + 1) << "\n";

	return 0;
}

/*
8
1 1 2 3 6 7 20 30
*/
/*
7
1 2 3 6 7 20 30
*/