#include <iostream>
#include <cstring>

using namespace std;

// 성장, 번식
// 나무는 인접 개수만큼 성장(동시)
// 나무는 인접칸으로 번식(동시), 예외: 제초제, 다른 나무, 벽

// 억제
// 뿌렸을 때 나무를 가장 많이 없애는 경우(대각 k)
// 벽이나 빈공간:멈춤
// c년 동안 제초제
int n;
int m, c, k;

int f_board[22][22];
int f_tmp[22][22];
int e_board[22][22];

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

int e_dr[4] = { -1,1,1,-1 };
int e_dc[4] = { 1,1,-1,-1 };

int total_en;

int main()
{
	cin >> n >> m >> k >> c;
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			cin >> f_board[r][c];
		}
	}

	for (int ti = 0; ti < m; ti++)
	{
		int g_w, s_w, nr, nc;
		g_w = 0;
		s_w = 0;

		// 성장
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < n; c++)
			{
				if (f_board[r][c] > 0)
				{
					g_w = 0;
					for (int di = 0; di < 4; di++)
					{
						nr = r + dr[di];
						nc = c + dc[di];

						if (0 > nr || n - 1 < nr || 0 > nc || n - 1 < nc) continue;
						if (f_board[nr][nc] > 0)
						{
							g_w += 1;
						}
					}
					f_board[r][c] += g_w;
				}
			}
		}

		// 번식
		memcpy(f_tmp, f_board, sizeof(f_board));
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < n; c++)
			{
				if (f_tmp[r][c] > 0)
				{
					s_w = 0;
					for (int di = 0; di < 4; di++)
					{
						nr = r + dr[di];
						nc = c + dc[di];

						if (0 > nr || n - 1 < nr || 0 > nc || n - 1 < nc) continue;
						if (f_tmp[nr][nc] == 0)
						{
							if (e_board[nr][nc] > 0) continue;
							s_w += 1;
						}
					}

					for (int di = 0; di < 4; di++)
					{
						nr = r + dr[di];
						nc = c + dc[di];

						if (0 > nr || n - 1 < nr || 0 > nc || n - 1 < nc) continue;
						if (f_tmp[nr][nc] == 0)
						{
							if (e_board[nr][nc] > 0) continue;
							f_board[nr][nc] += f_tmp[r][c] / s_w;
						}
					}
				}
			}
		}

		// 억제
		int max_en = 0;
		int now_en = 0;
		int e_r = 0;
		int e_c = 0;
		bool t_em = true;
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < n; c++)
			{
				if (f_board[r][c] > 0)
				{
					// 제초제 위치 정하기
					now_en = 0;
					now_en += f_board[r][c];
					for (int di = 0; di < 4; di++)
					{
						for (int s = 1; s < k + 1; s++)
						{
							nr = r + e_dr[di]*s;
							nc = c + e_dc[di]*s;

							if (0 > nr || n - 1 < nr || 0 > nc || n - 1 < nc) continue;
							if (f_board[nr][nc] == -1 || f_board[nr][nc] == 0)
							{
								break;
							}
							else if (f_board[nr][nc] > 0)
							{
								now_en += f_board[nr][nc];
							}
						}
					}
					if (max_en < now_en)
					{
						e_r = r;
						e_c = c;
						max_en = now_en;
						t_em = false;
					}
				}
			}
		}

		if (t_em) break;

		// 나무 제거 수 기록, 제초제 갱신
		total_en += f_board[e_r][e_c];
		f_board[e_r][e_c] = 0;
		e_board[e_r][e_c] = c+1;
		for (int di = 0; di < 4; di++)
		{
			for (int s = 1; s < k + 1; s++)
			{
				nr = e_r + e_dr[di] * s;
				nc = e_c + e_dc[di] * s;

				if (0 > nr || n - 1 < nr || 0 > nc || n - 1 < nc) continue;
				if (f_board[nr][nc] == -1 || f_board[nr][nc] == 0)
				{
					e_board[nr][nc] = c+1;
					break;
				}
				else if (f_board[nr][nc] > 0)
				{
					total_en += f_board[nr][nc];
					f_board[nr][nc] = 0;
					e_board[nr][nc] = c+1;
				}
			}
		}

		// 제초제 감소
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < n; c++)
			{
				if (e_board[r][c] > 0)
				{
					e_board[r][c] -= 1;
				}
			}
		}
	}

	cout << total_en << endl;
	return 0;
}