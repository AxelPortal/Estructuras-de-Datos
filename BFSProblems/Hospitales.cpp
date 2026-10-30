//
// Created by axelr on 29/10/2026.
//

#include <iostream>
#include <vector>

#include <queue>
using namespace std;

vector<int> MultisourceBFS(vector<int> &src,int n, vector<vector<int>> &G) {
    vector<int> dist(n,-1);
    queue<int> Q;
    for (auto &x : src) {
        dist[x]=0;
        Q.push(x);
    }

    while (not Q.empty()) {
        int f=Q.front();
        Q.pop();
        for (auto &v: G[f]) {
            if (dist[v]!=-1) continue;
            dist[v]=dist[f]+1;
            Q.push(v);
        }
    }

    return dist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> hospitals(k);
    for (int i=0;i<k;i++) {
        cin>>hospitals[i];
        hospitals[i]--;
    }

    vector<vector<int>> adj(n);
    for (int i=0;i<m;i++) {
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> resultado=MultisourceBFS(hospitals,n,adj);
    for (auto &x:resultado) cout<<x<<" ";

}