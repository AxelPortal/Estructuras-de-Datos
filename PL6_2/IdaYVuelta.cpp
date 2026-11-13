//
// Created by axelr on 13/11/2026.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int N = 200000 + 1;
const long long INF = 1e18;

int n, m;
vector<pair<int, int>> G[N], GT[N];

vector<long long> dijkstra(int s, vector<pair<int, int>> adj[]) {
    vector<long long> dist(n + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        GT[v].emplace_back(u, w);
    }

    vector<long long> ida = dijkstra(1, G);
    vector<long long> vuelta = dijkstra(1, GT);

    int atendidas = 0;
    long long total = 0;

    for (int v = 1; v <= n; v++) {
        if (ida[v] < INF && vuelta[v] < INF) {
            atendidas++;
            total += ida[v] + vuelta[v];
        }
    }

    cout << atendidas << " " << total << "\n";

    return 0;
}