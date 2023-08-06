#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int tc;
int n, m;
int k;

struct r_no{
    int to;
    int ct;
};

vector<r_no> r_gp[502];
int r_vi[502][502];
int w_vi[502][502];

// 음의 사이클이 존재하는지를 본다.
// 최적 경로가 확정이 되었음에도 한번더 갱신이 되면 위의 경우가 생긴다.
bool bellmfd()
{
    int up_dists[502] = {};
    for (int i = 0; i < n + 1; i++)
    {
        up_dists[i] = 21e8;
    }
    up_dists[1] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int v = 1; v < n + 1; v++)
        {
            int to_v, to_ct;
            for (int s = 0; s < r_gp[v].size(); s++)
            {
                to_v = r_gp[v][s].to;
                to_ct = r_gp[v][s].ct;

                if (up_dists[to_v] > up_dists[v] + to_ct)
                {
                    up_dists[to_v] = up_dists[v] + to_ct;
                    if (i == n - 1)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    cin >> tc;

    for (int ti = 0; ti < tc; ti++)
    {
        cin >> n >> m >> k;

        // 자료구조 초기화 하기
        memset(r_vi, -1, sizeof(r_vi));
        memset(w_vi, -1, sizeof(w_vi));
        for (int i = 0; i < n + 1; i++)
        {
            r_gp[i].clear();
        }

        // 도로 정보 입력 받기
        // 양방향이다.
        int a, b, ct;
        int r_ct = 0;
        for (int i=0; i<m; i++)
        { 
            cin >> a >> b >> ct;

            r_gp[a].push_back({ b,ct });
            r_gp[b].push_back({ a,ct });
        }

        // 웜홀 정보 입력 받기
        // 시간이 줄어든다.
        int w_ct = 0;
        for (int i = 0; i < k; i++)
        {
            cin >> a >> b >> ct;
            r_gp[a].push_back({ b,-ct });
            w_vi[a][b] = ct;
        }

        // 임의의 지점에서 시간이 줄어드는지를 본다.
        // 고로, 음의 사이클이 존재하는지를 판단한다.
        if (!bellmfd())
        {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
};