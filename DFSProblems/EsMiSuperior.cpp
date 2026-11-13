//
// Created by axelr on 3/11/2026.
//

#include <iostream>
#include <vector>

using namespace std;

int t=1;

void DFS(int src, vector<int> &tin, vector<int> &tout, vector<vector<int>> &adj) {
    tin[src]=t;
    t++;
    for (auto &v : adj[src]) {
        if (tin[v]!=0) continue;
        DFS(v,tin,tout,adj);
    }
    tout[src]=t;
    t++;
}

bool esSuperior(int u,int v, vector<int> &tin, vector<int> &tout) {
    return tin[u]<=tin[v] && tout[v]<=tout[u];


}


int main () {
    cin.tie(0)->sync_with_stdio(false);

    int n,q;
    cin>>n>>q;
    vector<int> tin(n+1,0);
    vector<int> tout(n+1,0);
    vector<vector<int>> adj(n+1);

    for (int i=0;i<n-1;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS(1,tin,tout,adj);

    while (q--) {
        int u,v;
        cin>>u>>v;
        if (esSuperior(u,v,tin,tout)) {
            cout<<"SI"<<endl;
        }
        else {
            cout<<"NO"<<endl;
        }

    }

    return 0;
}