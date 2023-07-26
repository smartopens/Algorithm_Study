#include <iostream>
#include <vector>
using namespace std;

struct ROBOT {
	int y;
	int x;
	int d;
};

int dy[4] = { -1, 0, 1, 0 }; // 북서남동 (반시계)
int dx[4] = { 0, -1, 0, 1 };

vector<ROBOT> robots; // N개의 로봇 정보
int MAP[102][102]; // 땅의 현재 정보
int A, B; // 땅의 사이즈 A*B
int N, M; // N: 로봇의 수, M: 명령의 수

// 'L', 'R'의 명령 수행 - 회전
void turnRobot(int rob, char dir, int cnt) {
	ROBOT curr = robots[rob];
	int cDir = curr.d;
	if (dir == 'L') { // 왼쪽으로 90도 회전(반시계)
		curr.d = (cDir + (cnt % 4)) % 4;
	}
	else { // 오른쪽으로 90도 회전(시계)
		curr.d = ((cDir - (cnt % 4)) + 4) % 4;
	}
	robots[rob].d = curr.d; // 회전 후 바라보는 방향으로 로봇 정보 변경
}

// 'F'의 명령 수행 - 앞으로 전진
int forwardRobot(int rob, int cnt) {
	ROBOT curr = robots[rob];
	int ny = curr.y;
	int nx = curr.x;
	for (int i = 1; i <= cnt; i++) { // cnt 칸만큼 전진한다
		ny += dy[curr.d];
		nx += dx[curr.d];

		// 한 칸씩 전진하는 도중 벽이나 다른 로봇을 만날 경우 반환
		if (ny > 100 || nx > B || ny <= 100 - A || nx <= 0) return -1;
		if (MAP[ny][nx] != 0) return MAP[ny][nx];
	}

	// cnt칸 전진 동안 충돌 미발생한다면 땅, 로봇 정보 갱신
	MAP[ny][nx] = rob;
	MAP[curr.y][curr.x] = 0;
	robots[rob].y = ny;
	robots[rob].x = nx;

	return 0;
}

int main() {
	// input
	int x, y, d;
	char dir;

	int crashed = 0; // 명령 도중 충돌 발생 여부

	robots.push_back({ 0,0,0 });
	cin >> B >> A >> N >> M;

	for (int i = 1; i <= N; i++) {
		cin >> x >> y >> dir;
		MAP[100 - y + 1][x] = i; // 땅의 정보 저장 (행 인덱스 주의)
		d = dir == 'N' ? 0 : dir == 'W' ? 1 : dir == 'S' ? 2 : 3; // 북서남동 순서
		robots.push_back({ 100 - y + 1, x, d }); // 로봇의 정보 저장
	}

	for (int i = 0; i < M; i++) {
		cin >> x >> dir >> y;
		if (dir == 'F') { // 직진 명령
			int robNum = forwardRobot(x, y);
			// -1 반환: 벽 충돌
			// 자연수 반환: 로봇 충돌
			// 0: 충돌 발생 X
			if (robNum > 0) cout << "Robot " << x << " crashes into robot " << robNum << "\n";
			else if (robNum == -1) cout << "Robot " << x << " crashes into the wall\n";

			if (robNum != 0) { // 충돌 발생했다면 더이상 명령 수행 X
				crashed = 1;
				break;
			}
		}
		else { // 회전 명령
			turnRobot(x, dir, y);
		}
	}

	// 충돌 미발생 시 output
	if (crashed == 0) cout << "OK\n";

	return 0;
}