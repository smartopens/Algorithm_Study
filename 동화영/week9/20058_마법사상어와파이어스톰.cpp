/* 마법사 상어와 파이어스톰 */
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
#define MAX_N 64
#define DIR_NUM 4

int rdir[DIR_NUM] = { -1, 1, 0, 0 };
int cdir[DIR_NUM] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N]; // 격자
int N; // 격자의 실사이즈 N*N

int visited[MAX_N][MAX_N]; // 최종 출력 답 구할 때 사용
int sum; // 최종으로 남아있는 얼음의 총 합

// 부분 격자를 시계방향으로 90도 회전
void rotate(int lev) {
	int level = pow(2, lev); // 부분 격자의 실사이즈
	int TMP[MAX_N][MAX_N] = { 0, }; // 회전한 결과를 저장할 배열

	// 모든 칸에 대해 부분격자로 쪼갠다면 각 칸은 (indR, indC) 그룹에 있다
	// 따라서 (indR, indC) 그룹 내에서 회전이 일어난다 => indR*level과 indC*level의 존재 이유 => TMP[indR * level][indC * level]
	// MAP (0, 0) (0, 1) (0,2) (0,3) -> TMP (0,3) (1,3) (2,3) (3,3)으로 이동 => 행->열, 열->행 과 관련 => TMP[j][i]
	// (indR, indC) 그룹 처리를 해줬기 때문에 각 칸의 실제 인덱스를 %(나머지) 연산하여 몇 번째인지만을 고려 => TMP[j % level][i % level]
	// TMP의 열은 MAP의 행을 level 기준으로 보수처리해야한다 => TMP[][level -1 - i]
	// 위의 고려사항들을 합한다면 아래의 인덱스 계산이 나온다
	for (int i = 0; i < N; i++) {
		int indR = i / level;
		for (int j = 0; j < N; j++) {
			int indC = j / level;
			TMP[indR * level + j % level][indC * level + level - 1 - i % level] = MAP[i][j];
		}
	}

	memcpy(MAP, TMP, sizeof(MAP)); // 회전한 결과를 MAP으로 복사
}

// 주변에 얼음이 있는 칸이 3칸 미만 시
// 해당 칸의 얼음 줄어들기 -1
void shrink() {
	int tmp[MAX_N][MAX_N] = { 0, }; // 얼음이 줄어들 칸 표기용

	// 모든 칸에 대해 탐색한다
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] == 0) continue; // 현재 칸에 이미 얼음이 0이라면 탐색 X

			// 4방향 탐색하며 주변에 얼음이 있다면 ice 증가해서 표기하기
			int ice = 0;
			for (int k = 0; k < DIR_NUM; k++) {
				int nr = i + rdir[k];
				int nc = j + cdir[k];

				if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; // 격자 밖은 무시
				if (MAP[nr][nc] == 0) continue; // 주변에 얼음이 0인 칸은 ice 증가 X

				ice++;
			}
			if (ice < 3) tmp[i][j] -= 1; // 얼음 줄어드는 칸 표기
		}
	}

	// 얼음이 줄어든다면 줄어드는 정도만큼 합쳐주기(-1)
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (tmp[i][j] != 0) MAP[i][j] += tmp[i][j];
}

// 최종 남아있는 얼음들 중 가장 큰 덩어리 찾기
int bfs(int r, int c) {
	int cnt = 0; // 덩어리의 칸 수

	// (r, c)부터 탐색 시작
	queue<pair<int, int>> q;
	q.push({ r, c });
	visited[r][c] = 1; // 방문 처리
	cnt++; // 덩어리의 칸 수 ++
	sum += MAP[r][c]; // 남아있는 얼음의 양도 더해주기

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int nr = now.first + rdir[i];
			int nc = now.second + cdir[i];

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; // 격자 밖은 무시
			if (visited[nr][nc] == 1) continue; // 이미 방문한 칸은 무시
			if (MAP[nr][nc] == 0) continue; // 얼음이 0이라면 탐색 X

			// 다음 탐색할 칸에 대한 처리
			q.push({ nr, nc });
			visited[nr][nc] = 1; // 방문 처리
			cnt++; // 덩어리의 칸 수 ++
			sum += MAP[nr][nc]; // 남아있는 얼음의 양도 더해주기
		}
	}

	return cnt;
}

int main() {
	 // input
	int szN, Q; // szN : 격자 사이즈(2^szN) Q : 파이어스톰 횟수
	cin >> szN >> Q;

	N = pow(2, szN); // 격자의 실사이즈
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	// 각 시전마다의 level로 회전과 얼음 줄어들기를 반복 수행
	int level;
	for (int i = 0; i < Q; i++) {
		cin >> level;

		rotate(level);
		shrink();
	}

	int cnt = 0; // 얼음 덩어리
	int ans = 0; // 가장 큰 얼음 덩어리
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// (i,j)에 얼음이 있으면서 아직 방문하지 않았다면 bfs 탐색
			// 반환받은 cnt(덩어리의 칸 수)와 ans를 비교하여 갱신
			if (MAP[i][j] > 0 && visited[i][j] == 0) {
				cnt = bfs(i, j);
				if (ans < cnt) ans = cnt;
			}
		}
	}

	cout << sum << "\n" << ans << "\n";

	return 0;
}