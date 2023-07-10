#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int t;
int n;
int r_v;
int t_v1, t_v2;

vector<int> t_graph[10002];
vector<int> f_graph[10002];

struct node {
    int lev;
    bool v1_f;
    bool v2_f;
};

node dp[10002];

// 부모노드에서 자식노드까지 탐색한다.
// 목표노드를 만난다면 해당 경로에 이를 기록한다.
// lev역시 기록한다.
node c_find(int v, int lev)
{
    if (v == t_v1)
    {
        dp[v].v1_f = true;
    }
    if (v == t_v2)
    {
        dp[v].v2_f = true;
    }

    if (dp[v].lev != -1)
    {
        return dp[v];
    }

    dp[v].lev = lev;

    // 다음번 노드가 목표노드를 찾았는지를 본다.
    for (int s = 0; s < t_graph[v].size(); s++)
    {
        int to = t_graph[v][s];
        node now = c_find(to, lev+1);
        if (now.v1_f == true) {
            dp[v].v1_f = true;
        }
        if (now.v2_f == true) {
            dp[v].v2_f = true;
        }
    }

    return dp[v];
}

// 루트 노드를 찾는다.
// 부모 노드가 없을때까지를 본다.
void p_find(int v)
{
    bool em_p = false;

    for (int s = 0; s < f_graph[v].size(); s++)
    {
        int to = f_graph[v][s];
        em_p = true;
        p_find(to);
    }

    if (em_p == false) {
        r_v = v;
        return;
    }
}
int main() {
    cin >> t;
    for (int tc = 0; tc < t; tc++)
    {
        cin >> n;
        memset(t_graph, 0, sizeof(t_graph));
        memset(f_graph, 0, sizeof(f_graph));

        // 부모 -> 자식 그래프: t_graph
        // 자식 -> 부모 그래프: f_graph
        for (int i = 0; i < n-1; i++)
        {
            int p, c;
            cin >> p >> c;
            t_graph[p].push_back(c);
            f_graph[c].push_back(p);
        }

        // 목표 노드
        cin >> t_v1 >> t_v2;

        // 루트 노드를 찾는다.
        // 랜덤 노드로부터 부모가 없을때까지를 본다.
        p_find(n);

        // 저장소를 초기화한다.
        for (int i = 0; i < n + 1; i++)
        {
            dp[i].lev = -1;
            dp[i].v1_f = false;
            dp[i].v2_f = false;
        }

        // 부모노드로부터 시작해서 목표노드까지를 탐색한다.
        // 이 때 목표노드에 도착했다면 해당 경로에 이를 기록한다.
        // 가장 윗 노드에서 lev을 기록한다.
        // 이 기록으로 가장 깊은 층의 조상을 구한다.
        c_find(r_v,1);
        
        // 가장 깊은층 공통 조상 찾기
        int f_v = 0;
        int max_l = 0;

        for (int i = n; i > 0; i--)
        {
            if (dp[i].v1_f == true && dp[i].v2_f == true)
            {
                if (dp[i].lev > max_l)
                {
                    f_v = i;
                    max_l = dp[i].lev;
                }
            }
        }
        cout << f_v << endl;
    }
    return 0;
}