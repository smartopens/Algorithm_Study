#include <iostream>
#include <cstring>
using namespace std;

int schedule[1001][1001]; // 건물 건설의 우선순위 schedule[a][b] => a->b
int time[1001]; // 각 건물 건설시 소요 시간

int cache[1001]; // 각 건물 건설 완료 시점을 저장

int N, K; // N:건물의 수 K:건물 우선순위 조건의 수
int target; // 타겟 건물의 번호

// tar번 건물을 짓는데 소요되는 시간 구하기
int build(int tar) {
	// tar건물을 짓기 이전에 미리 지어야하는 건물들이 있다
	// 이 건물들을 모두 짓고 오는 시간이 timer
	// 즉 tar 직전에 완료해야 하는 건물들 중 최대 소요시간을 timer에 저장한다
	int timer = 0;
	for (int i = 1; i <= N; i++) {
		if (schedule[i][tar] != 0) { // tar건물 짓기 이전에 i번 건물을 완료해야 한다
			if (cache[i] == -1) build(i); // i번 건물을 짓는데 소요된 시간 값이 없다면 -> 구하러 가기

			if (cache[i] > timer) timer = cache[i]; // tar 이전에 완료해야 하는 건물들 중 최대 소요시간 갱신
		}
	}

	return cache[tar] = (timer + time[tar]); // tar건물 건설 소요시간을 저장 및 반환 -> (이전 소요시간 + tar 건설 소요시간)
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// init
		memset(schedule, 0, sizeof(schedule));
		memset(cache, -1, sizeof(cache));

		// input
		cin >> N >> K;
		for (int i = 1; i <= N; i++) cin >> time[i];
		int a, b;
		for (int i = 0; i < K; i++) {
			cin >> a >> b;
			schedule[a][b] = 1;
		}
		cin >> target;

		// solve & output
		cout << build(target) << "\n";
	}

	return 0;
}

/*
5
3 2
1 2 3
3 2
2 1
1
4 3
5 5 5 5
1 2
1 3
2 3
4
5 10
100000 99999 99997 99994 99990
4 5
3 5
3 4
2 5
2 4
2 3
1 5
1 4
1 3
1 2
4
4 3
1 1 1 1
1 2
3 2
1 4
4
7 8
0 0 0 0 0 0 0
1 2
1 3
2 4
3 4
4 5
4 6
5 7
6 7
7
*/

/*
6
5
399990
2
0
*/