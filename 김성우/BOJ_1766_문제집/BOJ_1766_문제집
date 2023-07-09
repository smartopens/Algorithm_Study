#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX_LEN 32100

struct cmp {
    
    bool operator()(int left, int right){

        if (left > right)
            return true;
        else if (left < right)
            return false;
        return false;
    }
};

int N, M;
int A, B;
vector<int> v[MAX_LEN];
int v_pointed[MAX_LEN] = { 0, }; // 지목당한 문제들을 보관할 DHT
// int v_pointing[MAX_LEN] = { 0, };
priority_queue<int, vector<int>, cmp> pq;
vector<int> ansv;

void sol() {

    // 지목당하지 않은 문제들을 pq에 하나씩 넣는다.
    for (int i = 1; i <= N; i++) {
        if (v_pointed[i] == 0)
            pq.push(i);
    }

    while (!pq.empty()) {
        int problem = pq.top();
        pq.pop();
        ansv.push_back(problem);

        for (int i = 0; i < v[problem].size(); i++) {
            int p = v[problem][i];
            v_pointed[p]--;

            if (v_pointed[p] == 0) {
                pq.push(p);
            }
        }
    }
}

void input() {

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> A >> B;
        v[A].push_back(B); // A가 B를 지목
        v_pointed[B]++; // 지목당했으면 DHT를 업데이트한다.
        // v_pointing[A]++; // 여기에선 지목한 친구도 DHT를 업데이트 한다 (지목한 친구 먼저 풀어야 하니까)
        // -> 이게 문제였다.. 문제를 잘못 이해해서 ㅅㅂ
    }
}

int main() {

    input();

    sol();

    for (int i = 0; i < ansv.size(); i++) {
        cout << ansv[i] << " ";
    }


}