/* LCA */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 각 노드의 정보
struct Node {
	int parent; // 부모노드
	int level; // 노드의 레벨
};

vector<int> al[50001]; // 입력 용도(연결된 두 노드의 인접리스트)
Node parent[50001]; // 각 노드들의 정보
int N; // 노드의 총 개수

// 입력값을 토대로 트리 만들기
void makeTree() {
	queue<int> q;

	// 루트는 1번 노드이므로 1에서부터 시작
	q.push(1);
	parent[1].parent = 0;
	parent[1].level = 0;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		// now번 노드와 연결된 노드들을 탐색하기
		int sz = al[now].size();
		for (int i = 0; i < sz; i++) {
			int nxt = al[now][i];

			if (nxt == 1) continue; // root노드(1번)라면 무시
			if (parent[nxt].parent != 0) continue; // 이미 부모노드를 찾은 노드라면 무시

			// nxt 노드의 부모는 now이다
			// nxt 노드의 레벨은 부모노드(now)의 레벨보다 1 크다
			parent[nxt].parent = now;
			parent[nxt].level = parent[now].level + 1;

			q.push(nxt); // nxt 노드 탐색 예정
		}
	}
}

// num번 노드를 lev까지 올라와 맞춰주기
int getLevel(int num, int lev) {
	int ret = num;
	int cLev = parent[num].level;

	// num번 노드의 (현재 레벨 - 목표 레벨)만큼 부모노드로 타고 올라가기
	for (int i = 0; i < cLev - lev; ++i) {
		ret = parent[ret].parent;
	}

	return ret;
}

// a와 b번 노드의 가장 가까운 공통 조상 찾기
int findCA(int a, int b) {
	int ca = a, cb = b;

	// a와 b의 현재 레벨
	int la = parent[ca].level;
	int lb = parent[cb].level;

	// la가 더 깊은 레벨에 있다면
	if (la > lb) {
		ca = getLevel(a, lb); // a노드를 b의 레벨까지 맞춰주기
	}
	// lb가 더 깊은 레벨에 있다면
	else if (la < lb) {
		cb = getLevel(b, la); // b노드를 a의 레벨까지 맞춰주기
	}

	// ca 와 cb는 현재 같은 레벨에 위치한다
	// 한칸씩 위로 올라가다가 같은 조상 발견 시 종료
	while (ca != cb) {
		ca = parent[ca].parent;
		cb = parent[cb].parent;
	}

	return ca;
}

int main() {
	// input
	cin >> N;
	int a, b;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		al[a].push_back(b); // 양방향 연결
		al[b].push_back(a);
	}

	// 1. 트리 구축
	makeTree();

	// M개의 쿼리 입력받기
	int M;
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;

		// 2. a와 b 노드의 가장 가까운 공통 조상 찾아서 출력
		cout << findCA(a, b) << "\n";
	}

	return 0;
}