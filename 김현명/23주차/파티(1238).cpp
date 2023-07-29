#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// x -> 마을 경로

int n, m;
int t_v;

struct r_no {
    int to_v;
    int ct;

    bool operator < (r_no n_v) const {
        if (ct > n_v.ct)
        {
            return true;
        }
        if (ct < n_v.ct)
        {
            return false;
        }
        return false;
    }
};

vector<r_no> for_gp[1002];
vector<r_no> back_gp[1002];

int s_dists[1002];

// 학생들이 파티장소에 갔다 오는 경우
void for_count() {
    int dists[1002] = {};

    for (int i = 0; i < n + 1; i++)
    {
        dists[i] = 10e8;
    }
    dists[t_v] = 0;

    priority_queue<r_no> pq = {};
    pq.push({ t_v,0 });

    while (!pq.empty())
    {
        r_no n_no = pq.top();
        pq.pop();

        if (dists[n_no.to_v] < n_no.ct) { continue; }
        
        int to_v = 0;
        int to_ct = 0;
        for (int s = 0; s < for_gp[n_no.to_v].size(); s++)
        {
            to_v = for_gp[n_no.to_v][s].to_v;
            to_ct = dists[n_no.to_v] + for_gp[n_no.to_v][s].ct;
            if (dists[to_v] < to_ct) { continue; }
            dists[to_v] = to_ct;

            pq.push({ to_v, to_ct });
        }
    }

    // 비용 저장하기
    for (int i = 1; i < n + 1; i++)
    {
        s_dists[i] += dists[i];
    }

    return;
}

// 학생들이 파티 장소로 가는 경우
void back_count()
{
    int dists[1002] = {};

    for (int i = 0; i < n + 1; i++)
    {
        dists[i] = 10e8;
    }
    dists[t_v] = 0;

    priority_queue<r_no> pq = {};
    pq.push({ t_v,0 });

    while (!pq.empty())
    {
        r_no n_no = pq.top();
        pq.pop();

        if (dists[n_no.to_v] < n_no.ct) { continue; }

        int to_v = 0;
        int to_ct = 0;
        for (int s = 0; s < back_gp[n_no.to_v].size(); s++)
        {
            to_v = back_gp[n_no.to_v][s].to_v;
            to_ct = dists[n_no.to_v] + back_gp[n_no.to_v][s].ct;
            if (dists[to_v] < to_ct) { continue; }
            dists[to_v] = to_ct;

            pq.push({ to_v, to_ct });
        }
    }

    // 비용 저장하기
    for (int i = 1; i < n + 1; i++)
    {
        s_dists[i] += dists[i];
    }

    return;
}

int main() {
    cin >> n >> m >> t_v;

    // 정방향 그래프에서 t_v까지의 경로를 볼 수 있다.
    // 역방향에서는 학생들이 파티장소에서 돌아오는 비용을 구할 수 있다.
    // 학생들과 t_v까지의 최소 경로, t_v에서 학생들까지의 최소 경로를 구한다.
    // 위의 두 경우에서의 최소비용을 구하고 dists에 저장한다.
    int a, b, ct;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> ct;
        for_gp[a].push_back({ b,ct });
        back_gp[b].push_back({ a,ct });
    }

    // 두 경우의 최소 비용을 구한다.
    for_count();
    back_count();

    // 학생들의 왕복 경우 중 최대 값을 구한다.
    int max_dist = 0;
    for (int i = 1; i < n + 1; i++)
    {
        if (max_dist < s_dists[i])
        {
            max_dist = s_dists[i];
        }
    }

    cout << max_dist << endl;

    return 0;
};