#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>

using namespace std;

// 초기 지역 설정
int n, m, time;
int board[50][50];
int tmp_board[50][50];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

// 공기청정기 위치 정보
struct node {
    int r;
    int c;
};

node cleaner[2];

int main() {
    cin >> n >> m >> time;

    // 공기청정기 위치, 전체 먼지 양
    int node_i = 0;
    int m1_r, m1_c, m2_r, m2_c;
    int total_dust = 0;

    // 미세먼지 정보 입력
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            cin >> board[r][c];
            
            if (board[r][c] == -1) {
                cleaner[node_i] = { r,c };
                board[r][c] = 0;
                node_i += 1;
            }
        }
    }

    // 공기 청정기 위치 저장
    m1_r = cleaner[0].r;
    m1_c = cleaner[0].c;
    m2_r = cleaner[1].r;
    m2_c = cleaner[1].c;

    // 시간 흐르기
    for (int sec = 0; sec < time; sec++) {
        // 임시 Board 초기화
        memset(tmp_board, 0, sizeof(tmp_board));

        // 미세 먼지 확산
        // 만약 확산되는 지점이 공기 청정기가 있는곳이면 무시한다.
        // 미세 먼지는 공통영역에 퍼질 수 있다.
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                int dust = 0;
                int nr, nc;

                if (board[r][c] > 0) {
                    tmp_board[r][c] += board[r][c];
                    for (int di = 0; di < 4; di++) {
                        nr = r + dr[di];
                        nc = c + dc[di];

                        if (0 > nr || n <= nr || 0 > nc || m <= nc) continue;
                        if((nr == m1_r && nc == m1_c) || (nr == m2_r && nc == m2_c)) continue;
                        tmp_board[nr][nc] += (board[r][c] / 5);
                        dust += (board[r][c] / 5);
                    }
                    tmp_board[r][c] -= dust;
                }
            }
        }

        // 먼지 정보 갱신
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                board[r][c] = tmp_board[r][c];
            }
        }


        // 공기 청정기 작동
        
        // 위, 반시계방향
        // 처음 윗방향으로 미세먼지를 흡입한다.
        // 공기 청정기에 오는 미세먼지를 정화 시키고 나머지 방향은 이것을 고려하지 않고 동작시킨다.
        for (int r = m1_r; r > 0; r--) {
            board[r][0] = board[r - 1][0];
        }

        board[m1_r][m1_c] = 0;

        for (int c = 0; c < m - 1; c++) {
            board[0][c] = board[0][c + 1];
        }

        for (int r = 0; r < m1_r; r++) {
            board[r][m - 1] = board[r + 1][m - 1];
        }

        for (int c = m - 1; c > 0; c--) {
            board[m1_r][c] = board[m1_r][c - 1];
        }

        // 아래, 시계방향
        // 처음 아래방향으로 미세먼지를 흡입한다.
        // 공기 청정기에 오는 미세먼지를 정화 시키고 나머지 방향은 이것을 고려하지 않고 동작시킨다.
        for (int r = m2_r; r < n-1; r++) {
            board[r][0] = board[r + 1][0];
        }

        board[m2_r][m2_c] = 0;

        for (int c = 0; c < m - 1; c++) {
            board[n-1][c] = board[n-1][c + 1];
        }

        for (int r = n-1; r > m2_r; r--) {
            board[r][m - 1] = board[r - 1][m-1];
        }

        for (int c = m - 1; c > 0; c--) {
            board[m2_r][c] = board[m2_r][c - 1];
        }
    }

    // 총 미세먼지 입력
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            total_dust += board[r][c];
        }
    }

    cout << total_dust << endl;

    return 0;
}