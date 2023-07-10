#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>

using namespace std;

// 체스판 선언 : board
// 실제 말 이동 지역: board_id
int n, k;
int board[20][20];

vector<int> board_id[20][20];

// 말들의 위치, 방향 정보: dolls
struct node {
	int r;
	int c;
	int di;
};

node dolls[400];

// 방향 설정
int dr[4] = { 0,0,-1,1 };
int dc[4] = { 1,-1,0,0 };
int c_di[4] = { 1,0,3,2 };

// 체스 종료 조건
bool is_ok = false;

// 말들 이동하기
// 1번부터 k번까지 말들을 이동시킨다.
// 말들의 다음번 이동 지역 색깔에 따라서 행동을 설정한다.

void doll_go() {
	
	for (int id = 1; id < k + 1; id++) {
		// 현재 말 정보
		int r, c, di;

		// 다음번 말 정보
		int nr, nc, n_di;

		r = dolls[id].r;
		c = dolls[id].c;
		di = dolls[id].di;

		nr = r + dr[di];
		nc = c + dc[di];
		n_di = di;

		// 흰칸으로 이동하기
		if (board[nr][nc] == 0) {

			// 말 이동시 해당 id말부터 위로 쌓인 말들이 같이 이동한다.
			// 고로, 이동되는 말들과 이동하지 않는 말들을 생각한다.
			bool d_s = false;
			vector<int> ori_tmp = {};
			vector<int> n_tmp = {};

			for (int i = 0; i < board_id[r][c].size(); i++) {
				if (board_id[r][c][i] == id) d_s = true;

				if (d_s == false)
				{
					ori_tmp.push_back({ board_id[r][c][i] });
				}
				else if (d_s == true)
				{
					n_tmp.push_back({ board_id[r][c][i] });
				}
			}
			// 다음 지역에 말들을 이동시키기
			vector<int> n_ori_tmp = board_id[nr][nc];
			for (int i = 0; i < n_tmp.size(); i++) {
				n_ori_tmp.push_back(n_tmp[i]);
			}

			// 말 이동 정보 갱신
			board_id[nr][nc] = n_ori_tmp;
			board_id[r][c] = ori_tmp;

			// 같이 이동되는 말들의 정보를 갱신한다.
			for (int i = 0; i < n_tmp.size(); i++) {
				int n_id = n_tmp[i];
				dolls[n_id].r = nr;
				dolls[n_id].c = nc;
			}

			// 체스 종료 조건
			if (n_ori_tmp.size() >= 4) {
				is_ok = true;
				return;
			}
		}

		// 말 이동시 해당 id말부터 위로 쌓인 말들이 같이 이동한다.
		// 빨강지역이므로 뒤집어서 이동한다.
		else if (board[nr][nc] == 1) {
			bool d_s = false;
			vector<int> ori_tmp = {};
			vector<int> n_tmp = {};

			for (int i = 0; i < board_id[r][c].size(); i++) {
				if (board_id[r][c][i] == id) d_s = true;

				if (d_s == false)
				{
					ori_tmp.push_back({ board_id[r][c][i] });
				}
				else if (d_s == true)
				{
					n_tmp.push_back({ board_id[r][c][i] });
				}
			}

			// 다음 지역에 말들을 이동시키기
			vector<int> n_ori_tmp = board_id[nr][nc];
			int n_size = n_tmp.size();
			for (int i = 0; i < n_size; i++) {
				n_ori_tmp.push_back(n_tmp[n_size-1-i]);
			}

			// 말 이동 정보 갱신
			board_id[nr][nc] = n_ori_tmp;
			board_id[r][c] = ori_tmp;


			// 같이 이동되는 말들의 정보를 갱신한다.
			for (int i = 0; i < n_tmp.size(); i++) {
				int n_id = n_tmp[i];
				dolls[n_id].r = nr;
				dolls[n_id].c = nc;
			}

			// 체스 종료 조건
			if (n_ori_tmp.size() >= 4) {
				is_ok = true;
				return;
			}
		}

		// 말 이동시 해당 id말부터 위로 쌓인 말들이 같이 이동한다.
		// 파랑지역임을 유의하자.
		// 말의 방향정보가 갱신된다. 이 후, 원래 위치부터 갱신된 방향으로 이동을 고려한다.
		// 이 때, 다음 이동방향의 색깔정보 역시 고려해준다.
		else if (board[nr][nc] == 2) {
			bool d_s = false;
			vector<int> ori_tmp = {};
			vector<int> n_tmp = {};

			for (int i = 0; i < board_id[r][c].size(); i++) {
				if (board_id[r][c][i] == id) d_s = true;

				if (d_s == false)
				{
					ori_tmp.push_back({ board_id[r][c][i] });
				}
				else if (d_s == true)
				{
					n_tmp.push_back({ board_id[r][c][i] });
				}
			}

			// 방향정보, 다음 이동 위치 고려하기
			n_di = c_di[di];
			nr = r + dr[n_di];
			nc = c + dc[n_di];

			// 다음 지역에 말들을 이동시키기
			// 이 때 해당 지역의 색깔을 고려한다.
			// 파랑인 경우
			if (board[nr][nc] == 2) {
				nr = r;
				nc = c;
			}
			else {
				vector<int> n_ori_tmp = board_id[nr][nc];

				// 흰색과 빨강지역 고려하기
				if (board[nr][nc] == 0) {
					for (int i = 0; i < n_tmp.size(); i++) {
						n_ori_tmp.push_back(n_tmp[i]);
					}

				}
				else if (board[nr][nc] == 1) {
					int n_size = n_tmp.size();
					for (int i = 0; i < n_size; i++) {
						n_ori_tmp.push_back(n_tmp[n_size - 1 - i]);
					}
				}
				// 말 이동 정보 갱신
				board_id[nr][nc] = n_ori_tmp;
				board_id[r][c] = ori_tmp;

				// 같이 이동되는 말들의 정보를 갱신한다.
				for (int i = 0; i < n_tmp.size(); i++) {
					int n_id = n_tmp[i];
					dolls[n_id].r = nr;
					dolls[n_id].c = nc;
				}
				// 체스 종료 조건
				if (n_ori_tmp.size() >= 4) {
					is_ok = true;
					return;
				}


			}
		}

		dolls[id].di = n_di;
	}
}

int main() {

	cin >> n >> k;

	// 체스 경계 설정
	// 행
	for (int r = 0; r < n + 2; r++) {
		board[r][0] = 2;
		board[r][n + 1] = 2;
	}

	// 열
	for (int c = 0; c < n + 2; c++) {
		board[0][c] = 2;
		board[n + 1][c] = 2;
	}

	// 체스판 정보 입력
	for (int r = 1; r < n + 1; r++) {
		for (int c = 1; c < n + 1; c++) {
			int num;
			cin >> num;
			board[r][c] = num;
		}
	}

	// 말들 정보 입력 : dolls
	// 말의 이동 정보 입력 : board_id
	for (int id = 1; id < k + 1; id++) {
		int r, c, di;
		cin >> r >> c >> di;

		di -= 1;

		dolls[id] = { r,c,di };
		board_id[r][c].push_back(id);
	}

	// 게임 진행하기
	int turn = 1;

	while (turn <= 1000) {
		// 말들 이동하기
		doll_go();

		// 말이 4칸 이상 쌓인 경우
		if (is_ok == true) break;
		turn += 1;
	}

	if (turn > 1000) cout << -1 << endl;
	else cout << turn << endl;

	return 0;
}