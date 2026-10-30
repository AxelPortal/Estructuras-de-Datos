//
// Created by axelr on 29/10/2026.
//

#include <iostream>
#include <vector>
using namespace std;

int main () {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1); //sigue a
    vector<vector<int>> adjT(n+1); //es seguido por
    for (int i=0;i<m;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adjT[v].push_back(u);
    }

    vector<int> marca(n+1,0);
    for (int a=1;a<=n;a++) {
        for (int c: adjT[a]) {
            marca[c]=a;
        }

        for (int b:adj[a]) {
            for (int c:adj[b]) {
                if (marca[c]==a) {
                    cout<<"SI";
                    return 0;
                }
            }

        }

    }

    cout<<"NO";


    return 0;
}