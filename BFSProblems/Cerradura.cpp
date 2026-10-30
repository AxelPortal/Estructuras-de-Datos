//
// Created by axelr on 30/10/2026.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int w;
    if (!(cin >> w)) return 0;

    string s, t;
    cin >> s >> t;

    int k;
    cin >> k;

    unordered_set<string> forbidden;
    for (int i = 0; i < k; ++i) {
        string code;
        cin >> code;
        forbidden.insert(code);
    }

    // Caso borde: si el inicio o el final están prohibidos
    if (forbidden.count(s) || forbidden.count(t)) {
        cout << -1 << "\n";
        return 0;
    }

    // BFS
    queue<pair<string, int>> q;
    unordered_set<string> visited;

    q.push({s, 0});
    visited.insert(s);

    while (!q.empty()) {
        auto [curr, dist] = q.front();
        q.pop();

        if (curr == t) {
            cout << dist << "\n";
            return 0;
        }

        // Generar los 2 * w vecinos
        for (int i = 0; i < w; ++i) {
            char original = curr[i];

            // Subir (d + 1) % 10
            char up = (original - '0' + 1) % 10 + '0';
            curr[i] = up;
            if (!forbidden.count(curr) && !visited.count(curr)) {
                visited.insert(curr);
                q.push({curr, dist + 1});
            }

            // Bajar (d - 1 + 10) % 10
            char down = (original - '0' + 9) % 10 + '0';
            curr[i] = down;
            if (!forbidden.count(curr) && !visited.count(curr)) {
                visited.insert(curr);
                q.push({curr, dist + 1});
            }

            // Restaurar carácter original para el siguiente ciclo
            curr[i] = original;
        }
    }

    // Si no fue posible alcanzar el objetivo
    cout << -1 << "\n";
    return 0;
}