/* LCA */
#include <iostream>
using namespace std;

int parent[50001];
int N;

int findLevel(int node) {
	int ret = 0, curr = node;
	while (curr != 0) {
		curr = parent[curr];
		ret++;
	}

	return ret - 1;
}

int sameLevel(int tar, int cLev, int nLev) {
	int ret = tar;
	for (int i = 0; i < cLev - nLev; i++) {
		ret = parent[ret];
	}

	return ret;
}

int findCA(int a, int b) {
	int la = findLevel(a);
	int lb = findLevel(b);

	int ta = a, tb = b;
	if (la < lb) {
		tb = sameLevel(b, lb, la);
	}
	else if (la > lb) {
		ta = sameLevel(a, la, lb);
	}

	// ta 와 tb로부터 위로 올라가다가 같은 조상
	while (ta != tb) {
		ta = parent[ta];
		tb = parent[tb];
	}

	return ta;
}

void makeTree() {

}

int main() {
	cin >> N;
	int a, b;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
	}

	makeTree();

	int M;
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;

		cout << findCA(a, b) << "\n";
	}

	return 0;
}