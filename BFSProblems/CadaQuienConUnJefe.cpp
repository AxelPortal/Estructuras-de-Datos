//
// Created by axelr on 30/10/2026.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main () {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    for (int i=0;i<m;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(n+1,false);
    bool esPosible=true;

    for (int i=0;i<n;i++) {

        if (!visited[i]) {
            long long sum_deg=0;
            int num_vertices=0;
            queue<int> q;
            q.push(i);
            visited[i]=true;
            while (!q.empty()) {
                int u=q.front();
                q.pop();
                num_vertices++;
                sum_deg+=adj[u].size();

                for (int &v:adj[u]) {
                    if (!visited[v]) {
                        q.push(v);
                        visited[v]=true;
                    }
                }
            }
            if (sum_deg/2>num_vertices) {
                esPosible=false;
                break;
            }
        }
    }

    if (esPosible) cout<<"SI";
    else cout<<"NO";
    return 0;
}