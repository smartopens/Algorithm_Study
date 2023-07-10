#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int n;
int t;
int k;

struct node {
    int id;
    int cost;
};

struct g_v {
    int to;
};

node build[1002];
vector<int> b_graph[1002];
int dp[1002];

// 목표노드 w로부터 차례차례 본다.
// 한 노드를 기준으로 다음 노드의 시간비용중 최대를 고려한다.
// 해당 시간만큼 기다려야되기 때문이다.
// 자기 건물을 짓는 시간에 위 시간을 더하고 최소 시간비용으로 저장한다. 
int dfs(int now)
{
    if (dp[now] != 21e8)
    {
        return dp[now];
    }

    int max_t = 0;

    for (int s = 0; s < b_graph[now].size(); s++)
    {
        int to = b_graph[now][s];
        max_t = max(max_t, dfs(to));
    }

    dp[now] = min(dp[now], build[now].cost + max_t);
    return dp[now];
}

int main() {
    cin >> t;
    // 목적 노드
    int w;

    for (int tc = 0; tc < t; tc++)
    {
        cin >> n >> k;
        memset(b_graph, 0, sizeof(b_graph));

        // 각 건물 노드의 비용을 저장하기
        for (int i = 0; i < n; i++)
        {
            build[i+1].id = i+1;
            cin >> build[i+1].cost;
        }

        // 건물 노드별 먼저 지어야하는 노드를 연결한다.
        // 목표노드는 w이다.
        // 고로 해당 노드로부터 풀어야하는 것들을 보면
        // 되기 때문에 단방향으로 설정한다.
        for (int i = 0; i < k; i++)
        {
            int a, b;
            cin >> a >> b;
            b_graph[b].push_back(a);
        }

        cin >> w;

        // 맨 마지막 노드로 부터 건물을 짓는 최대 시간이 저장된다.
        // 이 값은 다음 건물에서도 사용되므로 기록해서 사용한다.
        for (int i = 0; i < n+1; i++)
        {
            dp[i] = 21e8;
        }

        // 건물w를 짓는 최소 시간
        int min_time = dfs(w);
        cout << min_time << endl;
    }

    return 0;
}