/* 컨베이어 벨트 위의 로봇 */
#include <iostream>
#include <queue>
using namespace std;
const int MAX_N = 201;

// 모든 정보는 시작지점의 1~2*N 칸에서 변경하지 않는다
// 현재 올리는 위치와 내리는 위치가 어디인가만 변경해준다
// 즉, 컨베이어 벨트 자체는 미동이며 회전할 때마다 올리는/내리는 위치가 반시계로 돈다고 생각

queue<int> robots; // 로봇들이 위치한 칸
int used[MAX_N]; // 현재 각 칸에 로봇이 위치해있는가
int MAP[MAX_N]; // 각 칸의 내구도
int N, K; // N: 컨베이어 벨트의 길이, K: 내구도 0인 칸의 제한
int cnt; // 내구도가 0인 칸의 개수

int enterInd, exitInd; // 현재 올리는 위치와 내리는 위치를 가리키는 인덱스

// 1. 컨베이어 벨트가 통째로 회전
// 컨베이어가 시계방향 회전 -> 컨베이어는 고정 -> 아래판이 반시계로 회전한다고 생각
void rotate() {
	enterInd--;
	exitInd--;

	// 1번 다음은 2*N을 가리킬 수 있게끔
	if (enterInd == 0) enterInd = 2 * N;
	if (exitInd == 0) exitInd = 2 * N;
}

// 2. 각 로봇의 순차 이동
void move() {
	// 로봇의 수만큼 이동 가능 여부 확인 및 이동 처리
	int sz = robots.size();
	for (int i = 0; i < sz; i++) {
		int now = robots.front();
		robots.pop();

		// 직전의 컨베이어 회전으로 인해 내리는 위치에 온 로봇이라면
		// 바로 내린다
		if (now == exitInd) {
			used[now] = 0;
			continue;
		}

		// 이동하려는 칸에 로봇이 없고 내구도가 1 이상이라면 이동한다
		int tmp = now + 1 > 2 * N ? 1 : now + 1;
		if (used[tmp] == 0 && MAP[tmp] > 0) {
			used[now] = 0; // 기존 칸 used 비워주기
			now = tmp; // 이동 처리
			used[now] = 1; // used 갱신
			MAP[now]--; // 새로운 칸의 내구도 --
			if (MAP[now] == 0) cnt++; // 방금 이동으로 인해 해당 칸의 내구도가 0이 되었다면 cnt++

			if (now == exitInd) { // 이동해왔더니 내리는 위치라면 내리기
				used[now] = 0; // used 비워주기
				continue;
			}
		}

		// 이동했다면 새로운 칸을 push할 것이고
		// 이동하지 못했다면 기존의 칸이 다시 push될 것이다
		robots.push(now);
	}
}

void add() {
	// 올리는 위치에 로봇을 올릴 때는 used를 확인하지 않는다 (조건에 명시 X)
	if (MAP[enterInd] > 0) { // 내구도가 1이상이라면 로봇 추가
		used[enterInd] = 1; // used 갱신
		MAP[enterInd]--; // 올리는 위치의 내구도 --
		if (MAP[enterInd] == 0) cnt++; // 방금 추가로 인해 내구도가 0인 되었다면 cnt++
		robots.push(enterInd); // 로봇들의 위치에 추가해주기
	}
}

int main() {
	// input
	cin >> N >> K;
	for (int i = 1; i <= 2 * N; i++) {
		cin >> MAP[i];
	}

	int lev = 0; // 몇 번째 턴
	cnt = 0; // 초기에는 전체 칸의 내구도가 1 이상
	enterInd = 1, exitInd = N; // 초기에는 1과 N이 올리는 위치/내리는 위치
	while (cnt < K) { // 내구도가 0인 칸이 K개가 된다면 종료
		rotate(); // 1. 컨베이어 벨트가 통째로 회전
		move(); // 2. 각 로봇의 순차 이동
		add(); // 3. 올리는 위치에 로봇 추가
		lev++; // 턴++
	}

	// output
	cout << lev;

	return 0;
}