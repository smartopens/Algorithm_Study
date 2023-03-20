/* 낚시왕 */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define MAX_RC 101
#define DIR_NUM 4

// 상어의 정보
struct shark {
	int r; // 위치
	int c;
	int s; // 속력
	int d; // 방향
	int z; // 크기
};

int rdir[DIR_NUM] = { -1, 0, 1, 0 }; // 상좌하우
int cdir[DIR_NUM] = { 0, -1, 0, 1 };

queue<shark> sharks; // 살아있는 상어들의 정보

int MAP[MAX_RC][MAX_RC]; // 격자판 - 상어의 크기만 저장
int R, C; // R*C 격자판의 크기
int ans; // 낚시왕이 잡은 상어들의 크기의 합

// king열에서 낚시하기
int grab(int king) {
	int ret = -1;

	for (int i = 1; i <= R; i++) {
		// king열에서 땅과 가장 가까운 상어를 찾았다면 해당 열의 ind 반환
		if (MAP[i][king] > 0) {
			ret = i;
			ans += MAP[i][king]; // 잡은 상어의 크기 합하기
			break;
		}
	}

	return ret;
}

// 상어들 이동
// (tr, tc)에 위치한 상어는 방금 잡혔으므로 제거
void move(int tr, int tc) {
	int TMP[MAX_RC][MAX_RC] = { 0, }; // 이번 턴의 이동결과를 기록

	int sz = sharks.size();

	for (int i = 0; i < sz; i++) {
		shark now = sharks.front();
		sharks.pop();
		
		// 방금 잡힌 상어는 더이상의 이동 X
		if (now.r == tr && now.c == tc) continue;

		// 이전의 이동 후 더 큰 상어한테 잡아먹힌 상어 또한 이동 X
		if (MAP[now.r][now.c] > now.z) continue;

		// 살아있는 상어는 이동 O
		int nr = now.r + rdir[now.d] * now.s;
		int nc = now.c + cdir[now.d] * now.s;

		if (now.d % 2 == 0) { // 상하
			// 범위 내에 들 때까지 인덱스 계산
			while (!(nr > 0 && nr <= R)) {
				if (nr <= 0) nr = 2 - nr;
				else if (nr > R) nr = R - (nr - R);

				now.d = (now.d + 2) % DIR_NUM; // 이 안에 들어왔다는 것은 격자를 벗어났다 -> 방향 전환
			}
		}
		else { // 좌우
			// 범위 내에 들 때까지 인덱스 계산
			while (!(nc > 0 && nc <= C)) {
				if (nc <= 0) nc = 2 - nc;
				else if (nc > C) nc = C - (nc - C);

				now.d = (now.d + 2) % DIR_NUM; // 이 안에 들어왔다는 것은 격자를 벗어났다 -> 방향 전환
			}
		}

		// 인덱스 계산하기 싫어서 아래처럼 상어의 이동을 구현하였더니 시간초과 발생,,
		/*int nr = now.r;
		int nc = now.c;
		for (int j = 0; j < now.s; j++) {
			nr += rdir[now.d];
			nc += cdir[now.d];

			if (nr <= 0 || nc <= 0 || nr > R || nc > C) {
				nr -= rdir[now.d];
				nc -= cdir[now.d];

				now.d = (now.d + 2) % DIR_NUM;

				nr += rdir[now.d];
				nc += cdir[now.d];
			}
		}*/

		// 빈 칸 혹은 더 작은 상어가 있는 칸에만 갱신
		if (TMP[nr][nc] < now.z) {
			TMP[nr][nc] = now.z;
			sharks.push({ nr, nc, now.s, now.d, now.z });
		}
	}

	// 이번 턴의 이동결과를 MAP에 저장
	memcpy(MAP, TMP, sizeof(TMP));
}

int main() {
	int M; // 초기 상어의 수
	cin >> R >> C >> M;

	for (int i = 0; i < M; i++) {
		int ir, ic, is, id, iz;
		cin >> ir >> ic >> is >> id >> iz;

		id = id == 1 ? 0 : id == 4 ? 1 : id; // 상좌하우 순으로 변경
		sharks.push({ ir, ic, is, id, iz });
		MAP[ir][ic] = iz;
	}

	int king = 0;

	while (king <= C && sharks.size() > 0) {
		int ind = grab(++king); // (ind, king)의 상어가 잡혔다
		move(ind, king); // 상어들 이동하기
	}

	// output
	cout << ans << '\n';

	return 0;
}