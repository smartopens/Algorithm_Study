#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

// 기본 지역 셋팅
int n;
int sea[20][20];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

// 우선순위 큐 사용하기
struct node {
    int r;
    int c;
};

struct pq_node {
    int r;
    int c;
    int dist;

    bool operator < (pq_node now) const {
        if (dist > now.dist) {
            return true;
        }
        if (dist < now.dist) {
            return false;
        }
        return false;
    }
};


// 상어 정보
// 상어 위치, 현재 크기, 먹은 정도
int shark_r, shark_c;
int s_size;
int s_eat;

// 먹은 물고기, 상어와 물고기까지의 거리, 지난 시간
int fish_num;
int fish_dist;
int w_time;


// 물고기 탐색
// 현재 사이즈보다 작거나 같다면 이동 가능하다.
// 현재 사이즈보다 작으면 target으로 지정 가능하다.
pq_node detect_path(int sr, int sc, int tr, int tc) {
    queue<node>q = {};
    q.push({ sr,sc });
    int visited[20][20] = { {} };

    visited[sr][sc] = 1;

    while (!q.empty()) {
        node now = q.front();
        q.pop();

        // 물고기까지 올 수 있는 경우 거리와 함께 return한다.
        if (now.r == tr && now.c == tc) {
            int now_dist = visited[now.r][now.c] - 1;
            return {tr,tc,now_dist};
        }

        int nr, nc;
        for (int i = 0; i < 4; i++) {
            nr = now.r + dr[i];
            nc = now.c + dc[i];

            if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
            if (visited[nr][nc] != 0) continue;
            if (s_size < sea[nr][nc]) continue;

            visited[nr][nc] = visited[now.r][now.c] + 1;
            q.push({ nr,nc });
        }
    }

    return { -1,-1,-1 };
}

// 상어 출발하기
void go_shark() {
    // 먹을 수 있는 물고기 탐색
    // 해당 물고기를 먹을 수 있다면 우선순위 큐에 dist와 함께 저장한다.
    priority_queue<pq_node>pq = {};

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (0 < sea[r][c] && s_size > sea[r][c]) {
                pq_node tmp;
                tmp = detect_path(shark_r, shark_c, r, c);

                if (tmp.dist == -1) continue;
                
                pq.push(tmp);
            }
        }
    }

    // 거리가 가장 가까운 물고기로 정보 갱신
    // 상어 좌표, 전체시간, 상어size, 상어 먹은정도 갱신
    // 물고기를 다먹었다면 return한다.
    if (!pq.empty()) {
        pq_node now = pq.top();
        shark_r = now.r;
        shark_c = now.c;

        w_time += now.dist;
        fish_num -= 1;
        s_eat += 1;

        if (s_eat >= s_size) {
            s_size += 1;
            s_eat = 0;
        }

        if (fish_num == 0) {
            return;
        }

        sea[shark_r][shark_c] = 0;
        
        go_shark();
    }
}

int main() {
    // 상어 size 초기화
    cin >> n;
    s_size = 2;

    // 물고기, 상어 정보 입력
    // fish_num은 물고기를 다 먹으면 바로 return할때 사용한다.
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> sea[r][c];

            if (0 < sea[r][c] && 9 != sea[r][c]) {
                fish_num += 1;
            }
            // 상어위치 정보 저장, 좌표로 활용
            else if (9 == sea[r][c]) {
                shark_r = r;
                shark_c = c;
                sea[r][c] = 0;
            }
        }
    }

    // 탐색
    go_shark();

    // 출력
    cout << w_time << endl;

    return 0;
}