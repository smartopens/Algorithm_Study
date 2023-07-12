// 2637 장난감 조립
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<pair<int, int>> al[101]; // 각 부품을 만들기 위한 { 재료, 개수 }
int indegree[101]; // 각 부품을 만드는데 필요한 재료의 수
int ans[101]; // 각 부품의 필요한 개수

int main() {
	// input
	int N, M;
	int X, Y, K;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> X >> Y >> K;
		al[X].push_back({ Y, K }); // X를 만드는데 Y가 K개 필요하다
		indegree[Y]++; // (역으로) 재료가 쓰이는 곳의 개수를 센다
	}

	queue<pair<int, int>> q;
	q.push({ N, 1 }); // N번 완제품을 1개 만드는게 목표로 시작
	ans[N] = 1;

	// N개의 완제품/부품을 모두 만들면 결국 N번동안 하나씩 빼서 확인하기
	for (int i = 1; i <= N; i++) {
		pair<int, int> now = q.front();
		q.pop();

		int sz = al[now.first].size();
		for (int j = 0; j < sz; j++) {
			pair<int, int> nxt = al[now.first][j];
			
			indegree[nxt.first]--; // nxt.first를 필요로 하는 부품 하나 감소
			int nxtCnt = now.second * nxt.second; // now 부품을 만들기 위해 필요한 nxt 부품의 개수
			ans[nxt.first] += nxtCnt;
			if (indegree[nxt.first] == 0) // nxt.first번 부품이 필요한 부품을 모두 완료했다면
				q.push({ nxt.first, ans[nxt.first] }); // queue에 넣어서 이후 탐색 예정
		}
	}

	// output
	for (int i = 1; i <= N; i++) {
		// i번 부품을 만들기 위해 필요한 부품이 0개인 경우
		// 즉 기본 부품인 경우에만 { 번호, 개수 }를 출력
		if (al[i].size() == 0) cout << i << " " << ans[i] << "\n";
	}

	return 0;
}