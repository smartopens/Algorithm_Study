// 1715 카드 정렬하기
#include <iostream>
#include <queue>
using namespace std;

// 현 기준에서 가장 작은 카드 묶음 2개를 골라서
// 비교하는 횟수를 더한다
// 단순히 초기에 1회를 정렬하지 않고 PQ를 사용하는 이유는
// 비교 횟수를 더하면서도 묶음의 카드 수가 갱신되고 이 안에서 또 정렬이 필요하기 때문에
// 현재 기준으로 가장 작은 묶음 2개를 고르는게 맞다 (그리디 알고리즘)

int main() {
	int N, num; // N: 카드 묶음의 수, num: 입력값
	priority_queue<int, vector<int>, greater<int>> pq; // 오름차순 정렬의 PQ

	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		pq.push(num);
	}

	int sum = 0; // 총 비교횟수

	// pq에 최소 2개가 있어야 비교 가능
	// 1개의 데이터만 있다면 최종 비교 후 합쳐진 총 카드의 수이다
	while (pq.size() > 1) {
		// 2개의 최소 묶음을 가져온다
		int one = pq.top(); pq.pop();
		int two = pq.top(); pq.pop();
		sum += (one + two); // 비교 횟수를 더한다
		pq.push(one + two); // pq에 데이터를 새로 넣어준다
	}

	// output
	cout << sum << "\n";

	return 0;
}