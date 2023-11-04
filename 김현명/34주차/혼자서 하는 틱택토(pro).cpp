#include <string>
#include <vector>

using namespace std;

// o, x를 번갈아가면서 둔다(최대 9개)

// 종료조건
// 먼저 3빙고를 만들 경우
// 가능한 수를 모두 둔 경우

// ex)
// oxo

// 1) 선공을 잘 못 둔 경우: x는 o개수와 같거나 1이하
// 2) 후공을 잘 못 둔 경우: o는 x와 같거나 1이상
// - l_num > f_num
// - l_num + 1 < f_num
// 빙고
int n = 3;
bool n_game = true;

int r_n = 0;
int f_n = 0;
int l_n = 0;

void e_count(vector<string> board)
{
    int fb_num = 0;
    int lb_num = 0;
    char now_a;
    bool is_bingo;
    bool double_w = false;
    for (int r = 0; r < n; r++)
    {
        now_a = board[r][0];
        if (now_a == '.') continue;
        is_bingo = true;
        for (int c = 1; c < n; c++)
        {
            if (now_a != board[r][c])
            {
                is_bingo = false;
                break;
            }
        }
        if (is_bingo)
        {
            if (now_a == 'O')
            {
                fb_num += 1;
            }
            else if (now_a == 'X')
            {
                lb_num += 1;
            }
        }
    }

    for (int c = 0; c < n; c++)
    {
        now_a = board[0][c];
        if (now_a == '.') continue;

        is_bingo = true;
        for (int r = 1; r < n; r++)
        {
            if (now_a != board[r][c])
            {
                is_bingo = false;
                break;
            }
        }
        if (is_bingo)
        {
            if (now_a == 'O')
            {
                fb_num += 1;
                if (fb_num == 2)
                {
                    double_w = true;
                }
            }
            else if (now_a == 'X')
            {
                lb_num += 1;
            }
        }
    }

    now_a = board[0][0];
    is_bingo = true;

    if (now_a != '.')
    {
        for (int s = 1; s < n; s++)
        {
            if (now_a != board[s][s])
            {
                is_bingo = false;
                break;
            }
        }

        if (is_bingo)
        {
            if (now_a == 'O')
            {
                fb_num += 1;
                if (fb_num == 2)
                {
                    double_w = true;
                }
            }
            else if (now_a == 'X')
            {
                lb_num += 1;
            }
        }
    }


    now_a = board[0][n - 1];
    if (now_a != '.')
    {
        is_bingo = true;
        for (int s = 1; s < n; s++)
        {
            if (now_a != board[s][n - 1 - s])
            {
                is_bingo = false;
                break;
            }
        }

        if (is_bingo)
        {
            if (now_a == 'O')
            {
                fb_num += 1;
                if (fb_num == 2)
                {
                    double_w = true;
                }
            }
            else if (now_a == 'X')
            {
                lb_num += 1;
            }
        }
    }

    if (f_n == l_n)
    {
        if (fb_num >= 1)
        {
            n_game = false;
        }
    }
    else if (f_n == l_n + 1)
    {
        if (lb_num >= 1)
        {
            n_game = false;
        }
    }
    return;
}

int solution(vector<string> board) {
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (board[r][c] == 'O')
            {
                f_n += 1;
            }
            else if (board[r][c] == 'X')
            {
                l_n += 1;
            }
        }
    }
    // l_num > f_num
    // - l_num + 1 < f_num
    if (l_n > f_n)
    {
        n_game = false;
    }
    else if (l_n + 1 < f_n)
    {
        n_game = false;
    }

    if (n_game)
    {
        e_count(board);
    }

    if (!n_game)
    {
        r_n = 0;
    }
    else
    {
        r_n = 1;
    }

    return r_n;
}