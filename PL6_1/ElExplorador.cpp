//
// Created by axelr on 13/11/2026.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> vis(200000+1,0);
vector<int> orden;
void dfs(vector<vector<int>> &G, int src) {
    vis[src] = 1;


    orden.push_back(src);
    for (auto &v : G[src]) {
        if (!vis[v]) {
            vis[v]=1;
            dfs(G,v);
        }
    }


}


int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    for(int i=1;i<=m;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for (auto &v: adj) {
        sort(v.begin(),v.end());
    }

    dfs(adj,1);
    cout<<orden.size();
    cout<<"\n";
    for (auto &i:orden) {
        cout<<i<<" ";
    }



    return 0;
}