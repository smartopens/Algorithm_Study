#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

vector<string> phoneBook; //전화번호부

//전화번호부의 일관성 탐색
int searchPhoneBook(int N) {
	//0 ~ N-1 까지의 전화번호를 다음 전화번호와 비교
	//nxt의 초기 일부 번호가 curr와 동일하다면 일관성 없음
	//그렇지 않다면 일관성 있음
	for (int i = 0; i < N - 1; i++) {
		string curr = phoneBook[i]; //i번 전화번호
		int cSz = curr.size();
		
		string nxt = phoneBook[i + 1]; //i+1번 전화번호
		int nSz = nxt.size();

		if (cSz > nSz) continue; //nxt의 길이가 더 짧다면 무시(정렬을 했기에 이 때는 앞번호가 바뀐거임 - 같을 수가 없음)
		if (nxt.substr(0, cSz) == curr) return -1; //일관성 없는 전화번호 발견!!
	}

	return 1; //여기까지 왔다면 일관성 있는 전화번호 목록이다!!
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		//init
		phoneBook.clear();

		//input
		int N;
		cin >> N;

		string inp;
		for (int i = 0; i < N; i++) {
			cin >> inp;
			phoneBook.push_back(inp);
		}

		//string 타입의 전화번호를 오름차순으로 정렬
		sort(phoneBook.begin(), phoneBook.end());

		int ret = searchPhoneBook(N); //전화번호부의 일관성 탐색

		//output
		if (ret == -1) cout << "NO\n"; //일관성 없음
		else cout << "YES\n"; //일관성 있음
	}

	return 0;
}