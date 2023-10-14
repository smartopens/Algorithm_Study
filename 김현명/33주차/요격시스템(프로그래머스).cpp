#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// method1
// ��ġ�� ���� t1, t2, t4
// targets: sort() 
// �̺�Ž��: ���ĵ� ���� ������ Ư�� ���� ã��
// 50��*(log1��)

// method2
// targets: ���
// mt1, mt2, mt3
// -> ã��
// 50��*log(50��)

// v1, v2, v3
// (3,5) , (2,6) , (4,8)
bool cmp(vector<int> a, vector<int> b)
{
    if (a[1] < b[1])
    {
        return true;
    }
    if (a[1] > b[1])
    {
        return false;
    }
    return false;
}


int solution(vector<vector<int>> targets) {
    int min_mn = 1;

    sort(targets.begin(), targets.end(), cmp);

    int now_e = targets[0][1] - 1;
    //pq.push(now_e);

    int to_s;
    int to_e;
    for (int tv = 1; tv < targets.size(); tv++)
    {
        to_s = targets[tv][0];
        to_e = targets[tv][1];

        if (now_e < to_s)
        {
            min_mn += 1;
            now_e = to_e - 1;

        }
    }

    return min_mn;
}