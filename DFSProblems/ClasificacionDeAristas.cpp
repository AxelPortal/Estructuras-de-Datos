//
// Created by axelr on 3/11/2026.
//


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int N=200000 + 1;
int T;
int n,m;
int tin[N];
int tout[N];
int vis[N];
//0 sin visitar
//1 en proceso
//2 finalizado

int tree, back, forward_edge, cross;

void DFS(int u, vector<vector<int>> &G) {
    vis[u]=1;
    tin[u]=T;
    T++;
    for (auto &v: G[u]) {
        if (vis[v]==1) {
            back++;
        }
        else if (vis[v]==2) {
            if (tin[u]<tin[v]) forward_edge++;
            else cross++;
        }
        else {
            DFS(v,G);
            tree++;
        }
    }
    tout[u]=T;
    T++;
    vis[u]=2;

}


int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    for (int i=0;i<m;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }

    for (int r=1;r<=n;r++) {
        sort(adj[r].begin(),adj[r].end());
    }

    for (int r=1;r<=n;r++) {
        if (vis[r]) continue;
        DFS(r,adj);
    }

    cout<<tree<<" "<<back<<" "<<forward_edge<<" "<<cross<<endl;


    return 0;
}