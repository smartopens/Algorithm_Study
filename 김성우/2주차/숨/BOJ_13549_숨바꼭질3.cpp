#include<iostream>
#include<queue>
using namespace std;

#define MAX 100000

int n, k;
int dist[100100]; // 이동 거리
deque<int> dq;
int ans;

// 다익스트라 문제
// 먼저 X*2(순간이동)할 때부터 이동한다.
// 그 후 X+1, X-1 중 작은 값을 데이터에 넣는다
// 처리 순서를 deque에 넣고, 순서대로 꺼내서 돌린다.

int main() {

	cin >> n >> k;

	dq.push_back(n);

	dist[n] = 1;
	
	while (!dq.empty()) {

		int pos = dq.front();
		dq.pop_front();

		if (pos == k) {
			ans = dist[pos] - 1;
			break;
		}

		if (pos * 2 <= MAX && !dist[pos * 2]) {
			dq.push_front(pos * 2);
			dist[pos * 2] = dist[pos];
		}

		if (pos - 1 >= 0 && !dist[pos - 1]) {
			dq.push_back(pos - 1);
			dist[pos - 1] = dist[pos] + 1;
		}

		if (pos + 1 <= MAX && !dist[pos + 1]) {
			dq.push_back(pos + 1);
			dist[pos + 1] = dist[pos] + 1;
		}

		

	}

	cout << ans;

}