#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int alpha[26]; // A ~ Z 각 알파벳의 자리에 해당하는 숫자들의 합
vector<pair<int, int>> ans; // 각 알파벳 별 차지하는 숫자의 총 합

int main() {
	int N; // 단어의 수
	char words[10][10]; // 입력받을 단어

	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> words[i];

		// 단어의 길이 구하기
		int len = 0;
		for (int j = 0; j < 10; j++) {
			if (words[i][j] == '\0') break;
			len++;
		}

		// 각 알파벳의 위치에 따른 숫자 합하기
		for (int j = 1; j <= len; j++) {
			int ind = (int)(words[i][j - 1] - 'A');
			alpha[ind] += pow(10, len - j);
		}
	}
	
	// 각 알파벳 별 차지하는 숫자의 총 합을 vector에 저장
	for (int i = 0; i < 26; i++) {
		if (alpha[i] == 0) continue;
		ans.push_back({ alpha[i], i });
	}
	
	sort(ans.begin(), ans.end(), greater<>()); // 내림차순 정렬

	// 가장 큰 수를 차지하는 알파벳부터 9 지정하여 답 구하기
	int res = 0;
	for (int i = 0; i < ans.size(); i++) {
		res += (9 - i) * ans[i].first;
	}

	// output
	cout << res << "\n";

	return 0;
}