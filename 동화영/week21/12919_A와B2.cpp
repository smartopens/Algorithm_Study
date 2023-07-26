// 12919 A와 B 2
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

// S에서 T를 만들기에는 경우의 수가 (최악의 경우) 2^50가지이다.
// 따라서 시간 초과 발생
// T에서 S를 만들기로 결정
// 1. 현재 T`에서 뒤에 A가 있으면 A를 뺀 문자열을 queue에 넣는다.
// 2. 현재 T`에서 앞에 B가 있으면 B를 빼고 뒤집은 문자열을 queue에 넣는다.
// 이 방법이라면 불필요한 연산을 할 필요가 없어서 시간 단축

int main() {
	// input
	string S, T;
	cin >> S >> T;

	int ans = 0;
	int sLen = S.size();
	queue<string> q;
	q.push(T);

	while (!q.empty()) {
		string now = q.front();
		q.pop();

		// 현재 탐색 중인 문자열이 원문자 S와 동일하다면 ans 갱신 후 탐색 중지
		if (now == S) {
			ans = 1;
			break;
		}

		// now와 S의 길이가 같다면 이미 틀렸다는 뜻이므로
		// 더이상 탐색할 필요 없다
		if (now.size() == sLen) continue;

		// 1. 맨 뒤가 A라면 A를 뺀 문자열을 queue에 추가
		if (now[now.size() - 1] == 'A') {
			q.push(now.substr(0, now.size() - 1));
		}
		// 2. 맨 앞이 B라면 B를 빼고 reverse한 문자열을 queue에 추가
		if (now[0] == 'B') {
			string nxt = now.substr(1);
			reverse(nxt.begin(), nxt.end());
			q.push(nxt);
		}
	}

	// 답을 찾아서 탈출한 경우 queue에 남은 데이터 삭제
	while (!q.empty()) q.pop();

	// output
	// 1:답 찾음 0:답 못찾음
	cout << ans << "\n";

	return 0;
}