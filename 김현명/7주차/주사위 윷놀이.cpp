#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

// 도로 정보
// road1 ~ road4: 겹치지 않는 도로 경우
// road5: 도로가 겹치는 경우
int road1[22] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
int road2[20] = { 0,13,16,19,25};
int road3[20] = { 0,22,24,25};
int road4[20] = { 0,28,27,26,25};
int road5[20] = { 0,30,35,40 };

// 현재 말의 위치 정보를 기록한다.
// 도로가 겹치는 경우는 vi5에서 기록한다.
// 이미 말이 있는 경우를 생각한다.
int vi1[20];
int vi2[20];
int vi3[20];
int vi4[20];
int vi5[20];

// 마지막 겹치는 구간
//road1: 20이상
//road2: 4이상
//road3: 3이상
//road4: 4이상

// 도착하는 경우
int r1_end = 21;
int r2_end = 8;
int r3_end = 7;
int r4_end = 8;

// 말 정보 설정
struct node {
    int id;
    int r_num;
    int now;
    bool end ;
};

// 말 정보
node dolls[5];

int m_nums[10];
int max_score;

node dolls_path[10];

// 주사위의 경우에서 말들을 움직인다.
// 최대 점수를 갱신한다.
void dfs(int m_id, int score){
    // 모든 주사위만큼 움직였다.
    if (m_id >= 10) {
        if (score > max_score) {
            max_score = score;

        }
        return;
    }

    // 1번에서 4번말을 움직인다.
    // - 현재 말의 r_type에 따른 경로로 움직인다.
    // - 말을 움직일때 다음 말의 경우를 본다.
    // - 현재 말이 도착한 말일 경우 다음 말을 생각한다.
    for (int i = 1; i < 5; i++) {
        node doll = dolls[i];
        int to = doll.now + m_nums[m_id];
        int r_type = doll.r_num;

        // 말이 이미 도착한 경우
        if (doll.end == true) continue;

        // 1번 도로에 있는 경우
        if (r_type == 1) {
            if (vi1[to] == 1) continue;
            
            if (to == 5 || to == 10 || to == 15) {
                // 다음 말 위치가 파랑 지역 즉, 도로 2, 3, 4로 가는 경우
                int n_road = to / 5 + 1;

                // 이전 방문 기록과 앞으로의 방문 기록을 갱신한다.
                if (n_road == 2) {
                    if (vi2[0] == 1) continue;
                    vi1[doll.now] = 0;
                    vi2[0] = 1;
                }
                else if (n_road == 3) {
                    if (vi3[0] == 1) continue;
                    vi1[doll.now] = 0;
                    vi3[0] = 1;
                }
                else if (n_road == 4) {
                    if (vi4[0] == 1) continue;
                    vi1[doll.now] = 0;
                    vi4[0] = 1;
                }

                // 말의 도로 타입, 도로에서의 위치를 갱신한다.
                dolls[i].r_num = n_road;
                dolls[i].now = 0;

                dolls_path[m_id] = doll;
                dfs(m_id + 1, score + road1[to]);
                dolls_path[m_id] = {};


                // 앞서 수정된 정보들을 복구한다.
                dolls[i].r_num = 1; 
                dolls[i].now = doll.now;

                if (n_road == 2) {
                    vi1[doll.now] = 1;
                    vi2[0] = 0;
                }
                else if (n_road == 3) {
                    vi1[doll.now] = 1;
                    vi3[0] = 0;
                }
                else if (n_road == 4) {
                    vi1[doll.now] = 1;
                    vi4[0] = 0;
                }
                continue;
            }
            else {
                // 말이 도착하는 경우
                if (to > 19) {
                    // 도착할 때 말은 road5와 vi5로 생각한다.
                    int vi_to = to - 17;
                    if (vi5[vi_to] == 1) continue;

                    vi1[doll.now] = 0;
                    dolls[i].r_num = 5;
                    dolls[i].now = vi_to;
                    vi5[vi_to] = 1;

                    dolls_path[m_id] = doll;

                    // road1의 끝에 도착하는 경우, road5의 중간에 도착하는 경우
                    if (vi_to == 0) {
                        dfs(m_id + 1, score + road1[to]);
                    }
                    else {
                        dfs(m_id + 1, score + road5[vi_to]);
                    }
                    dolls_path[m_id] = {};

                    vi5[vi_to] = 0;
                    dolls[i].now = doll.now;
                    dolls[i].r_num = 1;
                    vi1[doll.now] = 1;
                    continue;
                }

                // 이전 방문 기록과 앞으로의 방문 기록을 갱신한다.
                vi1[doll.now] = 0;
                dolls[i].now = to;
                vi1[to] = 1;

                dolls_path[m_id] = doll;
                dfs(m_id + 1, score + road1[to]);
                dolls_path[m_id] = {};

                vi1[to] = 0;
                dolls[i].now = doll.now;
                vi1[doll.now] = 1;
            }
        }
        // 2번 도로에 있는 경우
        else if (r_type == 2) {
            if (to > 3) {
                int vi_to = to - 4;
                if (vi5[vi_to] == 1) continue;

                vi2[doll.now] = 0;
                dolls[i].r_num = 5;
                dolls[i].now = vi_to;
                vi5[vi_to] = 1;

                dolls_path[m_id] = doll;
                if (vi_to == 0) {
                    dfs(m_id + 1, score + road2[to]);
                }
                else {
                    dfs(m_id + 1, score + road5[vi_to]);
                }
                dolls_path[m_id] = {};

                vi5[vi_to] = 0;
                dolls[i].r_num = 2;
                dolls[i].now = doll.now;
                vi2[doll.now] = 1;
                continue;
            }

            if (vi2[to] == 1) continue;

            vi2[doll.now] = 0;
            dolls[i].now = to;
            vi2[to] = 1;

            dolls_path[m_id] = doll;
            dfs(m_id + 1, score + road2[to]);
            dolls_path[m_id] = {};

            vi2[to] = 0;
            dolls[i].now = doll.now;
            vi2[doll.now] = 1;
        }

        // 3번 도로에 있는 경우
        else if (r_type == 3) {
            if (to > 2) {
                int vi_to = to - 3;
                if (vi5[vi_to] == 1) continue;

                vi3[doll.now] = 0;
                dolls[i].r_num = 5;
                dolls[i].now = vi_to;
                vi5[vi_to] = 1;

                dolls_path[m_id] = doll;
                if (vi_to == 0) {
                    dfs(m_id + 1, score + road3[to]);
                }
                else {
                    dfs(m_id + 1, score + road5[vi_to]);
                }
                dolls_path[m_id] = {};

                vi5[vi_to] = 0;
                dolls[i].r_num = 3;
                dolls[i].now = doll.now;
                vi3[doll.now] = 1;
                continue;
            }

            if (vi3[to] == 1) continue;

            vi3[doll.now] = 0;
            dolls[i].now = to;
            vi3[to] = 1;

            dolls_path[m_id] = doll;
            dfs(m_id + 1, score + road3[to]);
            dolls_path[m_id] = {};

            vi3[to] = 0;
            dolls[i].now = doll.now;
            vi3[doll.now] = 1;
        }

        // 4번 도로에 있는 경우
        else if (r_type == 4) {
            if (to > 3) {
                int vi_to = to - 4;
                if (vi5[vi_to] == 1) continue;

                vi4[doll.now] = 0;
                dolls[i].r_num = 5;
                dolls[i].now = vi_to;
                vi5[vi_to] = 1;

                dolls_path[m_id] = doll;
                if (vi_to == 0) {
                    dfs(m_id + 1, score + road4[to]);
                }
                else {
                    dfs(m_id + 1, score + road5[vi_to]);
                }
                dolls_path[m_id] = {};

                vi5[vi_to] = 0;
                dolls[i].r_num = 4;
                dolls[i].now = doll.now;
                vi4[doll.now] = 1;
                continue;
            }

            if (vi4[to] == 1) continue;

            vi4[doll.now] = 0;
            dolls[i].now = to;
            vi4[to] = 1;

            dolls_path[m_id] = doll;
            dfs(m_id + 1, score + road4[to]);
            dolls_path[m_id] = {};

            vi4[to] = 0;
            dolls[i].now = doll.now;
            vi4[doll.now] = 1;
        }

        // 5번 도로에 있는 경우
        else if (r_type == 5) {
            if (to > 3) {
                // 말이 도착하는 경우
                // 이전 방문 기록을 갱신한다.
                vi5[doll.now] = 0;
                dolls[i].end = true;
                dolls_path[m_id] = doll;
                dfs(m_id + 1, score);
                dolls_path[m_id] = {};
                dolls[i].end = false;
                vi5[doll.now] = 1;
                continue;
            }

            if (vi5[to] == 1) continue;

            vi5[doll.now] = 0;
            dolls[i].now = to;
            vi5[to] = 1;

            dolls_path[m_id] = doll;
            dfs(m_id + 1, score + road5[to]);
            dolls_path[m_id] = {};

            vi5[to] = 0;
            dolls[i].now = doll.now;
            vi5[doll.now] = 1;
        }
    }
}

int main() {
    // 주사위 경우 입력 받기
    for (int i = 0; i < 10; i++) {
        cin >> m_nums[i];
    }

    // 말 정보 초기화
    // 말 id, road 타입, road내 위치, 도착 정보
    for (int i = 1; i < 5; i++) {
        dolls[i] = { i,1,0,false };
    }

    // 경우의 수 보기
    dfs(0, 0);
    
    // 최대 정답 경우
    cout << max_score << endl;

    return 0;
}