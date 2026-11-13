//
// Created by axelr on 13/11/2026.
//

#include <iostream>
#include <vector>

using namespace std;

const int N = 200000 + 1;

int n, m;
vector<int> G[N], GT[N];
int visited[N];

void DFS1(int u, int &cand) {
    visited[u] = 1;
    for (auto &v : G[u]) {
        if (visited[v]) continue;
        DFS1(v, cand);
    }
    cand = u;
}

int DFS2(int u, vector<int> adj[], int marca) {
    visited[u] = marca;
    int cnt = 1;
    for (auto &v : adj[u]) {
        if (visited[v] == marca) continue;
        cnt += DFS2(v, adj, marca);
    }
    return cnt;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        GT[v].push_back(u);
    }

    // 1. Encontrar el único candidato a líder
    int cand = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            DFS1(i, cand);
        }
    }

    // 2. Verificar que 'cand' llegue a todos los n nodos en G (usando marca = 2)
    if (DFS2(cand, G, 2) < n) {
        cout << 0 << "\n";
        return 0;
    }

    // 3. Contar cuántos nodos llegan a 'cand' en GT (usando marca = 3)
    cout << DFS2(cand, GT, 3) << "\n";

    return 0;
}