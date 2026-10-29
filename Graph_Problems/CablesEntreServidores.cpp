//
// Created by axelr on 23/10/2026.
//

#include <iostream>
#include <map>

using namespace std;

int main() {

    cin.tie(0)->sync_with_stdio(false);
    int n,m,q;
    cin>>n>>m>>q;

    map<pair<int,int>,int> frec;
    for (int i=0;i<m;i++) {
        int u,v;
        cin>>u>>v;
        if (u>v) swap(u,v);
        frec[make_pair(u,v)]++;
    }
    while (q--) {
        int u,v;
        cin>>u>>v;
        if (u>v) swap(u,v);
        if (frec.count(make_pair(u,v))!=0) {
            cout<<frec[make_pair(u,v)]<<"\n";
        }
        else {
            cout<<0<<"\n";
        }
    }
    return 0;
}