// 1722 순열의 순서
#include <iostream>
using namespace std;

/* 문제 풀이 회고
일단 나의 풀이 방법은 좀 복잡하다..
수학적인 요소가 들어가서 깔끔한 풀이가 아니다
2가지 타입의 입력에 대한 각각의 함수가 있으며 각 풀이에 대한 해설은 아래에서 한다
*/

int visited[21]; // 현기준 각 수의 사용 여부
int nums[21]; // 순열 기록
long long N; // 1 ~ N 까지의 숫자의 순열 (최대 20)
long long k; // k 번째 순열

// 팩토리얼 구하기
// N이 최대 20이므로 long long으로 잡자
long long getFactorial() {
	long long ret = 1;
	for (int i = 1; i < N; i++) ret *= i;
	return ret;
}

// Type 1 : k번째의 배열 구하기
/*
* 일단 시작은 (N-1)! 에서 시작한다
* 구하려는 순서인 k를 (N-1)!, (N-2)!, (N-3)!, ..., 1 순서로 나눈다
* 그 때의 몫(Q)은 이번 칸에 들어갈 숫자를 가리키는 지표이다 -> 현기준 미사용 숫자 중 Q번째 넣기
* 그 때의 (나눈값)*(몫)을 빼서 다음 인덱스 탐색을 위해 저장해둔다
*/
void findArr() {
	long long divided = getFactorial();
	long long div = N - 1;
	long long target = k;

	for (int i = 0; i < N; i++) {
		long long curr = ((target - 1) / divided) + 1; // 몫을 구해서 i번째에 들어갈 숫자를 구한다
		long long tmp = 0;
		for (int j = 1; j <= N; j++) { // 미사용중인 숫자 중 curr번째의 숫자가 i번에 들어간다
			if (!visited[j]) tmp++;
			if (tmp == curr) {
				nums[i] = j;
				visited[j] = 1; // 사용 기록
				break;
			}
		}

		if (i == N - 1) break; // divided by zero 발생 방지
		target -= (divided * (curr - 1)); // 다음 인덱스 탐색을 위해 갱신
		divided /= (div--);
	}

	for (int i = 0; i < N; i++) cout << nums[i] << " ";
	cout << "\n";
}

// Type 2 : 주어진 순열이 몇 번째인가 구하기 (k번째)
/*
* i번째가 현기준 미사용중인 숫자 중 몇 번째인가를 구한다
* k에 i * (몇번째) 만큼을 더해준다
* 각 인덱스별로 구하여 다 더해주면 구하려고 하는 순열 앞에 몇 개의 순열이 있는가가 구해진다
* 따라서 구하려고 하는 순열의 순서는 +1을 하여 출력한다
*/
void findKth() {
	long long ans = 0;
	long long divided = getFactorial();
	long long div = N - 1;
	for (int i = 0; i < N; i++) {
		// i번째 숫자가 현기준 미사용중인 숫자 중 몇 번째인가를 구하기 
		long long tmp = 0;
		long long curr = nums[i];
		for (int j = 1; j <= curr; j++) {
			if (!visited[j]) tmp++;
		}
		visited[nums[i]] = 1;
		ans += (tmp - 1) * divided; // 이 숫자가 온다면 그 앞에 몇개의 순열이 있을지를 더해주기
		
		if (i == N - 1) break; // divided by zero 발생을 방지
		divided /= (div--);
	}

	cout << ans + 1 << "\n"; // +1 해서 출력
}

int main() {
	// input
	cin >> N;

	int type;
	cin >> type;

	if (type == 1) { // type 1
		cin >> k;

		findArr(); // 순열 구하기
	}
	else if (type == 2) { // type 2
		char c;
		for (int i = 0; i < N; i++) {
			cin >> nums[i];
		}
		findKth(); // 순열이 몇 번째인가를 구하기
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