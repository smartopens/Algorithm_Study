// 7662 이중 우선순위 큐
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_N = 1000000;
bool isPoped[MAX_N]; // 0:살아있음, 1:pop 발생됨
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> asc; // 오름차순 (값, 인덱스)
priority_queue<pair<int, int>> desc; // 내림차순 (기본)
int cnt, aliveCnt; // cnt: insert된 총 개수, aliveCnt: 현재 pop되지 않고 남아있는 개수

// INSERT 실행
void insertPQ(int  num) {
	// 각 pq에 push
	asc.push({ num, cnt });
	desc.push({ num, cnt });

	// 신규 숫자가 들어왔으므로 cnt 증가
	aliveCnt++;
	cnt++;
}

// DELETE 실행
void deletePQ(int prior, bool isAns) {
	if (aliveCnt == 0) return;

	int target = 0, targetInd = 0;
	if (prior == -1) { // 최소값 찾기
		while (!asc.empty()) {
			pair<int, int> mini = asc.top();
			asc.pop();
			if (isPoped[mini.second]) continue;

			target = mini.first;
			targetInd = mini.second;
			break;
		}
	}
	else if (prior == 1) { // 최대값 찾기
		while (!desc.empty()) {
			pair<int, int> maxi = desc.top();
			desc.pop();
			if (isPoped[maxi.second]) continue;

			target = maxi.first;
			targetInd = maxi.second;
			break;
		}
	}

	if (isAns) {
		cout << target << " ";
		return;
	}
	isPoped[targetInd] = true;
	aliveCnt--;
}

int main() {
	// input
	int T, Q, num;
	char act;

	cin >> T;
	for (int t = 1; t <= T; ++t) {
		// init
		cnt = 0, aliveCnt = 0;
		memset(isPoped, false, sizeof(isPoped));
		while (!asc.empty()) asc.pop();
		while (!desc.empty()) desc.pop();

		cin >> Q;
		for (int j = 0; j < Q; ++j) {
			cin >> act >> num;
			
			if (act == 'I') insertPQ(num); // insert 실행
			else if (act == 'D') deletePQ(num, false); // delete 실행 (false: 미출력)
		}

		// output
		if (aliveCnt == 0) cout << "EMPTY\n"; // 남아있는 숫자가 없으면 EMPTY 출력
		else {
			// 출력용 delete
			deletePQ(1, true);
			deletePQ(-1, true);
			cout << "\n";
		}
	}

	return 0;
}
