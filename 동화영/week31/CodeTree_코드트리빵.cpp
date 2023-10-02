#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Person {
	int num; //m번
	int r; //위치
	int c;
};

int dr[4] = { -1, 0, 0, 1 }; //상좌우하
int dc[4] = { 0, -1, 1, 0 };

queue<Person> people; //사람들의 현재 위치
vector<pair<int, int>> stores; //목표 편의점
int MAP[16][16]; //0:빈칸, 1:베이스캠프, -1:점유된 베이스캠프, 2~:timer분에 점유된 편의점
int n, m; //n:격자의 사이즈, m:사람의 수
int arrived; //목표 편의점에 도달한 사람의 수
int timer; //타이머

//curr사람이 이동할 방향 탐색
//현위치 -> 편의점까지 이동시 가장 가까운 경로로 한 칸 이동 예정
//따라서, BFS탐색을 하되 각 경로별로 이동방향을 함께 저장
//BFS 탐색 완료 후, 역으로 탐색하며 어느 방향으로 이동할지를 반환
int BFS(Person curr) {
	queue<pair<int, int>> q;
	int visited[16][16] = { 0, };
	int dirHistory[16][16] = { 0, }; //매 이동마다의 이동 방향

	visited[curr.r][curr.c] = 1;
	q.push({ curr.r, curr.c });

	//BFS탐색
	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = now.first + dr[i];
			int nc = now.second + dc[i];

			if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue; //격자 밖은 이동불가
			if (visited[nr][nc] > 0) continue; //기방문 지점은 무시
			if (MAP[nr][nc] < 0 || (MAP[nr][nc] > 1 && MAP[nr][nc] < timer)) continue; //점유된 베이스캠프이거나, timer 이전에 점유된 편의점은 이동 불가
			//timer분에 점유된 편의점으로는 이동 가능(문제에 제시)

			q.push({ nr, nc }); //탐색할 지점 push
			visited[nr][nc] = 1;
			dirHistory[nr][nc] = i; //이동 방향 저장
		}
	}

	//BFS 결과를 역으로 추적
	pair<int, int> history = stores[curr.num]; //편의점에서부터 탐색 시작
	while (1) {
		int dir = dirHistory[history.first][history.second];
		int nr = history.first - dr[dir]; //저장된 방향의 반대로 이동
		int nc = history.second - dc[dir];

		if (nr == curr.r && nc == curr.c) { //현위치를 찾았다면
			return dir; //첫 이동방향을 반환
		}

		history = { nr, nc }; //이동하면서 탐색
	}

	return -1;
}

//1. 격자 내 인원 이동
void Move() {
	int sz = people.size(); //현재 이동할 사람만큼 탐색
	for (int i = 0; i < sz; i++) {
		Person curr = people.front();
		people.pop();

		//BFS - 이번에 탐색할 curr 사람이 이동할 방향
		int dir = BFS(curr);
		int nr = curr.r + dr[dir]; //이동
		int nc = curr.c + dc[dir];

		//목표 편의점에 도달했다면
		if (stores[curr.num].first == nr && stores[curr.num].second == nc) {
			arrived++; //도착 인원 카운팅
			MAP[nr][nc] = timer; //MAP에 표기(timer분에 점유된 편의점)
			continue; //이동 멈춤
		}

		people.push({ curr.num, nr, nc }); //아직 도달 못한 사람은 계속 이동
	}
}

//timer번 사람의 시작 베이스캠프 찾기
pair<int, int> GoBasecamp() {
	pair<int, int> tStore = stores[timer]; //목표 편의점의 위치
	int visited[16][16] = { 0, };
	queue<pair<int, int>> q;
	
	q.push({ tStore.first, tStore.second });
	visited[tStore.first][tStore.second] = 1;

	while (!q.empty()) {
		pair<int, int> curr = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nr = curr.first + dr[i];
			int nc = curr.second + dc[i];

			if (nr <= 0 || nc <= 0 || nr > n || nc > n) continue; //격자 밖은 이동불가
			if (visited[nr][nc] > 0) continue; //기방문 지점은 무시
			if (MAP[nr][nc] < 0 || MAP[nr][nc] > 1) continue; //점유된 베이스캠프와 편의점으로는 이동불가

			if (MAP[nr][nc] == 1) return { nr, nc }; //가장 먼저 찾은 베이스캠프를 반환

			q.push({ nr, nc }); //탐색 계속
			visited[nr][nc] = 1;
		}
	}

	return { 0, 0 };
}

int main() {
	//input
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> MAP[i][j];
		}
	}

	stores.push_back({ 0, 0 });
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		stores.push_back({ x, y }); //m번 사람의 목표 편의점
	}

	timer = 0;
	while (arrived < m) { //전원 도착할 때까지 진행
		timer++; //타이머 작동

		//1. 격자 내 전원 이동(최단거리) & 2.편의점 도착 처리
		Move();

		//3. timer번 사람이 베이스캠프로 이동
		if (timer > m) continue; //단, 전원 출발했다면 무시

		pair<int, int> target = GoBasecamp(); //시작할 베이스캠프 (목표 편의점과 가장 가까운 곳)
		if (target.first != 0) {
			MAP[target.first][target.second] = -1; //베이스캠프 점유
			people.push({ timer, target.first, target.second }); //m번 사람의 이동 시작
		}
	}

	//output
	cout << timer << "\n";

	return 0;
}