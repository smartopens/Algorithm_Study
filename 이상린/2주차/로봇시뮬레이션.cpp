#include <iostream>
#include <vector>

using namespace std;

// N, W, E, S

struct Robot {
    int y, x, r;
    // N:0 W:1 S:2 E:3
};

int Dr[2][4] = {
    -1,0,1,0,
    0,-1,0,1,
};

int main()
{
    // A: 가로 B: 세로
    int A, B, N, M; cin >> A >> B >> N >> M;
    int MAP[100][100] = { 0 };
    vector<Robot> rv;

    for (int i = 0;i < N;++i) // 로봇의 초기 위치(x,y)와 방향
    {
        int x, y;
        char r;
        cin >> x >> y >> r;

        MAP[B - y][x-1] = rv.size()+1;

        int temp;
        if (r == 'N') temp = 0;
        else if (r == 'W') temp = 1;
        else if (r == 'S') temp = 2;
        else if (r == 'E') temp = 3;

        rv.push_back({ B-y,x-1,temp });
    }

    int flag = 0;
    for (int i = 0;i < M;++i) // 명령
    {
        // 명령내리는 로봇, 명령의 종류, 명령 반복 횟수(1<= <=100)
        int robot, repeat;
        char go;
        cin >> robot >> go >> repeat;
        robot--;
        /*
        명령
        L : 로봇 기준 왼쪽 90도
        R: 로봇 기준 오른쪽 90도
        F: 로봇 기준 앞으로 한칸
        */
        if (go == 'L')
        {
            rv[robot].r = (rv[robot].r + repeat) % 4;
            
        }
        else if (go == 'R')
        {
            rv[robot].r = (rv[robot].r + 100 - repeat) % 4;
        }
        else if (go == 'F')
        {
            // 충돌하는지 판별해야함
            for (int j = 0;j < repeat;j++)
            {
                MAP[rv[robot].y][rv[robot].x] = 0;
                rv[robot].y += Dr[0][rv[robot].r];
                rv[robot].x += Dr[1][rv[robot].r];

                if (rv[robot].y < 0 || rv[robot].x < 0 || rv[robot].y >= B || rv[robot].x >= A)
                {
                    cout << "Robot " << robot + 1 << " crashes into the wall";
                    flag = 1;
                    break;
                }

                if (MAP[rv[robot].y][rv[robot].x] > 0)
                {
                    cout << "Robot " << robot + 1 << " crashes into robot " << MAP[rv[robot].y][rv[robot].x];
                    flag = 1;
                    break;
                }

                MAP[rv[robot].y][rv[robot].x] = robot+1;
            }
        }

        if (flag == 1) break;
    }

    // 출력 : 시뮬레이션 결과
    // 문제 없는 경우 : OK
    if (!flag) cout << "OK";

    return 0;
}