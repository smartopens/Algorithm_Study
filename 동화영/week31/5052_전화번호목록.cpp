#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

vector<string> phoneBook; //��ȭ��ȣ��

//��ȭ��ȣ���� �ϰ��� Ž��
int searchPhoneBook(int N) {
	//0 ~ N-1 ������ ��ȭ��ȣ�� ���� ��ȭ��ȣ�� ��
	//nxt�� �ʱ� �Ϻ� ��ȣ�� curr�� �����ϴٸ� �ϰ��� ����
	//�׷��� �ʴٸ� �ϰ��� ����
	for (int i = 0; i < N - 1; i++) {
		string curr = phoneBook[i]; //i�� ��ȭ��ȣ
		int cSz = curr.size();
		
		string nxt = phoneBook[i + 1]; //i+1�� ��ȭ��ȣ
		int nSz = nxt.size();

		if (cSz > nSz) continue; //nxt�� ���̰� �� ª�ٸ� ����(������ �߱⿡ �� ���� �չ�ȣ�� �ٲ���� - ���� ���� ����)
		if (nxt.substr(0, cSz) == curr) return -1; //�ϰ��� ���� ��ȭ��ȣ �߰�!!
	}

	return 1; //������� �Դٸ� �ϰ��� �ִ� ��ȭ��ȣ ����̴�!!
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

		//string Ÿ���� ��ȭ��ȣ�� ������������ ����
		sort(phoneBook.begin(), phoneBook.end());

		int ret = searchPhoneBook(N); //��ȭ��ȣ���� �ϰ��� Ž��

		//output
		if (ret == -1) cout << "NO\n"; //�ϰ��� ����
		else cout << "YES\n"; //�ϰ��� ����
	}

	return 0;
}