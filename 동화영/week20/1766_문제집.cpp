// 1766 문제집
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> al[32001]; // 각 지점에서 나가는 단방향 간선의 도착 지점
int indegree[32001]; // 각 지점에 들어오는 간선의 수
int N; // 문제의 수

int main() {
	// input
	int A, B;
	int M;
	cin >> N >> M;


	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		al[A].push_back(B); // A->B
		indegree[B]++; // B에 들어오는 간선의 수를 증가
	}

	priority_queue<int, vector<int>, greater<int>> pq; // 문제번호(=난이도) 기준 오름차순
	for (int i = 1; i <= N; i++) {
		// 들어오는 간선이 없는 문제번호들 먼저 탐색
		if (indegree[i] == 0) pq.push(i);
	}

	// 1번 조건. N개의 문제는 모두 풀어야 한다.
	for (int i = 1; i <= N; i++) {
		// 가장 우선수위의 문제를 먼저 푼다
		int now = pq.top();
		pq.pop();

		cout << now << " "; // 바로 output

		// now번 문제를 풀었으니 now에서 나가는 간선의 도착지점의 indegree 감소
		for (int j = 0; j < al[now].size(); j++) {
			int nxt = al[now][j];

			indegree[nxt]--;
			if (indegree[nxt] == 0) pq.push(nxt); // 들어오는 간선이 0개가 되었다면 탐색 대상
		}
	}

	return 0;
}