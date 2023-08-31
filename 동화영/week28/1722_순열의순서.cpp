// 1722 ������ ����
#include <iostream>
using namespace std;

/* ���� Ǯ�� ȸ��
�ϴ� ���� Ǯ�� ����� �� �����ϴ�..
�������� ��Ұ� ���� ����� Ǯ�̰� �ƴϴ�
2���� Ÿ���� �Է¿� ���� ������ �Լ��� ������ �� Ǯ�̿� ���� �ؼ��� �Ʒ����� �Ѵ�
*/

int visited[21]; // ������ �� ���� ��� ����
int nums[21]; // ���� ���
long long N; // 1 ~ N ������ ������ ���� (�ִ� 20)
long long k; // k ��° ����

// ���丮�� ���ϱ�
// N�� �ִ� 20�̹Ƿ� long long���� ����
long long getFactorial() {
	long long ret = 1;
	for (int i = 1; i < N; i++) ret *= i;
	return ret;
}

// Type 1 : k��°�� �迭 ���ϱ�
/*
* �ϴ� ������ (N-1)! ���� �����Ѵ�
* ���Ϸ��� ������ k�� (N-1)!, (N-2)!, (N-3)!, ..., 1 ������ ������
* �� ���� ��(Q)�� �̹� ĭ�� �� ���ڸ� ����Ű�� ��ǥ�̴� -> ������ �̻�� ���� �� Q��° �ֱ�
* �� ���� (������)*(��)�� ���� ���� �ε��� Ž���� ���� �����صд�
*/
void findArr() {
	long long divided = getFactorial();
	long long div = N - 1;
	long long target = k;

	for (int i = 0; i < N; i++) {
		long long curr = ((target - 1) / divided) + 1; // ���� ���ؼ� i��°�� �� ���ڸ� ���Ѵ�
		long long tmp = 0;
		for (int j = 1; j <= N; j++) { // �̻������ ���� �� curr��°�� ���ڰ� i���� ����
			if (!visited[j]) tmp++;
			if (tmp == curr) {
				nums[i] = j;
				visited[j] = 1; // ��� ���
				break;
			}
		}

		if (i == N - 1) break; // divided by zero �߻� ����
		target -= (divided * (curr - 1)); // ���� �ε��� Ž���� ���� ����
		divided /= (div--);
	}

	for (int i = 0; i < N; i++) cout << nums[i] << " ";
	cout << "\n";
}

// Type 2 : �־��� ������ �� ��°�ΰ� ���ϱ� (k��°)
/*
* i��°�� ������ �̻������ ���� �� �� ��°�ΰ��� ���Ѵ�
* k�� i * (���°) ��ŭ�� �����ش�
* �� �ε������� ���Ͽ� �� �����ָ� ���Ϸ��� �ϴ� ���� �տ� �� ���� ������ �ִ°��� ��������
* ���� ���Ϸ��� �ϴ� ������ ������ +1�� �Ͽ� ����Ѵ�
*/
void findKth() {
	long long ans = 0;
	long long divided = getFactorial();
	long long div = N - 1;
	for (int i = 0; i < N; i++) {
		// i��° ���ڰ� ������ �̻������ ���� �� �� ��°�ΰ��� ���ϱ� 
		long long tmp = 0;
		long long curr = nums[i];
		for (int j = 1; j <= curr; j++) {
			if (!visited[j]) tmp++;
		}
		visited[nums[i]] = 1;
		ans += (tmp - 1) * divided; // �� ���ڰ� �´ٸ� �� �տ� ��� ������ �������� �����ֱ�
		
		if (i == N - 1) break; // divided by zero �߻��� ����
		divided /= (div--);
	}

	cout << ans + 1 << "\n"; // +1 �ؼ� ���
}

int main() {
	// input
	cin >> N;

	int type;
	cin >> type;

	if (type == 1) { // type 1
		cin >> k;

		findArr(); // ���� ���ϱ�
	}
	else if (type == 2) { // type 2
		char c;
		for (int i = 0; i < N; i++) {
			cin >> nums[i];
		}
		findKth(); // ������ �� ��°�ΰ��� ���ϱ�
	}

	return 0;
}

/* 5 4 2 3 1
5
1 118
*/

/* 118
5
2 5 4 2 3 1
*/

/*

long long getFactorial(int N) {
	long long ret = 1;
	for (int i = 1; i <= N; i++) ret *= i;
	return ret;
}

void findArr(int N, int k) {
	int ans[21] = { 0, };
	int visited[21] = { 0, };
	long long divided = getFactorial(N - 1);
	long long div = N - 1;
	long long target = k;
	for (int i = 0; i < N; i++) {
		long long curr = (target / divided) + 1;
		long long tmp = 0;
		for (int j = 1; j <= N; j++) {
			if (!visited[j]) tmp++;
			if (tmp == curr) {
				ans[i] = j;
				visited[j] = 1;
				break;
			}
		}

		target %= divided;
		divided /= (div--);
	}

	for (int i = 0; i < N; i++) cout << ans[i] << " ";
	cout << "\n";
}

void findKth(int N, int* nums) {
	long long ans = 0;
	long long divided = getFactorial(N - 1);
	long long div = N - 1;
	int visited[21] = { 0, };
	for (int i = 0; i < N; i++) {
		long long tmp = 0;
		long long curr = *(nums + i);
		for (int j = 1; j <= curr; j++) {
			if (!visited[j]) tmp++;
		}
		visited[*(nums + i)] = 1;
		ans += (tmp - 1) * divided;
		divided /= (div--);
	}

	cout << ans + 1 << "\n";
}
*/