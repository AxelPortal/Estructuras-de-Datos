//
// Created by axelr on 29/10/2026.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<vector<bool>> v(n+1,vector<bool> (n+1,false));
    vector<pair<int, int>> aristas;
    while (m--) {
        int a,b;
        cin>>a>>b;
        if (a>b) swap(a,b);
        v[a][b]=true;
        v[b][a]=true;
        aristas.push_back({a,b});
    }

    int trios=0;
    for (auto &it: aristas) {
        int a=it.first;
        int b=it.second;
        for (int c=b+1;c<=n;c++) {
            if (v[a][c] && v[b][c]) {
                trios++;
            }
        }
    }

    cout<<trios;
    return 0;
}