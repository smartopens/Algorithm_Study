#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

// 배열 정보 설정
int n, m, k;
int board[100][100];

struct pq_node {
    int n;
    int freq;

    bool operator < (pq_node now) const {
        if (freq > now.freq) {
            return true;
        }
        if (freq < now.freq) {
            return false;
        }
        if (n > now.n) {
            return true;
        }
        if (n < now.n) {
            return false;
        }
        return false;

    }
};


int max_r;
int max_c;

// c 연산하기
// 각 숫자의 빈도수 저장은 DAT를 활용한다.
// 숫자 빈도순, 숫자 크기 순은 우선순위큐로 처리한다.
void c_method() {
    int new_board[100][100] = { {} };

    for (int c = 0; c < max_c; c++) {
        priority_queue<pq_node> res_pq = {};
        int DAT[101] = {};

        for (int r = 0; r < max_c; r++) {
            DAT[board[r][c]] += 1;
        }

        for (int i = 1; i < 101; i++) {
            if (DAT[i] == 0) continue;

            res_pq.push({ i,DAT[i] });
        }

        int nr = 0;

        // nr == 100 일 경우 return하게 해서 최대 100개까지 저장한다.
        // 새로운 배열 맵에 저장하고 이를 나중에 복구한다.
        while (!res_pq.empty()) {
            pq_node now = res_pq.top();
            res_pq.pop();
            new_board[nr][c] = now.n;
            new_board[nr+1][c] = now.freq;
            nr += 2;

            if (nr == 100) break;
        }

        if (nr > max_r) max_r = nr;

    }

    // 배열 정보 복구하기
    for (int r = 0; r < max_r; r++) {
        for (int c = 0; c < max_c; c++) {
            board[r][c] = new_board[r][c];
        }
    }
}

// r 연산하기
// 각 숫자의 빈도수 저장은 DAT를 활용한다.
// 숫자 빈도순, 숫자 크기 순은 우선순위큐로 처리한다.
void r_method() {
    int new_board[100][100] = { {} };

    for (int r = 0; r < max_r; r++) {
        priority_queue<pq_node> res_pq = {};
        int DAT[101] = {};

        for (int c = 0; c < max_c; c++) {
            DAT[board[r][c]] += 1;
        }

        for (int i = 1; i < 101; i++) {
            if (DAT[i] == 0) continue;
            res_pq.push({i,DAT[i]});
        }
        
        int nc = 0;
        
        // nc == 100 일 경우 return하게 해서 최대 100개까지 저장한다.
        // 새로운 배열 맵에 저장하고 이를 나중에 복구한다.
        while(!res_pq.empty()){

            pq_node now = res_pq.top();
            res_pq.pop();

            new_board[r][nc] = now.n;
            new_board[r][nc + 1] = now.freq;
            nc += 2;
            if (nc == 100) break;
        }
        if (nc > max_c) max_c = nc;
    }

    // 배열 정보 복구하기
    for (int r = 0; r < max_r; r++) {
        for (int c = 0; c < max_c; c++) {
            board[r][c] = new_board[r][c];
        }
    }
}

int main() {
    // 종료 요인 설정
    int tr, tc;

    cin >> tr >> tc >> k;
    
    tr -= 1;
    tc -= 1;
    // 초기 배열 크기, 시간 선언하기
    max_r = 3;
    max_c = 3;
    int time = 0;

    // 배열 정보 입력받기
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            cin >> board[r][c];
        }
    }

    // 100초동안 연산하기
    // 연산하면서 각 배열의 행과 열크기는 변한다.
    // 이 때 가장 큰 값을 각각 저장한다.
    // 다음 연산시 최댓값으로 정해진 행,열로 처리한다.

    // 100 초가 넘을 경우 -1이다.
    while (time <= 100) {

        if (board[tr][tc] == k) break;

        if (max_r >= max_c) {
            r_method();
        }
        else {
            c_method();
        }

        time += 1;
    }

    if (time <= 100) {
        cout << time << endl;
    }
    else {
        cout << -1 << endl;
    }

    return 0;
}