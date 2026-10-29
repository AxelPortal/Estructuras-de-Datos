//
// Created by axelr on 20/10/2026.
//

#include "iostream"
#include "vector";

using namespace std;


int main() {
    int n,m;
    cin>>n>>m;
    vector<int> a(n,0);
    for(int i=0;i<m;i++) {
        int u,v;
        cin>>u>>v;
        a[u-1]++;
        a[v-1]++;
    }

    int imp=0;
    for(auto& iter:a) {
        if (iter%2==1) {
            imp++;
        }
    }

    if (imp==0) {
        cout<<"CIRCUITO";
        return 0;
    }
    if (imp==2) {
        cout<<"CAMINO";
        return 0;
    }

    cout<<"IMPOSIBLE";

    return 0;
}