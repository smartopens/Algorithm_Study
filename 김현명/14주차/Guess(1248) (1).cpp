#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int n;
char opers[12][12];
int nums[22];
int ans_num[12];

// 재귀가 진행되면서 해당 경우가 가능한지를 본다.
// 단계가 높을 수록 보는 조건도 증가한다.
// 해당 수열의 합이 opers의 조건과 맞는지를 본다.
bool isPossible(int now)
{
	if (now == 0) return true;
	int t_sum = 0;

	for (int sr = now - 1; sr > -1; sr--)
	{
		t_sum = 0;

		for (int i = 0; i < (now-1-(sr))+1; i++) {
			t_sum += ans_num[now - 1 - i];
		}

		if (t_sum > 0 && opers[sr][now - 1] != '+') return false;
		if (t_sum < 0 && opers[sr][now - 1] != '-') return false;
		if (t_sum == 0 && opers[sr][now - 1] != '0') return false;
	}

	return true;
}

// 수열의 경우를 탐색한다.
// 만약 정답이 되는 경로가 나오면 해당 경우를 출력한다.
// true를 반환하고 종료한다.
bool dfs(int now)
{
	if (!isPossible(now)) return false;

	if (now == n)
	{
		for (int i = 0; i < n; i++)
		{
			cout << ans_num[i] << " ";
		}
		return true;
	}

	for (int i = 0; i < 21; i++)
	{
		ans_num[now] = nums[i];
		if (dfs(now + 1)) return true;
	}

	return false;
}
 
int main() {
	// 가능한 수열의 수를 저장한다.
	int num = -10;

	for (int i = 0; i < 21; i++)
	{
		nums[i] = num;
		num += 1;
	}

	// 수열에 따른 상태정보 입력받기
	// n개의 수열 -> n*(n+1)/2 개의 상태
	cin >> n;
	for (int r = 0; r < n; r++)
	{
		for (int c = r; c < n; c++)
		{
			cin >> opers[r][c];
		}
	}

	// ans_num의 첫번째 경우에서부터 마지막 까지를 본다.
	// 숫자는 -10에서 10까지가 들어갈 수 있고 각 경우에서 가능한지를 본다.
	// 이 때, 단계가 진행될 수록 조건의 경우도 같이 증가한다.
	// 마지막까지 갈 수 있는 가능성은 줄어들고 만약 경로를 찾았다면
	// 백트래킹 분기점을 종료함으로써 효율을 높인다.
	dfs(0);

	return 0;
}