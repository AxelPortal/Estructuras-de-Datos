//
// Created by axelr on 13/11/2026.
//

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int N = 200000 + 1;

int n, t;

int pi[N];
int visited[N];
vector<int> G[N];

void DFS(int u) {
    visited[u] = 1;
    for (auto &v : G[u]) {
        if (visited[v]) continue;
        pi[v] = u;
        DFS(v);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> t;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int s = 1;
    DFS(s);

    stack<int> st;
    while (t != s) {
        st.emplace(t);
        t = pi[t];
    }

    cout << st.size() + 1 << "\n";
    cout << s;
    while (!st.empty()) {
        cout << " " << st.top();
        st.pop();
    }

    return 0;
}