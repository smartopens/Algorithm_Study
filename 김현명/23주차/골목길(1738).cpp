#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

int n, m;

struct c_no {
    int to;
    int cost;
};

vector<c_no> c_gp[102];
vector<c_no> cb_gp[102];
int up_dists[102];
int c_vi[102];
bool can_go = true;

void cp_count()
{
    for (int i = 0; i < n + 1; i++)
    {
        up_dists[i] = -10e8;
    }
    up_dists[1] = 0;

    for (int i = 0; i < n; i++)
    {
        int to_v, to_ct;
        for (int v = 1; v < n + 1; v++)
        {
            for (int s = 0; s < c_gp[v].size(); s++) {
                to_v = c_gp[v][s].to;
                to_ct = c_gp[v][s].cost;

                if (up_dists[to_v] < up_dists[v] + to_ct)
                {
                    up_dists[to_v] = up_dists[v] + to_ct;
                    if (i == n - 1)
                    {
                        if (c_vi[to_v] != 0)
                        {
                            can_go = false;
                        }
                    }
                }
            }
        }
    }

    return;
}

void ev_check(int v)
{
    c_vi[v] = 1;
    int to_v;
    for (int s = 0; s < cb_gp[v].size(); s++)
    {
        to_v = cb_gp[v][s].to;
        if (c_vi[to_v] != 0) continue;

        ev_check(to_v);

    }
    return;
}

int main() {
    cin >> n >> m;

    int v;
    int to_v;
    int ct;
    for (int i = 0; i < m; i++)
    {
        cin >> v >> to_v >> ct;
        c_gp[v].push_back({ to_v,ct });
        cb_gp[to_v].push_back({ v,ct });
    }

    ev_check(n);

    int cp[102] = {};
    cp_count();

    int cp_id = n;
    to_v = 0;
    ct = up_dists[n];
    int to_ct = 0;
    cp[n] = n;

    for (int i = n - 1; i > 0; i--)
    {
        for (int s = 0; s < cb_gp[cp_id].size(); s++)
        {
            to_v = cb_gp[cp_id][s].to;
            to_ct = ct - cb_gp[cp_id][s].cost;

            bool t_ok = false;
            for (int j = 1; j < n + 1; j++)
            {
                if (up_dists[j] == to_ct)
                {
                    cp_id = to_v;
                    ct = to_ct;
                    t_ok = true;
                    cp[i] = cp_id;
                    break;
                }
            }
            if (t_ok) {
                break;
            }
        }
    }

    if(!can_go)
    {
        cout << -1 << endl;
    }
    else
    {
        for (int i = 1; i < n + 1; i++)
        {
            cout << cp[i] << " ";
        }
    }

    return 0;
};