//
// Created by axelr on 30/10/2026.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int BFS(int src, int exit, vector<int> &trans, int D, int N) {
    vector<int> dist(N+1,-1);
    queue<int> Q;
    dist[src]=0;
    Q.push(src);
    while (! Q.empty()) {
        int u=Q.front();
        Q.pop();
        if (u==N) {
            return dist[u];
        }
        for (int d=1;d<=D;d++) {
            int nxt=u+d;
            if (nxt>N) break;
            int dest=trans[nxt];

            if (dist[dest]==-1) {
                dist[dest]=dist[u]+1;
                Q.push(dest);
            }

        }
    }

    return dist[N];



}

int main () {
    cin.tie(0)->sync_with_stdio(false);
    int N,D,K;
    cin>>N>>D>>K;
    vector<int> trans(N+1);
    for(int i=0;i<=N;i++) {
        trans[i]=i;
    }
    for (int i=0;i<K;i++) {
        int u,v;
        cin>>u>>v;
        trans[u]=v;
    }

    cout<<BFS(1,N,trans,D,N);



}