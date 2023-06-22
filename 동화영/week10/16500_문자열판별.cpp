/* 문자열 판별 */
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int dp[101];
string result;
string words[100];
int N;

// DP
// 문자열 전체를 부분문자열로 생성이 가능한가를 판별
// i번째 문자까지 생성가능하다면 dp[i+1]에 1로 표기
// 문자열 길이가 len이라면 dp[len] 의 값이 최종 정답이다

int main() {
	// input
	cin >> result;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> words[i];
	}

	int len = result.length();

	// 문자열 전체를 돌면서
	for (int i = 0; i < len; i++) {
		// 시작지점이거나 (i-1)문자까지 생성이 가능하다면 i번째부터 탐색 시작
		if (i == 0 || dp[i]) { 
			for (int j = 0; j < N; j++) { // 부분문자열들을 탐색
				int tlen = words[j].length();

				if (i + tlen > len) continue; // 문자열의 총 길이를 넘으면 무시

				// j번째 부분문자열이 i번 문자부터 나열되어 있는가를 탐색
				bool flag = true;
				for (int k = 0; k < tlen; k++) {
					if (result[i + k] != words[j][k]) {
						flag = false;
						break;
					}
				}

				// 포함되어 있다면 j번 부분문자열이 끝난 다음 번 인덱스에 1로 표기
				if (flag) {
					dp[i + tlen] = 1;
				}
			}
		}
	}

	// output
	cout << dp[len]; // 문자열 마지막까지 생성을 하였는가를 출력

	return 0;
}

/*
softwarecontest
3
software
cont
ntest
*/