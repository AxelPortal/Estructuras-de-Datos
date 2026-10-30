//
// Created by axelr on 30/10/2026.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;
int df[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int resolverEscapedelFuego(int R, int C, vector<string>& grilla) {
    queue<pair<int, int>> Q_fuego;
    queue<pair<int, int>> Q_persona;

    vector<vector<int>> fuego(R, vector<int>(C, INF));
    vector<vector<int>> dist(R, vector<int>(C, INF));

    // 1. Identificar posiciones iniciales
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grilla[r][c] == 'F') {
                fuego[r][c] = 0;
                Q_fuego.push({r, c});
            } else if (grilla[r][c] == 'P') {
                dist[r][c] = 0;
                Q_persona.push({r, c});
            }
        }
    }

    // 2. BFS para el Fuego
    while (!Q_fuego.empty()) {
        auto [f, c] = Q_fuego.front();
        Q_fuego.pop();

        for (int k = 0; k < 4; ++k) {
            int nf = f + df[k];
            int nc = c + dc[k];

            if (nf >= 0 && nf < R && nc >= 0 && nc < C && grilla[nf][nc] != '#') {
                if (fuego[nf][nc] == INF) {
                    fuego[nf][nc] = fuego[f][c] + 1;
                    Q_fuego.push({nf, nc});
                }
            }
        }
    }

    // 3. BFS para la Persona
    while (!Q_persona.empty()) {
        auto [f, c] = Q_persona.front();
        Q_persona.pop();

        // Si llegó a un borde, puede escapar en el siguiente minuto
        if (f == 0 || f == R - 1 || c == 0 || c == C - 1) {
            return dist[f][c] + 1;
        }

        for (int k = 0; k < 4; ++k) {
            int nf = f + df[k];
            int nc = c + dc[k];

            if (nf >= 0 && nf < R && nc >= 0 && nc < C && grilla[nf][nc] != '#') {
                // Solo ingresa si llega ANTES de que la casilla se queme
                if (dist[nf][nc] == INF && dist[f][c] + 1 < fuego[nf][nc]) {
                    dist[nf][nc] = dist[f][c] + 1;
                    Q_persona.push({nf, nc});
                }
            }
        }
    }

    return -1; // No es posible escapar
}