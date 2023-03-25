/* 원판 돌리기 */
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
using pii = pair<int, int>;
//#define MAX_N 51
const int MAX_N = 51;

int rdir[] = { -1, 1, 0, 0 }; // 상하좌우
int cdir[] = { 0, 0, -1, 1 };

int MAP[MAX_N][MAX_N * 2];
int INDEX[MAX_N]; // 각 원판의 시작 인덱스
int N, M; // N: 원판의 개수, M: 원판 내 숫자의 개수

int sum; // 원판에 적힌 수의 합 (답)
int alive; // 현재 살아있는 수의 개수

// 원판 회전하기
void rotate(int x, int d, int k) {
	for (int i = 1; i <= N; i++) { // 전체 N개의 원판에 대해 조건 확인
		if (i%x != 0) continue; // 회전할 원판이 아니라면 무시

		// 시계방향 - ind -1
		// 반시계방향 - ind + 1
		if (d == 0) INDEX[i] = (INDEX[i] - k + M) % M; // 시계방향은 인덱스가 --되는데 음수가 될 것을 방지하려 +M 처리 -> 이 때 M을 넘을 수도 있으니 %M
		else INDEX[i] = (INDEX[i] + k) % M; // 반시계방향은 인덱스가 ++되는데 M 이상이 될 것을 방지하려 %M 처리
	}
}

void Remove() {
	queue<pii> q; // 인접한 칸에 동일한 수가 있는 것을 찾기 위한 queue 준비
	bool isSame = false; // 이번 턴에 동일한 숫자를 찾았는가? 를 저장
	int target = 0; // 동일 숫자를 탐색하기 시작하는 칸의 숫자

	// 원판의 전체 숫자를 돌면서 탐색한다 -> visited를 활용한다면 시간을 더 줄일 수 있을 것 같지만 아래에서는 적용하지 않았다
	for (int i = 1; i <= N; i++) { // N개의 원판
		for (int j = 0; j < M; j++) { // 각 원판 내 M개의 숫자
			int nj = (j + INDEX[i]) % M; // 각 원판에서 현재 시작지점인 인덱스를 기준으로 j열 다시 계산
			if (MAP[i][nj] == 0) continue; // 이미 제거된 숫자라면 무시

			// 동일한 숫자 찾으러 시작!
			q.push({ i,nj });
			target = MAP[i][nj]; // 지금 찾고있는 숫자
			int cnt = 0; // 인접 칸 중 동일한 숫자의 개수 (단, 시작지점은 제외)

			while (!q.empty()) {
				pii now = q.front(); // target의 숫자인 칸들이며, 여기서부터 다시 인접 칸을 탐색
				q.pop();

				// 상 - 바로 안쪽의 원판
				// 하 - 바로 바깥쪽의 원판
				// 좌 - 동일 원판 내 바로 반시계 방향 옆의 숫자
				// 우 - 동일 원판 내 바로 시계 방향 옆의 숫자
				for (int k = 0; k < 4; k++) {
					int nr = now.first + rdir[k];
					// now 원판과 new 원판의 인덱스까지 고려해야 하므로 다소 복잡,,
					// now.second + cdir[k] -> 인접 칸의 인덱스
					// M - INDEX[now.first] -> now의 시작지점 INDEX를 기준으로 시작한다면 현재 now는 몇 번 째 칸에 있는 것인가?
					// + INDEX[nr] -> now가 현재 위치한 칸과 동일한 칸에 있는 new 원판의 칸은? -> new 원판의 시작지점 INDEX로 찾는다
					int nc = (now.second + (M - INDEX[now.first]) + cdir[k] + INDEX[nr]) % M;

					if (nc == -1) nc = M - 1; // 0번 열의 좌를 찾을 때 인덱스 정정
					if (nr <= 0 || nr > N) continue; // 원판을 벗어난다면 무시 - nc는 위에서 인덱스 처리해주므로 여기서는 확인할 필요 X
					if (nr == i && nc == nj) continue; // 시작지점은 제외

					// 현재 찾고있는 target의 숫자와 동일한 칸이라면
					if (MAP[nr][nc] == target) {
						q.push({ nr, nc }); // queue에 추가
						cnt++; // target 숫자 하나 더 찾았다!

						// 이 숫자는 이제 삭제한다
						sum -= MAP[nr][nc]; // 원판 내 숫자의 총 합에서 제거 처리
						MAP[nr][nc] = 0; // 원판의 숫자 제거 처리
						MAP[nr][nc + M] = 0; // 옆에 붙어있는 숫자도 처리
						alive--; // 현재 살아있는 숫자의 개수에서 제거 처리
					}
				}
			}

			// target과 동일한 숫자를 하나라도 찾았다면
			// 시작지점에 대해서도 제거 처리
			if (cnt > 0) {
				sum -= MAP[i][nj];
				MAP[i][nj] = 0;
				MAP[i][nj + M] = 0;
				alive--;
				isSame = true; // 이번 턴에서 동일한 숫자 찾아서 제거했다!라고 표기
			}
		}
	}

	if (alive == 0) return; // 현재 살아있는 숫자가 0개라면 끝

	// 이번 턴에 동일한 숫자를 찾아서 제거하지 못했다면
	// 남아있는 숫자들의 평균에 따라 각 칸을 처리
	// 평균보다 크다면 -1, 평균보다 작다면 +1 (평균은 소수점)
	// 평균과 동일하다면 무시
	if (!isSame) {
		float num = (float) sum / alive; // 평균은 소수점까지 계산

		// 원판 내 모든 숫자를 돌면서 비교 및 처리
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {
				if (MAP[i][j] == 0) continue; // 제거된 칸이라면 무시
				else if (MAP[i][j] > num) { // 평균보다 크다면
					// -1 처리
					MAP[i][j]--;
					MAP[i][j + M]--;
					sum--;
				}
				else if (MAP[i][j] < num) { // 평균보다 작다면
					// +1 처리
					MAP[i][j]++;
					MAP[i][j + M]++;
					sum++;
				}

				// 처리한 후 0이 되었다면 (즉, 1이었던 칸이 평균보다 커서 -1 처리했다면 0이 되었다)
				// 숫자 하나 제거되었다는 처리
				if (MAP[i][j] == 0) alive--;
			}
		}
	}
}

int main() {
	// input
	int T;
	cin >> N >> M >> T;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			MAP[i][j + M] = MAP[i][j]; // 뒤에 한 줄 더 이어주기
			sum += MAP[i][j]; // 숫자들의 총 합
		}
	}
	alive = N * M; // 살아있는 수의 개수 (즉, 0이 아닌 수의 개수)

	int x, d, k; // 입력받을 회전의 정보 - (x의 배수인 원판을 d방향으로 k칸 회전시킨다)
	for (int i = 0; i < T; i++) {
		cin >> x >> d >> k; // d - 0:시계방향, 1:반시계방향
		rotate(x, d, k); // 해당하는 원판들 회전
		Remove(); // 숫자들 제거
		if (alive == 0) break; // 이미 모든 수들이 사라졌다면(0이 되었다면) 끝낸다
	}

	// output
	cout << sum;

	return 0;
}