#include <iostream>

using namespace std;

// 플레이어 이동
// 바라보는 방향으로 1 이동 (정반대: 방향 전환, +1)

// b_area : 총, 플레이어

// players node: 위치, 방향, 초기능력치, 총, 점수

// 대결
// 질 경우: 총을 내려두고 다음 방향으로 이동(우측 회전)
// 이길 경우: 가장 강한 총을 가지고 점수 획득
// 점수: 두플레이어 공합의 차이

// 대결자들 정보맵
int p_area[22][22];
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

struct p_no {
	int di;
	int sv;
	int gp;
	int sco;
};

p_no players[402];

// 총 정보 맵
int g_area[22][22];

int n, m;
int k;

void p_move(int pv, int sr, int sc){

	int nr1, nc1, di1;
	di1 = players[pv].di;
	nr1 = sr + dr[di1];
	nc1 = sc + dc[di1];

	int ndi1 = 0;
	if (nr1 < 0 || nr1 > n - 1 || nc1 < 0 || nc1 > n - 1)
	{
		di1 = (di1 + 2) % 4;
		nr1 = sr + dr[di1];
		nc1 = sc + dc[di1];
	}

	players[pv].di = di1;
	p_area[sr][sc] = 0;
	// 이긴 사람
	int nr2, nc2, di2;
	
	//  진 사람
	int nr3, nc3, di3;
	int sco;
	int to_sco, to_v;
	if (p_area[nr1][nc1] > 0)
	{
		to_v = p_area[nr1][nc1];
		sco = players[pv].sv + players[pv].gp;
		to_sco = players[p_area[nr1][nc1]].sv + players[p_area[nr1][nc1]].gp;

		bool sco_first = false;
		if (sco == to_sco)
		{
			if (players[pv].sv > players[to_v].sv)
			{
				sco_first = true;
			}
		}

		if (sco > to_sco || sco_first == true)
		{
			for (int sdi = 0; sdi < 4; sdi++)
			{
				nr3 = nr1 + dr[(players[to_v].di + sdi)%4];
				nc3 = nc1 + dc[(players[to_v].di + sdi)%4];
				di3 = (players[to_v].di + sdi) % 4;

				if (nr3 < 0 || nr3 > n - 1 || nc3 < 0 || nc3 > n - 1) continue;
				if (p_area[nr3][nc3] > 0) continue;
				break;
			}
			int get_sco = abs((players[pv].gp + players[pv].sv) - (players[to_v].gp + players[to_v].sv));
			players[pv].sco += get_sco;
			// 총 내려놓기
			g_area[nr1][nc1] = players[to_v].gp;
			players[to_v].gp = g_area[nr3][nc3];
			players[to_v].di = di3;

			// 진 사람 이동
			p_area[nr3][nc3] = to_v;

			// 이긴 사람 총 교환
			int max_gp = max(players[pv].gp, g_area[nr1][nc1]);
			int min_gp = min(players[pv].gp, g_area[nr1][nc1]);
			
			g_area[nr1][nc1] = min_gp;
			players[pv].gp = max_gp;
			p_area[nr1][nc1] = pv;

		}
		else if (sco < to_sco || sco_first == false)
		{
			for (int sdi = 0; sdi < 4; sdi++)
			{
				nr3 = nr1 + dr[(players[pv].di + sdi) % 4];
				nc3 = nc1 + dc[(players[pv].di + sdi) % 4];
				di3 = (players[to_v].di + sdi) % 4;

				if (nr3 < 0 || nr3 > n - 1 || nc3 < 0 || nc3 > n - 1) continue;
				if (p_area[nr3][nc3] > 0) continue;
				break;
			}
			int get_sco = abs((players[pv].gp + players[pv].sv) - (players[to_v].gp + players[to_v].sv));
			players[to_v].sco += get_sco;

			// 총 내려놓기
			g_area[nr1][nc1] = players[pv].gp;
			players[pv].gp = g_area[nr3][nc3];
			players[pv].di = di3;

			// 진 사람 이동
			p_area[nr3][nc3] = pv;

			// 이긴 사람 총 교환
			int max_gp = max(players[to_v].gp, g_area[nr1][nc1]);
			int min_gp = min(players[to_v].gp, g_area[nr1][nc1]);

			g_area[nr1][nc1] = min_gp;
			players[to_v].gp = max_gp;
			p_area[nr1][nc1] = to_v;

		}

	}
	else
	{
		int max_gp = max(players[pv].gp, g_area[nr1][nc1]);
		int min_gp = min(players[pv].gp, g_area[nr1][nc1]);

		g_area[nr1][nc1] = min_gp;
		players[pv].gp = max_gp;
		p_area[nr1][nc1] = pv;
	}
}

int main()
{
	cin >> n >> m;
	cin >> k;

	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			cin >> g_area[r][c];
		}
	}

	int sr,sc, di, sv;
	for (int i = 0; i < m; i++)
	{
		cin >> sr >> sc >> di >> sv;
		sr -= 1;
		sc -= 1;

		p_area[sr][sc] = i + 1;
		players[i + 1] = { di,sv,0,0 };
	}

	for (int rn = 0; rn < k; rn++)
	{
		for (int pv = 1; pv < m + 1; pv++)
		{
			bool p_ok = false;
			for (int r = 0; r < n; r++)
			{
				for (int c = 0; c < n; c++)
				{
					if (p_area[r][c] == pv) {
						p_move(pv, r, c);
						p_ok = true;
					}
					if (p_ok) break;
				}
				if (p_ok) break;
			}
		}
	}

	for (int pv = 1; pv < m + 1; pv++)
	{
		cout << players[pv].sco << " ";
	}
	return 0;
}