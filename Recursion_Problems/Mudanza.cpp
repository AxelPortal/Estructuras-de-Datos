//
// Created by axelr on 16/10/2026.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<long long> w;
long long mejor_maximo = 1e18; // Inicializado en un valor muy grande

void repartir(int i, long long p1, long long p2, long long p3) {
    long long max_actual = max({p1, p2, p3});

    // Poda: si alguna persona ya carga tanto o más que la mejor solución
    // encontrada hasta ahora, no tiene sentido seguir por esta rama.
    if (max_actual >= mejor_maximo) {
        return;
    }

    // Caso base: se repartieron las n cajas
    if (i == n) {
        mejor_maximo = max_actual;
        return;
    }

    // Probar darle la caja 'i' a cada una de las 3 personas
    repartir(i + 1, p1 + w[i], p2, p3);
    repartir(i + 1, p1, p2 + w[i], p3);
    repartir(i + 1, p1, p2, p3 + w[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (cin >> n) {
        w.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> w[i];
        }

        // Opcional: ordenar de mayor a menor hace que la poda sea mucho más rápida
        sort(w.rbegin(), w.rend());

        // Truco de simetría opcional: la caja 0 siempre puede ir a la persona 1
        // (evita repetir los mismos repartos permutando a las 3 personas)
        repartir(1, w[0], 0, 0);

        cout << mejor_maximo << "\n";
    }
    return 0;
}