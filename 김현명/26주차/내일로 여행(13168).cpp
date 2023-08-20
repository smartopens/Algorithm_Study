#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int n;
int t_co;
int m;
int k;

string m_plan[202];

struct t_info {
    string to;
    string m_st;
    int co;
    
};

struct t_no
{
    string to;
    int co;
    bool operator < (t_no now) const {
        if (co > now.co)
        {
            return true;
        }
        if (co < now.co)
        {
            return false;
        }
        return false;
    };
};

unordered_map<string, vector<t_info>> c_gp;
unordered_map<string, int> c_names;
unordered_map<string, int> free_c;
unordered_map<string, int> half_c;
unordered_map<string, int> dists;

int min_co1 = 0;
int min_co2 = 0;

void t_count(string sc, int to_buy)
{
    priority_queue<t_no> pq;
    pq.push({sc,0});

    for (auto c_name : c_names)
    {
        dists[c_name.first] = 21e8;
    }
    dists[sc] = 0;

    while (!pq.empty())
    {
        t_no v = pq.top();
        pq.pop();

        if (dists[v.to] < v.co) continue;

        string to_v;
        int to_co;
        for (int s = 0; s < c_gp[v.to].size(); s++)
        {
            to_v = c_gp[v.to][s].to;
            int tmp_co;
            if (to_buy != 0 && free_c[c_gp[v.to][s].m_st] != 0)
            {
                tmp_co = 0;
            }
            else if (to_buy != 0 && half_c[c_gp[v.to][s].m_st] != 0)
            {
                tmp_co = c_gp[v.to][s].co * (1 / 2);
            }
            else {
                tmp_co = c_gp[v.to][s].co;
            }

            to_co = dists[v.to] + tmp_co;

            if (dists[to_v] >= to_co) continue;
            dists[to_v] = to_co;
            pq.push({to_v, to_co });
        }
    }

};

int main() {
    cin >> n >> t_co;

    string c_name;
    for (int i = 0; i < n; i++)
    {
        cin >> c_name;
        c_names[c_name] = 1;
        dists[c_name] = 21e8;
    }

    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> c_name;
        m_plan[i] = c_name;
    }
    
    cin >> k;
    string c_st, sc, ec;
    int to_co;
    for (int i = 0; i < k; i++)
    {
        cin >> c_st >> sc >> ec >> to_co;
        c_gp[sc].push_back({ec,c_st,to_co});
    }

    free_c["Mugunghwa"] = 1;
    free_c["ITX-Cheongchun"] = 1;
    free_c["ITX-Saemaeul"] = 1;
    half_c["V-Train"] = 1;
    half_c["S-Train"] = 1;

    for (int i = 0; i < m - 1; i++)
    {
        sc = m_plan[i];
        ec = m_plan[i + 1];
        t_count(sc,0);
        min_co1 += dists[ec];
        cout << min_co1 << endl;
    }
    cout << "\n" << endl;
    min_co2 += t_co;
    for (int i = 0; i < m - 1; i++)
    {
        sc = m_plan[i];
        ec = m_plan[i + 1];
        t_count(sc, 1);
        min_co2 += dists[ec];
        cout << min_co2 << endl;
    }

    //cout << min_co1 << " " << min_co2 << endl;

    if (min_co1 <= min_co2)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
    }
    return 0;
};