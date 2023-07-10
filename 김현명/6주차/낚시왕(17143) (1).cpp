#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

// 바다 지역 정보
// 상어 id로 관리한다.
int n, m, k;
int sea[100][100];

// 상어들 정보
// 상어속력, 방향, 크기가 있다.
// 상어 id와 연결되는 자료구조
struct node {
	int s_vel;
	int s_dir;
	int s_size;
};

node sharks[100001];

// 상어 방향
// 위 아래 오른쪽 왼쪽
// 벽에 부딪히는 경우 반대방향으로 이동
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };
int c_dir[4] = { 1,0,3,2 };

// 잡은 상어 수
int get_s_size;

// 상어 이동하기
// new_sea영역에 상어의 이동 결과를 담는다.
// 이동 후 sea영역을 복구한다.
void move_shark() {
	int new_sea[100][100] = { {} };

	// 상어가 있는 경우
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			if (sea[r][c] > 0) {
				int move;

				int dir;
				int nr = r;
				int nc = c;

				// 현재 상어방향, 이동 정도 설정
				dir = sharks[sea[r][c]].s_dir;
				move = sharks[sea[r][c]].s_vel;

				// 상어 행 방향으로 이동
				// 상어가 원래 지점으로 오는 경우를 기준으로 이동 거리를 설정한다.
				// 상어의 최대 이동거리는 벽에 부딪혀서 처음 위치로 오는 경우이다.
				// 위 거리로 이동 중 부딪힐 경우 위치와 방향을 갱신 한다.
				if (dir == 0 || dir == 1) {
					move %= 2 * (n - 1);

					for (int i = 0; i < move; i++) {
						nr += dr[dir];

						if (nr > n - 1)
						{
							nr = n - 2;
							dir = c_dir[dir];
						}
						else if (nr < 0)
						{
							nr = 1;
							dir = c_dir[dir];
						}
					}
				}
				// 상어 열 방향으로 이동
				// 상어가 원래 지점으로 오는 경우를 기준으로 이동 거리를 설정한다.
				// 상어의 최대 이동거리는 벽에 부딪혀서 처음 위치로 오는 경우이다.
				// 위 거리로 이동 중 부딪힐 경우 위치와 방향을 갱신 한다.
				else if (dir == 2 || dir == 3) {
					move %= 2 * (m - 1);

					for (int i = 0; i < move; i++) {
						nc += dc[dir];

						if (nc > m - 1)
						{
							nc = m - 2;
							dir = c_dir[dir];
						}
						else if (nc < 0)
						{
							nc = 1;
							dir = c_dir[dir];
						}
					}
				}

				// 방향 갱신
				sharks[sea[r][c]].s_dir = dir;

				// 상어가 여러마리 있을 경우
				// 가장 큰 상어만 남는다.
				if (new_sea[nr][nc] > 0) {
					int ori_size = sharks[new_sea[nr][nc]].s_size;
					int now_size = sharks[sea[r][c]].s_size;

					if (now_size > ori_size) {
						new_sea[nr][nc] = sea[r][c];
					}
				}
				else {
					new_sea[nr][nc] = sea[r][c];
				}
			}
		}
	}

	// 원래 바다 정보 복구
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			sea[r][c] = new_sea[r][c];
		}
	}

}

// 왕이 상어를 잡게 하기
// 상어를 잡는 경우 점수 갱신하고 끝난다.
void get_shark(int sc) {
	int nc;
	nc = sc;

	for (int nr = 0; nr < n; nr++) {
		if (sea[nr][nc] > 0) {
			int s_id = sea[nr][nc];
			get_s_size += sharks[s_id].s_size;

			sea[nr][nc] = 0;
			return;
		}
	}
}

int main() {
	cin >> n >> m >> k;

	// 상어 정보를 입력받는다.
	// id로 관리한다.
	int s_id = 1;
	for (int i = 0; i < k; i++) {
		// 위치, 속력, 방향, 크기
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;

		// 문제 조건 맞추기
		r -= 1;
		c -= 1;
		d -= 1;

		// id를 저장한다
		// id에 맞게 상어 정보 입력하기
		sea[r][c] = s_id;
		sharks[s_id] = { s,d,z};
		s_id += 1;
	}

	// 왕이 한칸씩 이동한다.
	// 위에서 가장 가까운 상어를 잡는다.
	// 왕이 이동한 후 상어 이동하기
	for (int sc = 0; sc < m; sc++) {
		get_shark(sc);
		move_shark();
	}

	cout << get_s_size << endl;

	return 0;
}