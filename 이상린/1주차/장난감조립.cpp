#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M, X, Y, K;
vector<pair<int, int>> toy[101];
queue<int> num;
int indegree[101];
int cnt[101][101];

int main() {

    ios::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        cin >> X >> Y >> K;
        toy[X].push_back({ Y,K }); // X는 K개의 Y가 필요하다
        indegree[Y]++; // Y를 필요로하는 중간부품 수
    }

    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) { // 완제품
            num.push(i);
            cnt[i][i] = 1;
        }
    }

    while (!num.empty()) { // 완제품에서 기본부품으로
        int i = num.front();
        num.pop();
        for (pair<int, int> temp : toy[i]) {
            for (int t = 1; t <= N; t++) {
                cnt[t][temp.first] += temp.second * cnt[t][i];
            }
            indegree[temp.first]--;
            // 더이상 temp.first 부품을 필요로하는 중간부품 수가 없다면
            if (indegree[temp.first] == 0) num.push(temp.first);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (toy[i].size() == 0) {
            cout << i << " " << cnt[N][i] << "\n";
        }
    }

    return 0;
}