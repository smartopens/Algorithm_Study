#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int n, m;
int k;
int m_s;

int parent[52];
int k_peo[52];
int m_peo[52][52];

int fs_num;

int Find(int v)
{
    if (v == parent[v])
    {
        return v;
    }

    return parent[v] = Find(parent[v]);
}

void Union(int v1, int v2)
{
    int pv1 = Find(v1);
    int pv2 = Find(v2);

    if (pv1 < pv2)
    {
        parent[pv2] = pv1;
    }
    else if (pv1 > pv2)
    {
        parent[pv1] = pv2;
    }
}

int main() {
    cin >> n >> m;
    cin >> k;

    for (int i = 1; i < n + 1; i++)
    {
        parent[i] = i;
    }

    // 진실을 아는 사람 입력
    // 해당 사람들의 그룹을 만들어둔다.
    int k_p;
    for (int i = 0; i < k; i++)
    {
        cin >> k_p;
        k_peo[i] = k_p;
    }
    for (int i = 0; i < k-1; i++)
    {
        Union(k_peo[i], k_peo[i + 1]);
    }

    // m개의 파티 정보를 저장하고 각 파티당 사람들은 관계가 맺어진다.
    // 해당 관계정보를 저장해둔다.
    // 이후에 진실을 아는 사람들과 관계가 맺어지는지를 조사하고
    // 해당된다면 지민이가 거짓을 말할 수 없다.
    // 이를 이용해 최대로 거짓을 말하는 경우를 구한다.
    for (int i = 0; i < m; i++)
    {
        cin >> m_s;
        int m_p = 0;
        for (int j = 0; j < m_s; j++)
        {
            cin >> m_p;
            m_peo[i][j] = m_p;
        }

        for (int j = 0; j < m_s-1; j++)
        {
            Union(m_peo[i][j], m_peo[i][j + 1]);
        }
    }

    // 다시 m개의 파티정보에서 거짓을 말할 수 있는지를 본다.
    for (int i = 0; i < m; i++)
    {
        bool can_s = true;
        for (int j = 0; j < 50; j++)
        {
            if (m_peo[i][j] == 0) break;
            if (Find(k_peo[0]) == Find(m_peo[i][j]))
            {
                can_s = false;
                break;
            }
        }
        if (can_s != false)
        {
            fs_num += 1;
        }
    }

    cout << fs_num << endl;
    return 0;
};