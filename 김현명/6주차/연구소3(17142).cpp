#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

// 연구소 지역 설정
int n, m;
int board[50][50];
int visited[50][50];

// 방향 설정
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

// 최소 시간 선언하기
// 퍼뜨릴 곳의 수: b_num
// 바이러스 수: v_num
int min_time = 21e8;
int b_num;
int v_num;

struct node {
	int r;
	int c;
};

// 바이러스 경우, 조합의 경우 지정
node virus[2500];
int possible[10];

// 바이러스를 퍼뜨린다.
// 이 때, 바이러스들이 동시에 퍼뜨리게 한다.
// queue에 담아서 1초마다 같이 퍼뜨리게 한다.
void extend() {

	int time = 0;
	int t_num = b_num;
	queue<node> q = {};

	// 시간 갱신
	if (t_num == 0) {
		if (time < min_time) min_time = time;
		return;
	}

	// 처음 바이러스 저장
	for (int i = 0; i < 10; i++) {
		if (possible[i] == 0) continue;
		int r, c;
		r = virus[i].r;
		c = virus[i].c;

		q.push({ r, c });
		visited[r][c] = 1;
	}

	// 바이러스 퍼뜨리기
	while (!q.empty()) {
		int q_size = q.size();
		time += 1;

		for (int s = 0; s < q_size; s++) {
			node now = q.front();
			q.pop();
			
			int r, c, nr, nc;
			r = now.r;
			c = now.c;

			// 벽이면 못지나간다.
			// 퍼뜨릴 장소에 도착했다면 t_num 갱신한다.
			// 모든 장소에 도착했다면 시간 갱신하고 종료한다.
			for (int i = 0; i < 4; i++) {
				nr = r + dr[i];
				nc = c + dc[i];
				
				if (0 > nr || nr >= n || 0 > nc || nc >= n) continue;
				if (board[nr][nc] == 1) continue;
				if (visited[nr][nc] != 0) continue;

				if (board[nr][nc] == 0) t_num -= 1;

				if (t_num == 0) {
					if (time < min_time) min_time = time;

					return;
				}
				
				visited[nr][nc] = visited[r][c] + 1;
				q.push({ nr,nc });
			}
		}
	}

	return;
}

void count_case(int a, int idx) {
	// 바이러스 경우 완성
	// 바이러스 퍼뜨리면서 시간 갱신하기
	if (a >= m) {
		memset(visited, 0, sizeof(visited));
		extend();

		return;
	}

	// 경우의 수 만들기
	for (int i = idx; i < v_num; i++) {
		possible[i] = 1;
		count_case(a + 1, i + 1);
		possible[i] = 0;
	}

	return;
}

int main() {

	cin >> n >> m;

	// 연구소 정보 입력받기
	// b_num 세기
	// 바이러스 위치 저장하기
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			cin >> board[r][c];

			if (board[r][c] == 0) b_num += 1;
			else if (board[r][c] == 2) {
				virus[v_num] = { r,c };
				v_num += 1;
			}

		}
	}

	// 바이러스를 퍼뜨릴 장소 경우를 고려한다.
	count_case(0, 0);

	// 최소 시간 출력하기
	if (min_time != 21e8) {
		cout << min_time << endl;
	}
	else if (min_time == 21e8) {
		cout << -1 << endl;
	}

	return 0;
}