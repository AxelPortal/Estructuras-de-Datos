//
// Created by axelr on 13/11/2026.
//

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<int> ruta;
int t;

bool dfs(int u, int p) {
    ruta.push_back(u);
    if (u == t) return true;

    for (int v : adj[u]) {
        if (v != p) {
            if (dfs(v, u)) return true;
        }
    }

    ruta.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n >> t)) return 0;

    adj.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    cout << ruta.size() << "\n";
    for (int i = 0; i < (int)ruta.size(); ++i) {
        cout << ruta[i] << (i + 1 == (int)ruta.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}