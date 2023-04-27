/* 트리 순회 */
#include <iostream>
using namespace std;

int map[26][26];

int N;

pair<int, int> findChild(int parent) {
	int left = -1, right = -1;
	for (int i = 0; i < 26; i++) {
		if (left >= 0 && right >= 0) break;

		if (map[parent][i] == 1) left = i;
		else if (map[parent][i] == 2) right = i;
	}

	return { left, right };
}

void preOrder(int node) {
	pair<int, int> child = findChild(node);
	int left = child.first;
	int right = child.second;

	cout << (char)(node + 'A');

	if (left >= 0) {
		preOrder(left);
	}

	if (right >= 0) {
		preOrder(right);
	}
}

void inOrder(int node) {
	pair<int, int> child = findChild(node);
	int left = child.first;
	int right = child.second;

	if (left >= 0) {
		inOrder(left);
	}

	cout << (char)(node + 'A');

	if (right >= 0) {
		inOrder(right);
	}
}

void postOrder(int node) {
	pair<int, int> child = findChild(node);
	int left = child.first;
	int right = child.second;

	if (left >= 0) {
		postOrder(left);
	}

	if (right >= 0) {
		postOrder(right);
	}

	cout << (char)(node + 'A');
}

int main() {
	cin >> N;
	char parent, left, right;
	for (int i = 0; i < N; i++) {
		cin >> parent >> left >> right;

		int ind = parent - 'A';
		
		if (left != '.') {
			int le = left - 'A';
			map[ind][le] = 1;
		}
		if (right != '.') {
			int ri = right - 'A';
			map[ind][ri] = 2;
		}

	}

	int root = -1;
	for (int i = 0; i < 26; i++) {
		bool flag = false;
		for (int j = 0; j < 26; j++) {
			if (map[j][i] > 0) {
				flag = true;
				break;
			}
		}

		if (!flag) {
			root = i;
			break;
		}
	}

	preOrder(root); // 전위 순회
	cout << '\n';

	inOrder(root); // 중위 순회
	cout << '\n';

	postOrder(root); // 후위 순회
	cout << '\n';

	return 0;
}