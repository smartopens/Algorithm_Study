#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>

using namespace std;

int n, k;
int f_sec;

int vi[200002][20];

struct p_no {
    int now_n;
    int jn;
};

// 수빈이 -> 동생까지 최소 시간을 고려한다.
// 이 때, 2배로 가는 경우는 드는 시간이 다른 것보다 적다.
// 고로 이 경우를 먼저 탐색해준다.
// 현재 수빈이의 위치에 따라 2배 점프 하는 경우가 달라진다.
// 2배점프, -1, 1로 가는 경우로 탐색한다.

void b_find()
{
    queue<p_no> q = {};
    q.push({ n,0 });
    vi[n][0] = 1;
    if (n == k)
    {
        f_sec = 0;
        return;
    }
    while (!q.empty())
    {
        p_no now_p = q.front();
        q.pop();

        if (now_p.now_n == k)
        {
            f_sec = vi[now_p.now_n][now_p.jn] - 1;
            return;
        }

        int to_n = 2 * now_p.now_n;
        if (to_n > 200000) continue;
        if (vi[to_n][now_p.jn + 1] != 0) continue;

        vi[to_n][now_p.jn + 1] = vi[now_p.now_n][now_p.jn];
        q.push({ to_n, now_p.jn + 1 });

        for (int di = -1; di < 2; di += 2)
        {
            to_n = now_p.now_n + di;
            if (to_n > 200000 || to_n < 0) continue;
            if (vi[to_n][now_p.jn] != 0) continue;

            vi[to_n][now_p.jn] = vi[now_p.now_n][now_p.jn] + 1;
            q.push({ to_n, now_p.jn });

        }
    }
}

int main() {
    // 수빈 위치:N
    // 동생 위치:K
    cin >> n >> k;

    // 수빈 -> 동생 가능한지 보기
    b_find();
    cout << f_sec << endl;
    return 0;
};