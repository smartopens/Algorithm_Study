//CodeTree 나무박멸
#include <iostream>
using namespace std;

int dr[8] = { -1, 0, 1, 0, -1, -1, 1, 1 }; //상좌하우 + 대각선4방향
int dc[8] = { 0, -1, 0, 1, 1, -1, -1, 1 };

int REMOVER[20][20]; //제초제 현황 (몇 분까지 유지되는가를 저장)
int MAP[20][20]; //격자의 정보 (-1:벽, 0:빈칸, 1~:나무)
int N, K, C; //N:격자의 사이즈, K:제초제의 전파길이, C:제초제의 유지시간

int timer; //시뮬레이션 소요시간
int removed; //박멸한 총 나무 그루의 수

//1.나무의 성장
void Grow() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] <= 0) continue; //현재 나무가 있는 칸에 한하여

			int cnt = 0;

			for (int k = 0; k < 4; k++) { //4방향 중 나무가 있는 칸의 수만큼 나무가 성장한다
				int nr = i + dr[k];
				int nc = j + dc[k];

				if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
				if (MAP[nr][nc] <= 0) continue;

				cnt++; //인접칸 중 나무 있는 칸을 세기
			}

			MAP[i][j] += cnt; //나무성장
		}
	}
}

//2.나무의 번식
void Spread() {
	int spreaded[20][20] = { 0, }; //이번 년에 번식되는 나무의 그루 수를 저장

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] <= 0) continue; //나무가 있는 칸에 한하여

			bool isSpread[4] = { 0, }; //상좌하우 4방향에 번식이 되는가를 기록
			int cnt = 0; //번식되는 칸의 수
			for (int k = 0; k < 4; k++) {
				int nr = i + dr[k];
				int nc = j + dc[k];

				if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue; //격자 밖은 무시
				if (MAP[nr][nc] != 0) continue; //빈칸이 아니라면 번식 X (즉, 벽이거나 다른 나무가 있거나)
				if (REMOVER[nr][nc] >= timer) continue; //현재 유지되고 있는 제초제가 있다면 번식 X

				isSpread[k] = true; //k방향으로 번식 진행
				cnt++;
			}

			for (int k = 0; k < 4; k++) { //4방향 중 번식되는 칸에 나무의 수를 기록
				if (isSpread[k]) {
					int nr = i + dr[k];
					int nc = j + dc[k];
					spreaded[nr][nc] += MAP[i][j] / cnt; //번식되는 칸으로 나눈만큼
				}
			}
		}
	}

	//번식되는 나무 더하기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MAP[i][j] += spreaded[i][j];
		}
	}
}

//3-1.제초제 최적의 위치 구하기 위한 시뮬레이션
int Simul(int r, int c) {
	if (MAP[r][c] <= 0) return 0; //벽이거나 나무가 없는 칸은 0으로 반환 (더이상 확산 X)

	int cnt = MAP[r][c]; //(r,c)부터 나무 박멸
	for (int i = 4; i < 8; i++) { //대각선 4방향으로
		for (int j = 1; j <= K; j++) { //K길이만큼 확산
			int nr = r + dr[i] * j;
			int nc = c + dc[i] * j;

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
			if (MAP[nr][nc] <= 0) break; //빈칸이거나 벽이면 더이상 확산 X

			cnt += MAP[nr][nc]; //(r,c) 제초제로 박멸되는 나무의 수 증가
		}
	}

	return cnt; //박멸되는 나무의 수를 반환
}

//3.제초제 뿌리기
void Remove() {
	//가장 많은 나무를 박멸하는 최적의 제초제 위치 찾기
	int maxTree = 0, maxR = -1, maxC = -1; //최적의 위치 및 이 때의 나무 박멸 수
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int trees = Simul(i, j); //(i,j)에 제초제를 뿌렸을 때 박멸하는 나무의 수
			if (trees > maxTree) { //최대값 갱신
				maxTree = trees;
				maxR = i;
				maxC = j;
			}
		}
	}

	MAP[maxR][maxC] = 0; //(maxR, maxC)칸에 제초제 뿌리기
	REMOVER[maxR][maxC] = timer + C; //현재(timer)로부터 C년간 제초제 유지
	for (int i = 4; i < 8; i++) {
		for (int j = 1; j <= K; j++) {
			int nr = maxR + dr[i] * j;
			int nc = maxC + dc[i] * j;

			if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;

			REMOVER[nr][nc] = timer + C; //제초제 확산

			if (MAP[nr][nc] > 0) MAP[nr][nc] = 0; //나무가 있는 칸이라면 나무 박멸
			else if (MAP[nr][nc] <= 0) break; //빈칸이거나 벽이라면 더이상 확산 X
		}
	}

	removed += maxTree; //박멸한 총 나무의 수 증가
}

int main() {
	//input
	int M;
	cin >> N >> M >> K >> C;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	//M년동안 시뮬레이션 진행
	for (int i = 1; i <= M; i++) {
		timer++; //제초제의 유지시간 비교를 위한 타이머 작동
		Grow(); //1.나무성장
		Spread(); //2.나무번식
		Remove(); //3.제초제 뿌리기
	}

	//output - 박멸한 총 나무의 그루 수
	cout << removed << "\n";

	return 0;
}