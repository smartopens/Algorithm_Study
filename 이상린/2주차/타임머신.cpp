// 공부해서 다시..

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node{
	int to;
	int cost;
};

const long long INF = 1e18; // 매우 큰 값
 
int main(){
    int N, M;
    long long dist[500];
		cin >> N >> M;
    vector<Node> adj[500];
    for(int i=0; i<M; i++){
        int A, B, C; cin >> A >> B >> C;
        adj[A-1].push_back({B-1, C});
    }
    int flag = 0;
		
		for (int i=0;i<N;i++)
		{
			dist[i]=INF;
		}

    dist[0] = 0;
    for(int i=0; i<N; i++){ // (N-1) + 1번의 루프. 마지막은 음의 싸이클 존재 여부 확인용
        for(int j=0; j<N; j++){
            // N-1번의 루프에 걸쳐 각 정점이 i+1개 정점을 거쳐오는 최단경로 갱신
						for (int k=0;k<M;k++)
						{
							int next = adj[j][k].to;
							int d = adj[j][k].cost;
							if(dist[j] != INF && dist[next] > dist[j] + d){
                    dist[next] = dist[j] + d;
                    // N번째 루프에 값이 갱신-> 음의 사이클 존재
                    if(i == N-1) flag = 1;
                }
						}
        }
    }
    if(flag) cout << -1;
    else{
        for(int i=1; i<N; i++)
						cout << (dist[i]!=INF ? dist[i] : -1);
    }
}
