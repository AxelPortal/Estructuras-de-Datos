//
// Created by axelr on 13/11/2026.
//


#include <cmath>
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

vector<int> Dijkstra(int src, int n, vector<vector<pair<int,int>>> &G) {
    vector<int> D(n+1,numeric_limits<int>::max());
    D[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
    Q.emplace(0,src);
    while(!Q.empty()) {
        int u,d;
        tie(d,u) = Q.top();
        Q.pop();
        if (D[u]!=d) continue;
        for (auto &e : G[u]) {
            int v,w;
            tie(v,w) = e;
            if (D[v]>D[u]+w) {
                D[v] = D[u]+w;
                Q.emplace(D[v],v);
            }
        }
    }
    return D;

}

int main () {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> G(n+1);
    for(int i=0;i<m;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        G[u].emplace_back(v,w);
        G[v].emplace_back(u,w);
    }

    long long t=0;
    long long ed=0;
    for (int i=1;i<=n;i++) {
        vector<int> D=Dijkstra(i,n,G);
        long long dis=0;
        for (int k=1;k<=n;k++) {
            dis+=D[k];
        }

        if (i==1) {
            t=dis;
            ed=i;
        }
        else {
            if (dis<t) {
                t=dis;
                ed=i;
            }
        }

    }

    cout<<ed<<" "<<t;
    return 0;
}