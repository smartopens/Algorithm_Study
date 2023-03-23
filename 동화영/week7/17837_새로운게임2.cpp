/* 새로운 게임 2 */
#include <iostream>
#include <vector>
using namespace std;
#define MAX_N 14 /// MAX_N을 13으로 저장했었어서..... OutOfBounds 발생.......
#define DIR_NUM 4

struct Horse {
	int y; // 위치
	int x;
	int dir; // 이동방향 - 상좌하우
};

int ydir[DIR_NUM] = { -1, 0, 1, 0 }; // 상좌하우
int xdir[DIR_NUM] = { 0, -1, 0, 1 };

vector<Horse> horses; // 말의 정보

// 맨 아래의 말이 vector의 맨 앞에 위치한다고 생각
vector<int> INFO[MAX_N][MAX_N]; // 말들의 위치(ind로 표기, 1~K)
int MAP[MAX_N][MAX_N]; // 체스판의 정보(0:흰, 1:빨, 2:파)
int N, K;

// ind번 말 이동하기
int moveInd(int ind) {
	Horse now = horses[ind];

	// 현 기준으로 ind번 말이 이동한다면 갈 위치 (ny, nx)
	int ny = now.y + ydir[now.dir];
	int nx = now.x + xdir[now.dir];

	if (MAP[ny][nx] == 0) { // 흰색 칸
		// ind번 말이 현재 위치한 칸의 말들을 돌면서
		// ind번 말은 몇 번째에 있는지를 찾기
		int sz = INFO[now.y][now.x].size();
		for (int i = 0; i < sz; i++) {
			if (INFO[now.y][now.x][i] == ind) {
				// i ~ 끝까지 순서대로 (ny, nx)로 이어 붙인다
				for (int j = i; j < sz; j++) {
					int num = INFO[now.y][now.x][j];
					INFO[ny][nx].push_back(num);

					horses[num].y = ny;
					horses[num].x = nx;
				}
				// 기존의 위치에서는 pop해주기
				for (int j = i; j < sz; j++) {
					INFO[now.y][now.x].pop_back();
				}
				break; // 이동시켰다면 완료
			}
		}
		
		if (INFO[ny][nx].size() >= 4) return 4; // 이동한 칸(ny, nx)에 말이 4개 이상이라면 4 반환
	}
	else if (MAP[ny][nx] == 1) { // 빨간색 칸
		int sz = INFO[now.y][now.x].size();
		for (int i = 0; i < sz; i++) {
			if (INFO[now.y][now.x][i] == ind) {
				// i ~ 끝까지의 말을 반대로
				// 즉, 끝 ~ i번까지의 말을 (ny, nx)로 이어 붙인다
				for (int j = sz - 1; j >= i; j--) {
					int num = INFO[now.y][now.x][j];
					INFO[ny][nx].push_back(num);

					horses[num].y = ny;
					horses[num].x = nx;

					// 기존의 위치에서는 pop해주기
					// 여기서는 맨 뒤에서부터 (ny, nx)로 붙이기 때문에
					// for문 안에 pop 써줘도 괜찮다
					INFO[now.y][now.x].pop_back();
				}
				break; // 이동시켰다면 완료
			}
		}

		if (INFO[ny][nx].size() >= 4) return 4; // 이동한 칸(ny, nx)에 말이 4개 이상이라면 4 반환
	}
	else { // 파란색 칸
		horses[ind].dir = (horses[ind].dir + 2) % DIR_NUM; // 방향 반대로 전환

		// 방향 전환 후의 위치
		now = horses[ind];
		ny = now.y + ydir[now.dir];
		nx = now.x + xdir[now.dir];

		// 방향 전환 후에 갈 위치가 파란색 칸이라면 그대로 이동 끝
		// 파란색 칸이 아니라면 ind번 말로 moveInd() 호출 -> 흰|빨간 칸 중 하나이므로
		if (MAP[ny][nx] != 2) {
			if (moveInd(ind) == 4) return 4; // 이동한 칸(ny, nx)에 말이 4개 이상이라면 4 반환
		}
	}

	return 0; // 모든 칸에 위치한 말의 개수가 4개 미만이라면 0 반환 - 즉, 게임 지속 진행 예정
}

// 모든 말을 1번부터 순서대로 이동하기
int moveAll() {
	int sz = horses.size();
	for (int i = 1; i < sz; i++) {
		if (moveInd(i) >= 4) return 1; // 4을 반환받았다면 게임 종료
	}

	return 0; // 한 칸에 4개 이상의 말이 존재하지 않는다면 0 반환 (아직 게임 종료 X)
}

int main() {
	// input
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}

	// 체스판을 벗어나는 경우에도 파란색과 동일하게 동작하므로
	// 체스판을 2로 둘러준다
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			if (i == 0 || i == N + 1 || j == 0 || j == N + 1) MAP[i][j] = 2;
		}
	}

	horses.push_back({ 0,0,0 }); // 빈 값으로 0번 인덱스 채우기 - 인덱스 맞춰주기
	// 말의 정보 저장
	int iy, ix, id;
	for (int i = 1; i <= K; i++) {
		cin >> iy >> ix >> id;
		
		id = id == 1 ? 3 : id == 2 ? 1 : id == 3 ? 0 : 2; // 상좌하우 순으로 dir 변경하여 저장
		horses.push_back({ iy, ix, id });
		INFO[iy][ix].push_back(i); // INFO 체스판에 말 번호 push
	}

	int turn = 1;
	while (turn <= 1000) { // 최대 1000번의 턴
		if(moveAll() == 1) break; // 한 칸에 4개 이상의 말이 있는 경우 탐색 종료

		turn++;
	}

	if (turn > 1000) turn = -1; // 1000번 탐색하였음에도 게임이 끝나지 않았다면 -1 출력
	cout << turn;

	return 0;
}

/*
4 4
2 2 2 2
0 0 0 0
2 2 2 2
0 0 0 0
1 1 3
1 2 3
1 3 3
1 4 3
*/