/* 스타트 택시 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAX_N = 21;
const int DIR_NUM = 4;

struct NODE {
	int r;
	int c;
};

struct COOR {
	int r;
	int c;
	int dist;

	// 거리 오름차순 -> 행 오름차순 -> 열 오름차순
	bool operator < (COOR nxt) const {
		if (dist < nxt.dist) return false;
		if (dist > nxt.dist) return true;
		if (r < nxt.r) return false;
		if (r > nxt.r) return true;
		if (c < nxt.c) return false;
		if (c > nxt.c) return true;
		return false;
	}
};

int rdir[DIR_NUM] = { -1, 1, 0, 0 }; // 상하좌우
int cdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N]; // -1: 벽, 0: 빈칸, 1~M: 승객의 시작지점
int N, M; // N: 격자의 사이즈, M: 승객의 수
int fuel; // 연료의 양

NODE taxi; // 택시의 위치
vector<NODE> sPoint; // 각 승객의 출발지점
vector<NODE> ePoint; // 각 승객의 도착지점

// 현재 택시의 위치를 기준으로 가장 가까운 승객을 고른다
// 거리의 순 -> 행의 순 -> 열의 순 으로 선택
int selectPerson() {
	int num = 0; // 선택될 승객의 번호

	// visited와 pq 준비
	// 택시의 현재 위치부터 시작을 표기
	int visited[MAX_N][MAX_N] = { 0, };
	visited[taxi.r][taxi.c] = 1;

	priority_queue<COOR> pq;
	pq.push({ taxi.r, taxi.c, 0 });

	while (!pq.empty()) {
		// 거리순으로 정렬 후
		// 동일한 거리 내에서 행과 열의 순으로 태우러 갈 승객을 선택하기 때문에
		// 각 거리마다 size를 구하여 sz만큼만 돌려보기
		int sz = pq.size();

		for (int i = 0; i < sz; i++) {
			COOR now = pq.top();
			pq.pop();

			// now칸에 승객이 기다리고 있다면 태운다
			if (MAP[now.r][now.c] > 0) {
				// now칸에 있는 승객을 태우러 가는데 드는 연료의 양이 현재 남아있는 연료의 양보다 크다면
				// 즉시 영업 종료
				if (fuel < now.dist) return -1;

				// 태우러 갈 수 있을 정도의 연료가 존재한다면
				fuel -= now.dist; // 연료 소모
				num = MAP[now.r][now.c]; // 태우러 간 승객의 번호 저장 -> 반환
				taxi = { now.r, now.c }; // 택시 이동
				MAP[now.r][now.c] = 0; // now칸에서 대기 중이던 승객 지워주기
				return num; // 승객 번호 반환
			}

			// now칸에 승객이 없다면 다시 4방향 탐색
			for (int i = 0; i < DIR_NUM; i++) {
				int nr = now.r + rdir[i];
				int nc = now.c + cdir[i];

				if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue; // 격자 밖은 무시
				if (MAP[nr][nc] == -1) continue; // 벽은 진입 불가
				if (visited[nr][nc] == 1) continue; // 이미 방문한 칸은 무시

				pq.push({ nr, nc, now.dist + 1 }); // 다음에 탐색할 칸을 추가 - 거리를 현재보다 +1만큼
				visited[nr][nc] = 1; // 방문 표기
			}
		}
	}

	return -1;
}

// num번 승객을 도착지점까지 데려다주기
int goEnd(int num) {
	NODE sTarget = sPoint[num]; // num번 승객의 시작지점
	NODE eTarget = ePoint[num]; // num번 승객의 도착지점

	// visited와 queue 준비
	// num번 승객의 시작지점으로부터 탐색 시작하기
	int visited[MAX_N][MAX_N] = { 0, };
	visited[sTarget.r][sTarget.c] = 1;

	queue<NODE> q;
	q.push({ sTarget.r, sTarget.c });

	while (!q.empty()) {
		NODE now = q.front();
		q.pop();

		// 4방향으로 탐색하며 도착지점 찾으러가기
		for (int i = 0; i < DIR_NUM; i++) {
			int nr = now.r + rdir[i];
			int nc = now.c + cdir[i];

			if (nr <= 0 || nc <= 0 || nr > N || nc > N) continue; // 격자 밖은 무시
			if (MAP[nr][nc] == -1) continue; // 벽은 진입 불가
			if (visited[nr][nc] > 0) continue; // 이미 방문한 칸은 무시

			// 도착지점을 찾았다면 바로 데려다주기
			if (nr == eTarget.r && nc == eTarget.c) {
				// 도착지점까지 데려다주는데 드는 연료의 양이 현재 남아있는 연료의 양보다 크다면
				// 즉시 영업 종료
				int dist = visited[now.r][now.c];
				if (fuel < dist) return -1;

				// dist만큼의 연료 소모 후 dist*2만큼의 연료가 충전
				// -> 즉, 연료 소모없이 dist만큼만 충전해주기
				fuel += dist;
				taxi = { nr, nc }; // 택시 이동
				return 0;
			}

			// 아직 도착지점에 가지 못했다면 다음칸을 탐색
			q.push({ nr, nc });
			visited[nr][nc] = visited[now.r][now.c] + 1; // 도착지점까지의 거리를 저장
		}
	}

	return -1;
}

int main() {
	//  input
	cin >> N >> M >> fuel;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) MAP[i][j] = -1; // 벽은 -1로 변경하여 저장
		}
	}

	int ir, ic, er, ec;;
	cin >> ir >> ic;
	taxi = { ir, ic }; // 택시의 초기위치
	
	// 1~M 승객의 시작/도착 지점
	sPoint.push_back({ 0, 0 }); // 인덱스 맞추기 위해 0번에 임의로 push
	ePoint.push_back({ 0, 0 });
	for (int i = 1; i <= M; i++) {
		cin >> ir >> ic >> er >> ec;
		sPoint.push_back({ ir, ic }); // i번 승객의 시작지점
		ePoint.push_back({ er, ec }); // i번 승객의 도착지점
		MAP[ir][ic] = i; // MAP에 i번 승객의 시작지점 표기
	}

	// M명의 승객을 이동시킨다
	for (int i = 0; i < M; i++) {
		int num = selectPerson(); // 가장 최단경로에 서있는 승객을 고른다
		if (num == -1) { // 승객 태우러 가는 길에 연료가 바닥났다면 운행 종료
			fuel = -1; // 연료 바닥 -1 표기
			break;
		}

		// num 승객의 도착지점으로 간다
		if (goEnd(num) == -1) { // 도착지점으로 가는 길에 연료가바닥난다면 운행 종료
			fuel = -1; // 연료 바닥 -1 표기
			break;
		}
	}

	// output
	cout << fuel; // 남은 연료의 양 출력

	return 0;
}