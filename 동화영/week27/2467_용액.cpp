#include <iostream>
#include <algorithm>
using namespace std;

// ����� Ư����
// �꼺�� 1 ~ 1,000,000,000
// ��Į������ -1,000,000,000 ~ -1
// ������������ �־����Ƿ� left, right �����ͷ� �����ϸ�
// 1) �� ���� ���� �����̸� left++
// 2) �� ���� ���� ����̸� right--
// 3) �� ���� ���� 0�̸� left++, right-- ó��
const int MAX_N = 100000;
int nums[MAX_N];

void findZero(int N) {
	int ans = 2134567890; // �ּ��� ����� Ư������ ��
	int num1 = 0, num2 = 0; // �ּ��� ����� left, right �ε���
	int left = 0, right = N - 1; // ���� �ε��� (two pointer)

	while (left < right) { // left�� �� ���ʿ� �ִ� ��츸 Ž��
		if (abs(nums[left] + nums[right]) < ans) { // �ּҰ� �߽߰� ����
			ans = abs(nums[left] + nums[right]);
			num1 = left;
			num2 = right;
		}

		if (nums[left] + nums[right] < 0) { // �� ���� ���� ������ ���
			left++; // left�� ������ �� ũ�Ƿ� left ������ �̵�
		}
		else if (nums[left] + nums[right] > 0) { // �� ���� ���� ����� ���
			right--;
		}
		else { // �� ���� ���� 0�� ���
			left++;
			right--;
		}
	}

	// output
	cout << nums[num1] << " " << nums[num2] << "\n";
}

int main() {
	int N;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> nums[i];
	}

	if (nums[0] > 0) { // ��ü ����� �꼺(���)�� ���
		cout << nums[0] << " " << nums[1] << "\n";
	}
	else if (nums[N - 1] < 0) { // ��ü ����� ��Į����(����)�� ���
		cout << nums[N - 2] << " " << nums[N - 1] << "\n";
	}
	else { // ��ü ��� �� �꼺/��Į���� ���� ���
		findZero(N);
	}

	return 0;
}