#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <iostream>

using namespace std;

// 도로 정보 선언
// 택시 위치 저장
int n, m;
int road[20][20];
int tr, tc;

// 연료 수, 임무 수행 가능 여부 저장
int f_num;
bool possible = true;

// 승객 이동 조건
struct m_node {
    int sr;
    int sc;
    int er;
    int ec;
    bool done;
};

// 어떤 승객에게 갈지를 정할때 사용한다.
struct p_node {
    int sr;
    int sc;
    int er;
    int ec;
    int id;

    bool operator < (p_node now) const {
        if (sr > now.sr) {
            return true;
        }
        if (sr < now.sr) {
            return false;
        }
        if (sc > now.sc) {
            return true;
        }
        if (sc < now.sr) {
            return false;
        }
        return false;
    }
};

// 행, 열 조건을 위해 사용하는 자료구조
priority_queue<p_node> s_m_info;

// 기존 승객 이동 정보 저장
m_node ori_m_info[400];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

struct node {
    int r;
    int c;
};

int move_to(int er, int ec) {
    queue<node> q;
    q.push({ tr,tc });

    int vi[20][20] = { {} };
    vi[tr][tc] = 1;

    if (tr == er && tc == ec) {
        return 0;
    }

    while (!q.empty()) {
        node now = q.front();
        q.pop();

        int nr, nc;

        for (int i = 0; i < 4; i++) {
            nr = now.r + dr[i];
            nc = now.c + dc[i];

            if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
            if (road[nr][nc] == 1) continue;
            if (vi[nr][nc] != 0) continue;

            vi[nr][nc] = vi[now.r][now.c] + 1;

            if (nr == er && nc == ec) {
                return vi[nr][nc] - 1;
            }

            q.push({ nr,nc });
        }
    }
    return -1;
};

// 택시위치에서 가장 가까운 승객들을 찾는다.
// 연료와 거리 수를 고려하고 이동한다.
// 승객위치로 이동 후, 해당 고객의 목표지점으로 이동한다. 
// 연료 정보를 갱신한다.
void t_move() {
    // 행 열 조건에 맞게 우선순위큐에 저장한다.
    priority_queue<p_node> q_m_info = {};

    for (int i = 0; i < m; i++) {
        q_m_info.push({ ori_m_info[i].sr ,ori_m_info[i].sc ,ori_m_info[i].er ,ori_m_info[i].ec ,i });
    }

    // 거리조건 설정
    int min_dist = 21e8;

    // 승객위치: nr,nc
    // 목표위치: nr2,nc2
    int nr = -1;
    int nc = -1;
    int nr2 = -1;
    int nc2 = -1;

    int id = 0;

    // 가장 가깝고 문제 조건에 맞는 승객을 찾는다.
    while (!q_m_info.empty()) {
        p_node now = q_m_info.top();
        q_m_info.pop();

        // 임무 수행 안된 승객을 고려한다.
        if (ori_m_info[now.id].done == true) continue;
        int er, ec;
        er = now.sr;
        ec = now.sc;

        // 거리 계산
        int dist = move_to(er, ec);

        // 가장 가까운 승객 정보 저장하기
        if (dist != -1 && dist < min_dist) {
            nr = er;
            nc = ec;
            min_dist = dist;
            id = now.id;

            nr2 = now.er;
            nc2 = now.ec;
        }
    }

    // 고객 위치로 이동 가능한지를 본다.
    if (nr == -1 && nc == -1)
    {
        possible = false;
        return;
    }

    // 연료수를 고려한다.
    if (f_num <= min_dist) {
        possible = false;
        return;
    }

    // 도착한 승객 정보 저장
    ori_m_info[id].done = true;
    f_num -= min_dist;
    
    // 목표로 이동하기
    tr = nr;
    tc = nc;

    int dist2 = move_to(nr2, nc2);

    // 연료 정보 고려 및 저장하기
    if (dist2 == -1 || f_num - dist2 < 0)
    {
        possible = false;
        return;
    }

    f_num += dist2;
    tr = nr2;
    tc = nc2;

};

int main() {
    cin >> n >> m >> f_num;

    // 도로 정보 입력
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> road[r][c];
        }
    }

    // m번 임무 수행
    // 택시 위치 입력
    int m_num = m;
    cin >> tr >> tc;
    tr -= 1;
    tc -= 1;

    // 승객 이동 정보 저장
    for (int i = 0; i < m; i++) {
        int sr, sc, er, ec;
        cin >> sr >> sc >> er >> ec;

        sr -= 1;
        sc -= 1;
        er -= 1;
        ec -= 1;

        ori_m_info[i] = { sr, sc, er, ec,false };
    }

    // m번 임무를 수행한다.
    // 임무 수행이 가능하다면 계속 수행한다.
    while (m_num > 0) {
        t_move();
        m_num -= 1;
        if (possible == false) {
            break;
        }
    }

    if (possible == false) {
        cout << -1 << endl;
    }
    else if (possible == true) {
        cout << f_num << endl;
    }
   return 0;
}