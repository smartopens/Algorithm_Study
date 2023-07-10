#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <math.h>
#include <iostream>

using namespace std;

int n, q;

// 얼음 정보 설정
int ice[102][102];
int new_ice[102][102];
int visited[102][102];

// 방향
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

// 남는 얼음 수
// 최대 얼음 덩어리 크기
// 얼음 덩어리 크기
int i_num;
int max_g_num ;
int g_num;

// 얼음 덩어리 탐색하기
// 덩어리 크기도 센다.
void g_view(int r, int c)
{
    int nr, nc;

    for (int di = 0; di < 4; di++)
    {
        nr = r + dr[di];
        nc = c + dc[di];

        if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
        if (ice[nr][nc] == 0) continue;
        if (visited[nr][nc] != 0) continue;

        visited[nr][nc] = 1;
        g_num += 1;
        g_view(nr, nc);
    }
};

// 얼음 녹이기
// 조건에 유의해서 1씩 녹이기
void storm()
{
    memset(new_ice, 0, sizeof(new_ice));
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (ice[r][c] == 0) continue;

            int i_num = 0;
            int nr, nc;
            bool melt = true;

            for (int di = 0; di < 4; di++)
            {
                nr = r + dr[di];
                nc = c + dc[di];

                if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
                if (ice[nr][nc] == 0) continue;

                i_num += 1;
            }

            if(i_num < 3)
            {
                new_ice[r][c] = ice[r][c] - 1;
            }
            else {
                new_ice[r][c] = ice[r][c];
            }
        }
    }
    memcpy(ice, new_ice, sizeof(new_ice));
};

// 특정지역 회전하기
// new_ice 자료를 활용한다.
void i_cycle(int sr, int sc, int m)
{
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < m; c++)
        {
            new_ice[sr+r][sc+c] = ice[sr+m-1-c][sc + r];
        }
    }


    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < m; c++)
        {
            ice[sr + r][sc + c] = new_ice[sr + r][sc + c];
        }
    }


};

// 부분화된 지역들 단위로 90도 회전한다.
// m 크기와 시작 인덱스를 활용한다.
void fire(int m)
{
    memset(new_ice, 0, sizeof(new_ice));
    for (int sr = 0; sr < n; sr+=m)
    {
        for (int sc = 0; sc < n; sc+=m)
        {
            i_cycle(sr, sc, m);
        }
    }

};

int main() {
    cin >> n >> q;

    // 사이즈 맞추기
    n = pow(2, n);

    // 얼음 정보 입력 받기
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            cin >> ice[r][c];
        }
    }

    // 마법 시전하기
    // fire: 얼음 회전
    // storm: 얼음 녹이기
    for (int qi = 0; qi < q; qi++)
    {
        int m;
        cin >> m;

        fire(pow(2,m));
        storm();
    }

    // 남은 얼음 개수 세기
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (ice[r][c] == 0) continue;
            i_num += ice[r][c];
        }
    }

    // 얼음 덩어리들의 개수 세기
    // 얼음이 있는 지역에서 g_view를 한다.
    // g_view는 해당 지역에서 가능한 만큼 얼음을 보고 덩어리 크기를 갱신한다.
    // 방문기록을 남겨서 탐색과 중복방지에 사용한다.
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (ice[r][c] == 0) continue;
            if (visited[r][c] != 0) continue;

            g_num = 1;
            visited[r][c] = 1;
            g_view(r,c);

            // 최대 얼음 덩어리 수 갱신
            if (g_num > max_g_num) {
                max_g_num = g_num;
            }
        }
    }
    
    cout << i_num << endl;
    cout << max_g_num << endl;

    return 0;
};