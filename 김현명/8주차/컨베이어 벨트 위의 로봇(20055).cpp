#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int n, k;

// 벨트 정보: 내구도, 로봇 유무
struct node {
    int life;
    bool robot;
};

node belt[2][100];

// 단계 수, operate 종료 조건
int step;
bool done = false;

// 로봇 움직이기
// 매턴마다 벨트가 회전한다.
// 내리는 위치에서 로봇들이 모두 내리기 때문에 robot : true, false로 가능하다. 
void r_move() {
    // 내리는 위치 로봇 고려하기
    if (belt[0][n - 1].robot == true) {
        belt[0][n - 1].robot = false;
    }

    if (belt[0][n - 2].robot == true && belt[0][n - 1].life > 0) {
        belt[0][n - 1].life -= 1;
        belt[0][n - 2].robot = false;
    }

    for (int c = n - 3; c > -1; c--) {
        if (belt[0][c].robot == true && belt[0][c+1].robot == false
            && belt[0][c+1].life > 0) {

            belt[0][c + 1].robot = true;
            belt[0][c + 1].life -= 1;
            belt[0][c].robot = false;
        }
    }

    // 로봇 올리기
    if (belt[0][0].life > 0) {
        belt[0][0].robot = true;
        belt[0][0].life -= 1;
    }
    
    // operate 종료 조건 고려하기
    int d_num = 0;

    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < n; c++) {
            if (belt[r][c].life <= 0)
            {
                d_num += 1;
            }
        }
    }

    if (d_num >= k) {
        done = true;
    }
};

// 벨트 돌리기
void b_cycle() {
    node r_tmp, l_tmp;
    
    r_tmp = belt[0][n - 1];
    l_tmp = belt[1][0];

    for (int c = n - 1; c > 0; c--) {
        belt[0][c] = belt[0][c - 1];
    }

    for (int c = 0; c < n-1; c++) {
        belt[1][c] = belt[1][c + 1];
    }

    belt[0][0] = l_tmp;
    belt[1][n - 1] = r_tmp;

};

// 벨트를 돌린다.
// 로봇을 움직인다.
void operate() {
    b_cycle();
    r_move();
};

int main() {
    cin >> n >> k;

    // 벨트 정보 입력받기
    // 문제 조건에 맞게 입력받자.
    for (int c = 0; c < n; c++) {
        cin >> belt[0][c].life;
        belt[0][c].robot = false;
    }
    for (int c = n-1; c > -1; c--) {
        cin >> belt[1][c].life;
        belt[1][c].robot = false;
    }

    // 내구도 조건이 만족할때까지 operate한다.
    while (done == false) {
        operate();
        step += 1;
    }

    cout << step << endl;

    return 0;
}