/* 문자 해독 */
#include <iostream>
using namespace std;

char gword[3000000] = { 0, }; // 문자열
int Word[60] = { 0, }; // 0:A~Z 26:a~z
int used[60] = { 0, }; // 현재 탐색중이 부분 문자열에서 사용중인 알파벳의 수
int g, slen; // W와 S의 길이

// Word 배열의 인덱스 계산을 위해
// 알파벳을 숫자로 변환해주는 함수
// A ~ Z : 0 ~ 25
// a ~ z : 26 ~ 51
int charToInt(char ch) {
	if (ch >= 'A' && ch <= 'Z') { // 대문자
		return (int)(ch - 'A');
	}
	else if (ch >= 'a' && ch <= 'z') { // 소문자
		return (int)(ch - 'a') + 26;
	}

	return -1; // 알파벳이 아닌 경우
}

// 알파벳 숫자 세기
bool checkWord() {
	for (int i = 0; i < 52; i++) {
		if (Word[i] != used[i]) return false; // 주어진 부분 문자열과 사용중인 알파벳의 숫자 비교
	}

	return true; // 모두 동일하면 true 반환
}

// 65 : A, 97 : a
int main() {
	char inp;

	// input
	cin >> g >> slen;
	for (int i = 0; i < g; i++) {
		cin >> inp;
		Word[charToInt(inp)]++; // W에 포함되는 알파벳 개수 세기
	}

	for (int i = 0; i < slen; i++) {
		cin >> gword[i];
		if (i < g) { // W 길이만큼만 알파벳 세기
			used[charToInt(gword[i])]++;
		}
	}

	int cnt = 0; // 정답 수

	if(checkWord()) cnt++; // 사용중인 알파벳 개수가 모두 동일하다면 cnt 증가
	for (int i = 0; i < slen - g; i++) {
		// 이전 부분 문자열 중
		// 앞에 한 칸은 알파벳 빼주기
		// 뒤에 한 칸은 알파벳 더해주기
		used[charToInt(gword[i])]--;
		used[charToInt(gword[i + g])]++;

		if (checkWord()) cnt++; // 사용중인 알파벳 개수가 모두 동일하다면 cnt 증가
	}

	// output
	cout << cnt << "\n";

	return 0;
}