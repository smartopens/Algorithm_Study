#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> al[32001];
int indegree[32001];
int N, M;

int main() {
    cin >> N >> M;

    int A, B;
    for (int i = 0; i < M; i++) {
        cin >> A >> B;
        al[A].push_back(B);
        indegree[B]++;
    }

    queue<int> ans;
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    for (int i = 1; i <= N; i++) {
        int now = q.front();
        q.pop();

        ans.push(now);
        for (int j = 0; j < al[now].size(); j++) {
            int nxt = al[now][j];

            indegree[nxt]--;
            if (indegree[nxt] == 0) q.push(nxt);
        }
    }

    while (!ans.empty()) {
        int now = ans.front();
        ans.pop();
        cout << now << " ";
    }

    return 0;
}