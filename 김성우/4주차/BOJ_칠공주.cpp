#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

struct pos {
    int row;
    int col;
};

char map[10][10];
int selected[27];
int ans = 0;
int isvisited[10][10];
queue<pos> q;
int temp_map[10][10];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void input();
void sol();
bool checkadj();

int main() {

    input();

    sol();

    cout << ans;

}

bool checkadj() {

    memset(isvisited, 0, sizeof(isvisited));
    memset(temp_map, 0, sizeof(temp_map));

    int y, x;
    for (int i = 0; i < 25; i++) {
        if (selected[i] == 0) continue;

        y = i / 5;
        x = i % 5;

        temp_map[y][x] = 1;

    }

    q.push({ y, x });

    isvisited[y][x] = 1;

    int cnt = 1;
    while (!q.empty()) {

        pos now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {

            int nr = now.row + dr[i];
            int nc = now.col + dc[i];

            if (nr < 0 || nc < 0 || nr >= 5 || nc >= 5) continue;
            if (isvisited[nr][nc] == 1) continue;

            if (temp_map[nr][nc] == 1) {
                cnt++;
                q.push({ nr, nc });
                isvisited[nr][nc] = 1;
            }

        }
    }
    if (cnt == 7) return true;
    else return false;


}

void dfs(int idx, int total, int s_cnt) {

    if (total == 7) {

        if (s_cnt >= 4) {
            if (checkadj()) ans++;
        }

        return;
    }

    for (int i = idx; i < 25; i++) {

        if (selected[i]) continue;
        selected[i] = 1;
        dfs(i, total + 1, s_cnt + (map[i/5][i%5] == 'S'));
        selected[i] = 0;

    }
}

void sol() {

    dfs(0, 0, 0);

}

void input() {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> map[i][j];
        }
    }
}
