#include <iostream>
#include <algorithm>
using namespace std;

// 용액의 특성값
// 산성은 1 ~ 1,000,000,000
// 알칼리성은 -1,000,000,000 ~ -1
// 오름차순으로 주어지므로 left, right 포인터로 시작하며
// 1) 두 값의 합이 음수이면 left++
// 2) 두 값의 합이 양수이면 right--
// 3) 두 값의 합이 0이면 left++, right-- 처리
const int MAX_N = 100000;
int nums[MAX_N];

void findZero(int N) {
	int ans = 2134567890; // 최소인 경우의 특성값의 합
	int num1 = 0, num2 = 0; // 최소인 경우의 left, right 인덱스
	int left = 0, right = N - 1; // 시작 인덱스 (two pointer)

	while (left < right) { // left가 더 왼쪽에 있는 경우만 탐색
		if (abs(nums[left] + nums[right]) < ans) { // 최소값 발견시 갱신
			ans = abs(nums[left] + nums[right]);
			num1 = left;
			num2 = right;
		}

		if (nums[left] + nums[right] < 0) { // 두 값의 합이 음수인 경우
			left++; // left의 절댓값이 더 크므로 left 포인터 이동
		}
		else if (nums[left] + nums[right] > 0) { // 두 값의 합이 양수인 경우
			right--;
		}
		else { // 두 값의 합이 0인 경우
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

	if (nums[0] > 0) { // 전체 용액이 산성(양수)인 경우
		cout << nums[0] << " " << nums[1] << "\n";
	}
	else if (nums[N - 1] < 0) { // 전체 용액이 알칼리성(음수)인 경우
		cout << nums[N - 2] << " " << nums[N - 1] << "\n";
	}
	else { // 전체 용액 내 산성/알칼리성 섞인 경우
		findZero(N);
	}

	return 0;
}