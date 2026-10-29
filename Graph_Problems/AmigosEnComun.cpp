//
// Created by axelr on 23/10/2026.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int>> mat(n+1,vector<int>());
    for(int i=1;i<=m;i++) {
        int u,v;
        cin>>u>>v;
        mat[u].push_back(v);
        mat[v].push_back(u);
    }

    vector<bool> used(n+1,false);
    while (q--) {
        int u,v;
        cin>>u>>v;
        for (int &it:mat[u]) {
            used[it]=true;
        }

        int res=0;
        for (int &it: mat[v]) {
            if (used[it]) {
                res++;
            }
        }
        for (int &it: mat[u]) {
            used[it]=false;
        }
        cout<<res<<"\n";
    }
    return 0;
}