#include <iostream>
using namespace std;

// 방향 배열
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int MAP[102][102]; // 격자 내 도미노의 높이 정보
char visited[102][102]; // 격자 내 도미노가 넘어졌는지 여부 저장
int  N, M; // N*M 격자의 사이즈

// 1. 공격
int Attack() {
	// 각 라운드의 공격 정보
	int x, y;
	char d;
	cin >> x >> y >> d;

	int cnt = 0; // 각 라운드에 공격수가 쓰러뜨린 도미노의 개수 - 반환값

	int dir = d == 'E' ? 0 : d == 'W' ? 1 : d == 'S' ? 2 : 3; // 각 라운드의 공격 방향
	int len = MAP[x][y]; // 앞으로 쓰러뜨릴 수 있는 도미노의 남은 개수
	while (len > 0) {
		if (x <= 0 || y <= 0 || x > N || y > M) break; // 격자 밖에 도달했다면 더이상 진행 X

		// 도달한 격자의 도미노가 서있는 상태라면
		// 1) 이번 라운드의 공격점수 획득
		// 2) 해당 격자의 도미노 넘어진 상태로 저장
		// 3) 남은 개수보다 현재 칸의 도미노 높이가 더 높다면 갱신
		if (visited[x][y] == 'S') {
			cnt++;
			visited[x][y] = 'F';
			if (MAP[x][y] > len) len = MAP[x][y];
		}

		// 다음 칸으로 전진 및 넘어뜨릴 수 있는 남은 개수 감소
		x += dx[dir];
		y += dy[dir];
		len--;
	}

	return cnt;
}

// 2. 수비
void Defence() {
	int x, y;
	cin >> x >> y;

	visited[x][y] = 'S'; // 입력받는 (x,y) 격자의 도미노 세우기 - flag 변경
}

int main() {
	// init
	int R;

	cin >> N >> M >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> MAP[i][j];
			visited[i][j] = 'S'; // 초기에는 전체 도미노가 일어나있다
		}
	}

	// R라운드 진행
	int ans = 0; // 공격수가 쓰러뜨린 도미노의 개수
	for (int i = 0; i < R; i++) {
		ans += Attack();
		Defence();
	}

	// output
	cout << ans << "\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << visited[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}