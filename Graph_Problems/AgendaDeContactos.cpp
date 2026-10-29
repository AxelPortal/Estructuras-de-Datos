//
// Created by axelr on 23/10/2026.
//

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int main () {
    cin.tie(0)->sync_with_stdio(false);
    int n,m,q;
    cin>>n>>m>>q;


    vector<vector<int>> ad(n+1);
    while (m--) {
        int u,v;
        cin>>u>>v;
        ad[u].push_back(v);
        ad[v].push_back(u);
    }

    for (auto &i : ad) {
        sort(i.begin(),i.end());
    }

    while (q--) {
        int op;
        cin>>op;
        if (op==1) {
            int u,k;
            cin>>u>>k;
            if (ad[u].size()<k) {
                cout<<-1<<"\n";
            }
            else {
                cout<<ad[u][k-1]<<"\n";
            }

        }

        else if (op==2) {
            int u,x;
            cin>>u>>x;
            cout<<upper_bound(ad[u].begin(),ad[u].end(),x)-ad[u].begin()<<"\n";
        }
    }


    return 0;
}