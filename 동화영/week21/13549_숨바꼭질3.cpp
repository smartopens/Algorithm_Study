// 13549 숨바꼭질 3
#include <iostream>
#include <queue>
using namespace std;

struct NODE {
	int time; // pnt에 도달하는데 걸린 시간
	int pnt; // pnt 지점

	bool operator < (NODE nxt) const {
		if (time < nxt.time) return false;
		if (time > nxt.time) return true;
		if (pnt < nxt.pnt) return false;
		if (pnt > nxt.pnt) return true;
		return false;
	}
};

int visited[100001]; // 0~100000 지점에 도달하는데 걸린 시간
int N, K; // N: 수빈이 초기 위치, K: 동생의 위치

int main() {
	// input
	cin >> N >> K;

	for (int i = 0; i <= 100000; i++) {
		visited[i] = 213456789; // 각 지점에 visited 값 최대로 초기화
	}

	priority_queue<NODE> pq;
	pq.push({ 0, N }); // N부터 시작
 	visited[N] = 0;

	while (!pq.empty()) {
		NODE now = pq.top();
		pq.pop();

		// K지점에 도달했다면 종료
		// PQ의 특성상 시간 순으로 pop하기 때문에 처음으로 K에 도달했다면
		// 이게 가장 빠른 길이다
		if (now.pnt == K) {
			break;
		}

		// i == 0 : -1칸으로 이동 (1초 소요)
		// i == 1 : +1칸으로 이동 (1초 소요)
		// i == 2 : *2칸으로 이동 (0초 소요)
		for (int i = 0; i < 3; i++) {
			int nxtNum = i == 2 ? now.pnt * 2 : i == 1 ? now.pnt + 1 : now.pnt - 1;
			int nxtTime = i == 2 ? now.time : now.time + 1;

			if (nxtNum < 0 || nxtNum > 100000) continue; // 0~100000 좌표 넘어가면 무시
			if (visited[nxtNum] <= nxtTime) continue; // 이미 더 일찍 도달했다면 무시

			pq.push({ nxtTime, nxtNum }); // 탐색 예정
			visited[nxtNum] = nxtTime;
		}
	}

	// output
	if (visited[K] == 213456789) visited[K] = -1; // K칸에 도달한 적이 없다면 도달 불가로 판단
	cout << visited[K] << "\n";
	
	return 0;
}