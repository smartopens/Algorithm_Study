#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

// ╩С го аб ©Л
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };
int c_di[4] = { 1, 0, 3, 2 };

int n;
int m;
int k;
int tc;
int cnt;

struct Node {
    int num = 0;
    int di = 0;
};

int main() {
    
    cin >> tc;

    for (int t = 0; t < tc; t++) {
        cin >> n >> m >> k;
        Node board[100][100] = { {} };
        cnt = 0;

        for (int i = 0; i < k; i++) {
            int r, c, num, di;
            cin >> r >> c >> num >> di;
            Node tmp;
            tmp.num = num;
            tmp.di = di-1;
            board[r][c] = tmp;
        }

           
        while (m > 0) {
            Node new_board[100][100]= {{}};
            int max_cnt[100][100] = {{}};


            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {

                    if (board[r][c].num == 0) continue;
                    int nr, nc, di;
                    di = board[r][c].di;
                    nr = r + dr[di];
                    nc = c + dc[di];

                    if (0 > nr || nr >= n || 0 > nc || nc >= n) continue;

                    if (max_cnt[nr][nc] > 0) {
                        int new_di = new_board[nr][nc].di;
                        if (max_cnt[nr][nc] < board[r][c].num)
                        {
                            new_di = board[r][c].di;
                            max_cnt[nr][nc] = board[r][c].num;
                        }


                        new_board[nr][nc].num += board[r][c].num;
                        new_board[nr][nc].di = new_di;
                        continue;
                    }

                    if (0 == nr || nr == n - 1 || 0 == nc || nc == n - 1)
                    {
                        int new_num = board[r][c].num / 2;
                        if (new_num == 0) continue;
                        new_board[nr][nc].num = new_num;
                        new_board[nr][nc].di = c_di[board[r][c].di];
                        continue;
                    }

                    new_board[nr][nc].num = board[r][c].num;
                    max_cnt[nr][nc] = board[r][c].num;
                    new_board[nr][nc].di = board[r][c].di;

                }
                
            }
            
            copy(&new_board[0][0], &new_board[0][0] + 100*100, &board[0][0]);
            m -= 1;
        }

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                cnt += board[r][c].num;
            }
        }
        cout << "#" << t+1 << " " << cnt << endl;

    }


    return 0;
}