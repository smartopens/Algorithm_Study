#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int n;
char d_area[102][102];
int vi[102][102];

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

void c_count(int sr, int sc, char f_c)
{
    int nr, nc;
    for (int di = 0; di < 4; di++)
    {
        nr = sr + dr[di];
        nc = sc + dc[di];
        
        if (0 > nr || n - 1 < nr || 0 > nc || n - 1 < nc) continue;
        if (d_area[nr][nc] != f_c) continue;
        if (vi[nr][nc] != 0) continue;

        vi[nr][nc] = 1;
        c_count(nr, nc, f_c);
    }
    return;
}
int main() {
    cin >> n;
    
    // 평범한 사람이 보는 색의 수
    // 적록색약인 사람이 보는 색의수
    int nor_n = 0;
    int spe_n = 0;
    string in_st = "";
    for (int r = 0; r < n; r++)
    {
        cin >> in_st;
        for (int c = 0; c < n; c++)
        {
            d_area[r][c] = in_st[c];
        }
    }

    // 색깔을 보는 구역을 세기
    for (int sr = 0; sr < n; sr++)
    {
        for (int sc = 0; sc < n; sc++)
        {
            if (vi[sr][sc] != 0) continue;

            vi[sr][sc] = 1;
            c_count(sr, sc, d_area[sr][sc]);
            nor_n += 1;
        }
    }

    memset(vi, 0, sizeof(vi));

    // 적색과 녹색을 같은 색으로 보기
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (d_area[r][c] == 'G')
            {
                d_area[r][c] = 'R';
            }
        }
    }

    // 색깔을 보는 구역을 세기
    for (int sr = 0; sr < n; sr++)
    {
        for (int sc = 0; sc < n; sc++)
        {
            if (vi[sr][sc] != 0) continue;

            vi[sr][sc] = 1;
            c_count(sr, sc, d_area[sr][sc]);
            spe_n += 1;
        }
    }

    cout << nor_n << " " << spe_n << endl;
    return 0;
};