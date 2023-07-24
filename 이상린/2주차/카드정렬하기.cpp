#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    int N; cin >> N;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0;i < N;++i)
    {
        // 숫자 카드 묶음 각각의 크기
        int a; cin >> a;
        pq.push(a);
    }

    int ans = 0;
    while (pq.size() > 1)
    {
        // 2개씩 빼고, 하나 넣기
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();

        int temp = a + b;
        ans += temp;
        pq.push(temp);
    }

    // 출력 : 최소 비교 횟수
    cout << ans;
    

    return 0;
}