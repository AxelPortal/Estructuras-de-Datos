//
// Created by axelr on 29/10/2026.
//

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    int aristas=0;
    for (int i=0;i<m;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        aristas++;
    }

    size_t max_grade=0;
    for (auto &v: adj) {
        size_t i=v.size();
        max_grade=max(max_grade,i);
    }

    bool arbol=false;
    bool completo=false;
    if (m==n-1) arbol=true;
    if (aristas==n*(n-1)/2) completo=true;

    cout<<max_grade<<endl;

    if (arbol && completo && n>=2) {
        cout<<"ARBOL";
        return 0;
    }

    if (arbol) {
        cout<<"ARBOL";
        return 0;
    }

    if (completo) {
        cout<<"COMPLETO"<<endl;
        return 0;
    }

    cout<<"OTRO";


    return 0;
}