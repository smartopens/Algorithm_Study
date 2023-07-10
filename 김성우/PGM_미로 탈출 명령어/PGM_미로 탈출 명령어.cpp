#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 101;
const int MAX_M = 101;

int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, -1, 1, 0};
char dAlpha[4] = {'d', 'l', 'r', 'u'};
string answer = "z";

bool isValid(int nx, int ny, int n, int m) {
    return (nx >= 1 && nx <= n && ny >= 1 && ny <= m);
}

void dfs(int n, int m, int x, int y, int r, int c, string prev_s, int cnt, int k) {
    if (k < cnt + abs(x - r) + abs(y - c))
        return;
    if (x == r && y == c && cnt == k) {
        answer = prev_s;
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (isValid(x + dx[i], y + dy[i], n, m) && prev_s < answer)
            dfs(n, m, x + dx[i], y + dy[i], r, c, prev_s + dAlpha[i], cnt + 1, k);
    }
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    int dist = abs(x - r) + abs(y - c);
    if (dist > k || (k - dist) % 2 == 1)
        return "impossible";

    dfs(n, m, x, y, r, c, "", 0, k);

    return answer;
}
