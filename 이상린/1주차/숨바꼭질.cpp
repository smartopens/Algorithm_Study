// deque 사용
#include <iostream>
#include <deque>

using namespace std;

int main()
{
    int N,K; cin >> N >> K;

    // 0초 후인 2*X가 우선순위가 높음

    deque<int> dq;

    int visited[200001]={0};
    visited[N]=1;
    dq.push_back(N);
    int rst;

    while(!dq.empty())
    {
        int now = dq.front(); dq.pop_front();

        if (now==K)
        {
            rst=visited[now]-1;
            break;
        }

        if (now*2<200001&&!visited[now*2])
        {
            visited[now*2]=visited[now];
            dq.push_front(now*2);
        }
        // -1과 +1 순서 바꾸면 틀림 -> greedy 요소?
        if (now>0&&!visited[now-1])
        {
            visited[now-1]=visited[now]+1;
            dq.push_back(now-1);
        }
        if (now+1<200001&&!visited[now+1])
        {
            visited[now+1]=visited[now]+1;
            dq.push_back(now+1);
        }
        
    }

    cout << rst;

    return 0;
}