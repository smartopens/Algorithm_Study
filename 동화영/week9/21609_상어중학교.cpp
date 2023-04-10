/* 상어 중학교 */
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define MAX_N 20
#define DIR_NUM 4

// 블록 그룹
struct Node {
	int cnt; // 블록의 개수
	int rainbow; // 무지개블록의 개수
	int y; // 기준 블록의 좌표
	int x;

	bool operator < (Node nxt) const {
		if (cnt > nxt.cnt) return false;
		if (cnt < nxt.cnt) return true;
		if (rainbow > nxt.rainbow) return false;
		if (rainbow < nxt.rainbow) return true;
		if (y > nxt.y) return false;
		if (y < nxt.y) return true;
		if (x > nxt.x) return false;
		if (x < nxt.x) return true;
		return false;
	}
};

int ydir[DIR_NUM] = { -1, 1, 0, 0 };
int xdir[DIR_NUM] = { 0, 0, -1, 1 };

priority_queue<Node> pq;

int visited[MAX_N][MAX_N];
int MAP[MAX_N][MAX_N]; // -2: 빈칸, -1: 검은색, 0: 무지개, 1~M: 일반
int N, M; // N: 격자 사이즈, M: 일반 블록 종류의 수

int ans; // 획득 점수

// 블록 그룹 탐색
// 찾은 그룹의 블록 개수 반환
int findGroup(int cy, int cx) {
	int color = MAP[cy][cx]; // 시작 블록의 색상
	int oriy = cy, orix = cx; // 기준 블록 좌표 (y, x)
	int eCnt = 1, rCnt = 0; // eCnt: 그룹 내 블록의 총 개수, rCnt: 그룹 내 무지개블록의 개수

	// bfs탐색을 위한 used배열과 queue 준비
	int used[MAX_N][MAX_N] = { 0, };
	used[cy][cx] = 1;
	queue<pair<int, int>> q;
	q.push({ cy, cx });

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int ny = now.first + ydir[i];
			int nx = now.second + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // 격자 밖은 무시
			if (used[ny][nx] == 1) continue; // 기방문한 칸은 무시
			if (MAP[ny][nx] < 0) continue; // 일반/무지개 블록만 탐색
			if (MAP[ny][nx] > 0 && MAP[ny][nx] != color) continue; // 일반 블록 중에서도 시작 블록의 색상과 동일 색상만을 탐색

			// (ny, nx) 방문 탐색
			q.push({ ny, nx });
			used[ny][nx] = 1;
			
			if (MAP[ny][nx] > 0) { // 일반 블록
				// 전체 방문기록에 저장
				visited[ny][nx] = 1;

				// 그룹의 기준 블록 갱신
				// 행 최소 -> 열 최소
				if (ny < oriy) {
					oriy = ny;
					orix = nx;
				}
				else if (ny == oriy) {
					if (nx < orix) {
						orix = nx;
					}
				}
			}
			// 무지개 블록 - 개수 증가
			// 무지개 블록은 전체 방문기록에 저장하지 않는다
			// 탐색 시작 위치는 일반 블록 기준으로 판단하므로
			else rCnt++;

			eCnt++; // 블록의 총 개수 증가
		}
	}

	if(eCnt > 1) pq.push({ eCnt, rCnt, oriy, orix }); // 블록 개수가 2개 이상인 그룹이라면 pq에 추가

	return eCnt; // 방금 탐색한 그룹의 총 블록 개수를 반환
}

// 가장 큰 블록 그룹을 제거
void Remove() {
	Node t = pq.top(); // 우선순위 기준으로 최대 블록 그룹 추출
	while (!pq.empty()) pq.pop(); // 나머지는 pop

	int color = MAP[t.y][t.x]; // 제거할 대상 그룹의 기준 색상
	MAP[t.y][t.x] = -2; // 제거하여 빈칸 처리

	int used[MAX_N][MAX_N] = { 0, }; // 타겟 그룹을 제거하는데 사용
	used[t.y][t.x] = 1;

	queue<pair<int, int>> q; // bfs 탐색을 위한 queue 준비
	q.push({ t.y, t.x });

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int ny = now.first + ydir[i];
			int nx = now.second + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // 격자 밖은 무시
			if (used[ny][nx] == 1) continue; // 기방문한 칸은 무시
			if (MAP[ny][nx] < 0) continue; // 일반/무지개 블록만 탐색
			if (MAP[ny][nx] > 0 && MAP[ny][nx] != color) continue; // 일반 블록 중에서도 타겟 색상과 동일한 블록만 탐색

			// 탐색할 (ny, nx) 블록 방문 처리 및 빈칸 처리
			q.push({ ny, nx });
			used[ny][nx] = 1;
			MAP[ny][nx] = -2;
		}
	}

	ans += (t.cnt*t.cnt); // 제거한 블록의 개수^2 만큼 점수 획득
}

// 중력 작용
void Gravity() {
	for (int i = 0; i < N; i++) { // 각 열에 대해
		int ind = N - 1; // 다음 일반/무지개 블록을 만났을 때 ind행으로 블록을 떨어뜨린다
		for (int j = N - 1; j >= 0; j--) { // 밑에서부터 각 행을 탐색
			if (MAP[j][i] == -2) {
				// 빈 칸이면 그냥 패쓰
			}
			else if (MAP[j][i] == -1) { // 벽을 만났다면 
				ind = j - 1; // 다음 블록은 이 벽 바로 위로 떨어진다
			}
			else if (MAP[j][i] >= 0) { // 일반/무지개 블록을 만났다면
				// ind행으로 블록 떨어뜨리기
				// 떨어뜨린후 j행은 -2(빈칸)으로 갱신해줘야 하기 때문에
				// tmp값 사용
				int tmp = MAP[j][i];
				MAP[j][i] = -2;
				MAP[ind][i] = tmp;
				ind--; // 다음 블록은 이 위로 떨어진다
			}
		}
	}
}

// 반시계 90도 회전
void Rotate() {
	int TMP[MAX_N][MAX_N] = { 0, };

	// 인덱스 계산
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			TMP[N - j - 1][i] = MAP[i][j];
		}
	}

	memcpy(MAP, TMP, sizeof(MAP));
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	// solve
	while (1) {
		// 각 턴마다 그룹 생성을 하였는지를 체크해줘야 하기 때문에 매번 초기화 필요
		memset(visited, 0, sizeof(visited));

		int cnt = 0; // 이번 턴에 생성된 그룹의 수
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				// 1. 일반 블록이면서 미방문인 칸을 시작으로 그룹 탐색
				// 각 그룹에 일반 블록이 최소 1개 필요하기 때문에 시작점을 일반 블록으로 잡기
				if (MAP[i][j] > 0 && visited[i][j] == 0) {
					// (i, j) 부터 시작한 그룹 탐색
					// 해당 그룹의 블록 수를 반환
					int tmp = findGroup(i, j);
					if (tmp > 1) cnt++; // 각 그룹에는 최소 2개 이상의 블록이 포함되어야 한다
				}
			}
		}
		if (cnt == 0) break; // 생성된 그룹이 0개라면 종료

		Remove(); // 2. 1에서 찾은 최대 블록 그룹 제거

		Gravity(); // 3. 중력 작용
		Rotate(); // 4. 반시계 90도 회전
		Gravity(); // 5. 중력 작용
	}

	// output
	cout << ans;

	return 0;
}