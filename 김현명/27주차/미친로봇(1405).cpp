#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int n;
double ep, wp, sp, np;
double mps[4];
double p_sum;

int vi[30][30];
int dr[4] = { 0,0,1,-1 };
int dc[4] = { 1,-1,0,0 };

// �κ��� n���̵��Ѵ�.
// �̵��� �Ϸ�Ǹ� �׵��� ����� Ȯ���� ���Ѵ�.
// �ѹ� �̵��� ��δ� �̵����� �ʰ� �Ѵ�.
void r_move(int a, int r, int c, double now_p)
{
    if (a > n-1)
    {
        p_sum += now_p;
        return;
    }

    int nr, nc;
    for (int i = 0; i < 4; i++)
    {
        nr = r + dr[i];
        nc = c + dc[i];

        if (vi[nr][nc] != 0) continue;

        vi[nr][nc] = 1;
        r_move(a + 1, nr, nc, now_p * mps[i]);
        vi[nr][nc] = 0;
    }

    return;
}

int main() {
    cin >> n;
    // ������: 10-9���� ���
    cout << fixed;
    cout.precision(9);

    // �κ��� �̵�Ȯ�� �Է¹ޱ�
    // �� �� �� ��
    double in_p;
    for (int i = 0; i < 4; i++)
    {
        cin >> in_p;
        mps[i] = in_p / 100;
    }

    // �κ� �̵���� ���
    vi[14][14] = 1;
    r_move(0, 14, 14, 1);

    cout << p_sum << endl;
    return 0;
};