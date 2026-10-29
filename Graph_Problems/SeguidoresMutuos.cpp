#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin>>n>>m;

    vector<int> in_degree(n + 1, 0);
    vector<vector<int>> adj(n + 1);
    int mutuos = 0;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;

        in_degree[b]++;

        for (int v : adj[b]) {
            if (v == a) {
                mutuos++;
                break;
            }
        }

        adj[a].push_back(b);
    }

    int max_followers = -1;
    int best_user = 1;

    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] > max_followers) {
            max_followers = in_degree[i];
            best_user = i;
        }
    }

    cout << mutuos << " " << best_user << " " << max_followers << "\n";

    return 0;
}