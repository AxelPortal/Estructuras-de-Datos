//
// Created by axelr on 13/11/2026.
//

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

vector<long long> Dijkstra(int src, int n, vector<vector<pair<int,int>>> &G) {
    vector<long long> D(n+1, numeric_limits<long long>::max());
    D[src] = 0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> Q;
    Q.emplace(0, src);
    while(!Q.empty()) {
        int u;
        long long d;
        tie(d, u) = Q.top();
        Q.pop();
        if (D[u] != d) continue;
        for (auto &e : G[u]) {
            int v, w;
            tie(v, w) = e;
            if (D[v] > D[u] + w) {
                D[v] = D[u] + w;
                Q.emplace(D[v], v);
            }
        }
    }
    return D;
}

int main () {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> G(n+1);
    for(int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    // 1. Primer recorrido desde el edificio 1 para hallar un extremo del diámetro
    vector<long long> D1 = Dijkstra(1, n, G);
    int extremo = 1;
    for (int i = 1; i <= n; i++) {
        if (D1[i] > D1[extremo]) {
            extremo = i;
        }
    }

    // 2. Segundo recorrido desde ese extremo para hallar la máxima distancia
    vector<long long> D2 = Dijkstra(extremo, n, G);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (D2[i] > ans) {
            ans = D2[i];
        }
    }

    cout << ans << "\n";
    return 0;
}