#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int n;

// 물고기 정보, 상어 정보 설정
struct node {
	int f_id;
	int r;
	int c;
	int dir;
	bool live;
};

struct s_node {
	int r;
	int c;
	int dir;
};

// 바다지역 설정
int sea[20][20];
node fishes[20];
s_node shark;

// 상 우상 우 >> 8가지 방향
int dr[8] = { -1,-1,0,1,1,1,0,-1 };
int dc[8] = { 0,-1,-1,-1,0,1,1,1 };

int max_f_num;

void go_fish() {
	for (int i = 1; i < n * n + 1; i++) {

		int r, c, dir;
		int nr, nc, n_dir;
		node now = fishes[i];

		r = now.r;
		c = now.c;
		dir = now.dir;

		if (now.live == false) continue;

		for (int s = 0; s < 8; s++) {
			int n_dir = (dir + s) % 8;
			nr = r + dr[n_dir];
			nc = c + dc[n_dir];

			if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
			if (sea[nr][nc] == 20) continue;
			
			node next = fishes[sea[nr][nc]];
			int now_id = now.f_id;
			int next_id = next.f_id;

			if (sea[nr][nc] > 0) {
				sea[nr][nc] = now_id;
				sea[r][c] = next_id;

				fishes[next_id].r = now.r;
				fishes[next_id].c = now.c;
				fishes[now_id].r = nr;
				fishes[now_id].c = nc;
			}
			else {
				fishes[now_id].r = nr;
				fishes[now_id].c = nc;
				sea[nr][nc] = now_id;
				sea[r][c] = 0;
			}

			fishes[now_id].dir = n_dir;
			break;
		}


	}


};

// 물고기가 움직이고 상어를 움직인다.
// 이 때, 변하는 바다의 정보와 물고기의 정보들을 생각한다.
// 다음 분기점으로 갔다오고 난 후, 원래 정보들을 복구한다.
void go_shark(int f_num) {
	// 물고기 움직이기
	go_fish();

	// 원래 정보 기록
	int ori_sea[20][20] = { {} };
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			ori_sea[r][c] = sea[r][c];
		}
	}

	node ori_fishes[20] = {};
	for (int i = 0; i < 20; i++) {
		ori_fishes[i] = fishes[i];
	}

	int sr, sc, dir;
	int s_id;

	// 현재 상어 정보
	sr = shark.r;
	sc = shark.c;
	dir = shark.dir;
	
	// 물고기 수 갱신
	if (f_num > max_f_num) {
		max_f_num = f_num;
	}

	int nr, nc;

	// 상어 이동
	// 거리1, 거리2, 거리3에 맞게 이동한다.
	// 물고기가 있는곳으로 이동 가능하다.
	for (int s = 1; s < n; s++) {
		nr = sr + dr[dir] * s;
		nc = sc + dc[dir] * s;

		if (0 > nr || n <= nr || 0 > nc || n <= nc) break;
		if (sea[nr][nc] == 0) continue;

		// 상어 이동
		// 바다 정보 갱신하기
		// 잡힌 물고기 기록하기
		
		int n_id = sea[nr][nc];
		shark.r = nr;
		shark.c = nc;
		shark.dir = fishes[n_id].dir;

		sea[sr][sc] = 0;
		sea[nr][nc] = 20;

		fishes[n_id].live = false;

		go_shark(f_num + n_id);


		// 분기점을 돌아오는 경우
		// 잡힌 물고기, 바다 정보, 상어 정보를 복구한다.

		fishes[n_id].live = true;
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				sea[r][c] = ori_sea[r][c];
			}
		}

		for (int i = 0; i < 20; i++) {
			fishes[i] = ori_fishes[i];
		}

		shark.dir = dir;
		shark.c = sc;
		shark.r = sr;

	}
};


int main() {
	// 바다 크기, 물고기 먹이 수
	n = 4;
	int f_num = 0;

	// 상어와 바다정보 입력받기
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			int id, dir;
			cin >> id;
			cin >> dir;
			dir -= 1;

			// 상어 정보 갱신, 맵에 표시하기
			if (r == 0 && c == 0) {
				shark = { 0,0, dir };
				f_num += id;
				sea[r][c] = 20;
				continue;
			}

			// 물고기 정보 갱신, 맵에 표시하기
			fishes[id] = { id,r,c,dir,true };
			sea[r][c] = id;
		}
	}

	// 상어 출발
	go_shark(f_num);

	cout << max_f_num << endl;

	return 0;
}