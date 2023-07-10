#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

int sr, sc;
int tr, tc;

int min_dist = 21e8;

int main() {
    // 코코의 위치, 목표 위치 입력하기 
    cin >> sc >> sr;
    cin >> tc >> tr;

    int c1, r1, c2, r2, c3, r3, c4, r4;
    cin >> c1 >> r1 >> c2 >> r2 >> c3 >> r3 >> c4 >> r4;

    // dist1: 그냥 걸어가는 경우 
    // dist2: 코코위치부터 지하철까지의 최소 경로
    // dist3: 목표 위치부터 지하철까지의 최소 경로

    int dist1 = abs(tc - sc) + abs(tr - sr);
    int dist2 = 21e8;
    int dist3 = 21e8;

    // 지하철 구간으로부터 코코위치와 목표위치까지의 거리를 각각 갱신한다.

    // 아래 가로 방향 탐색
    for (int c = c1; c < c2 + 1; c++) {
        if (abs(c - sc) + abs(r1 - sr) < dist2) {
            dist2 = abs(c - sc) + abs(r1 - sr);
        }
        if (abs(c - tc) + abs(r1 - tr) < dist3) {
            dist3 = abs(c - tc) + abs(r1 - tr);
        }
    }

    // 위 가로 방향 탐색
    for (int c = c1; c < c2 + 1; c++) {
        if (abs(c - sc) + abs(r3 - sr) < dist2) {
            dist2 = abs(c - sc) + abs(r3 - sr);
        }

        if (abs(c - tc) + abs(r3 - tr) < dist3) {
            dist3 = abs(c - tc) + abs(r3 - tr);
        }
    }

    // 왼쪽 세로 방향 탐색
    for (int r = r2; r < r3 + 1; r++) {
        if (abs(c1 - sc) + abs(r - sr) < dist2) {
            dist2 = abs(c1 - sc) + abs(r - sr);
        }

        if (abs(c1 - tc) + abs(r - tr) < dist3) {
            dist3 = abs(c1 - tc) + abs(r - tr);
        }
    }

    // 오른쪽 세로 방향 탐색
    for (int r = r2; r < r3 + 1; r++) {
        if (abs(c3 - sc) + abs(r - sr) < dist2) {
            dist2 = abs(c3 - sc) + abs(r - sr);
        }

        if (abs(c3 - tc) + abs(r - tr) < dist3) {
            dist3 = abs(c3 - tc) + abs(r - tr);
        }
    }

    // 그냥 걷는 경우와 지하철타는 경우를 비교한다.
    min_dist = min(dist1, dist2 + dist3);
    cout << min_dist << endl;

    return 0;
}