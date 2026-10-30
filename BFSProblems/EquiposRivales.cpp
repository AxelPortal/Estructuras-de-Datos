//
// Created by axelr on 30/10/2026.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MOD = 1e9 + 7;

bool BipartiteCheck(vector<vector<int>> &G, int n, int src, vector<int> &colores) {
    queue<int> Q;
    colores[src] = 0;
    Q.push(src);

    while (not Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto &x : G[u]) {
            if (colores[x]==-1) {
                colores[x]=1-colores[u];
                Q.push(x);
            }
            else if (colores[x]==colores[u]) {
                return false;
            }
        }
    }

    return true;
}

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    for (int i=0;i<m;i++) {
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> colores(n+1,-1);
    int componentes=0;
    bool esBipartito=true;
    for (int i=1;i<=n;i++) {
        if (colores[i]==-1) {
            componentes++;
            if (!BipartiteCheck(adj,n,i,colores)) {
                esBipartito=false;
            }
        }

    }

    if (!esBipartito) {
        cout << "NO\n";
    } else {
        cout << "SI " << power(2, componentes) << "\n";
    }


    return 0;
}