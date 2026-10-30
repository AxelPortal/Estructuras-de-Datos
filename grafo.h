
using namespace std;

// ============================================================================
// ESTRUCTURA DE DATOS: CLASE GRAFO (SOLO CON STD::VECTOR)
// ============================================================================
class Grafo {
private:
    int n;                  // Cantidad de vértices |V|
    int m;                  // Cantidad de aristas |E|
    bool dirigido;          // true si es dirigido, false si es no dirigido

    struct Arista {
        int destino;
        int peso;
    };

    vector<vector<Arista>> adj; // Lista de adyacencia: memoria Theta(n + m)
    vector<int> in_degree;      // Grado de entrada para grafos dirigidos

public:
    const int INF = -1;

    struct ResultadoBFS {
        vector<int> dist;
        vector<int> padre;
    };

    // Constructor: inicializa el grafo con n vértices (0 a n - 1)
    Grafo(int num_vertices, bool es_dirigido = false) {
        n = num_vertices;
        m = 0;
        dirigido = es_dirigido;
        adj.resize(n);
        in_degree.assign(n, 0);
    }

    // Agrega una arista en O(1) amortizado
    void agregarArista(int u, int v, int peso = 1) {
        adj[u].push_back({v, peso});
        in_degree[v]++;
        if (!dirigido) {
            if (u != v) {
                adj[v].push_back({u, peso});
            } else {
                adj[u].push_back({u, peso}); // Un lazo suma 2 al grado
            }
        }
        m++;
    }

    // Grado de u en O(1): tamaño de adj[u]
    int grado(int v) const {
        return adj[v].size();
    }

    int gradoEntrada(int v) const {
        return in_degree[v];
    }

    int numVertices() const { return n; }
    int numAristas() const { return m; }

    // Recorrer los vecinos de u en O(deg u)
    const vector<Arista>& obtenerVecinos(int u) const {
        return adj[u];
    }
    void ordenarVecinos()
    {
        for (int i = 0; i < n; i++)
        {
            sort(adj[i].begin(), adj[i].end(),[](const Arista& a, const Arista& b)
            {
                return a.destino < b.destino;
            });
        }
    }
    // ¿u y v son adyacentes? Búsqueda en adj[u] en O(deg u)
    bool sonAdyacentes(int u, int v) const {
        for (size_t i = 0; i < adj[u].size(); i++) {
            if (adj[u][i].destino == v) {
                return true;
            }
        }
        return false;
    }

    // Quitar una arista en O(1) una vez localizada (reemplazando con el último elemento)
    bool quitarAristaDirigida(int u, int v) {
        for (size_t i = 0; i < adj[u].size(); i++) {
            if (adj[u][i].destino == v) {
                adj[u][i] = adj[u][adj[u].size() - 1];
                adj[u].pop_back();
                in_degree[v]--;
                m--;
                return true;
            }
        }
        return false;
    }

    // Grafo transpuesto en O(n + m): invierte el sentido de todas las aristas
    Grafo obtenerTranspuesto() const {
        Grafo transpuesto(n, true);
        for (int u = 0; u < n; u++) {
            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].destino;
                int w = adj[u][i].peso;
                transpuesto.agregarArista(v, u, w);
            }
        }
        return transpuesto;
    }

    // Verifica el Lema del Apretón de Manos: sum(deg(v)) == 2m
    bool verificarApretonDeManos() const {
        int suma = 0;
        for (int v = 0; v < n; v++) {
            suma += grado(v);
        }
        return suma == 2 * m;
    }

    // Algoritmo BFS implementado SIN <queue>, usando std::vector y puntero 'frente'
    ResultadoBFS bfs(int origen) const {
        vector<int> dist(n, INF);
        vector<int> padre(n, -1);

        // Cola implementada sobre vector: reserve(n) evita realocaciones
        vector<int> cola;
        cola.reserve(n);
        size_t frente = 0;

        dist[origen] = 0;
        cola.push_back(origen); // Encolar en O(1)

        while (frente < cola.size()) {
            int u = cola[frente++]; // Desencolar en O(1) avanzando el índice

            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].destino;
                if (dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    padre[v] = u;
                    cola.push_back(v);
                }
            }
        }
        return {dist, padre};
    }

    // Retorna la distancia mínima d(u, v) en cantidad de aristas
    int distancia(int u, int v) const {
        ResultadoBFS res = bfs(u);
        return res.dist[v];
    }

    // Reconstruye el camino más corto entre u y v sin <algorithm>
    vector<int> caminoMasCorto(int u, int v) const {
        ResultadoBFS res = bfs(u);
        if (res.dist[v] == INF) return {};

        vector<int> camino;
        for (int actual = v; actual != -1; actual = res.padre[actual]) {
            camino.push_back(actual);
        }

        // Inversión manual del vector en O(k)
        int izq = 0;
        int der = (int)camino.size() - 1;
        while (izq < der) {
            int temp = camino[izq];
            camino[izq] = camino[der];
            camino[der] = temp;
            izq++;
            der--;
        }
        return camino;
    }

    // Halla todas las componentes conexas del grafo no dirigido
    vector<vector<int>> obtenerComponentesConexas() const {
        vector<bool> visitado(n, false);
        vector<vector<int>> componentes;

        for (int i = 0; i < n; i++) {
            if (!visitado[i]) {
                vector<int> comp;
                ResultadoBFS res = bfs(i);
                for (int j = 0; j < n; j++) {
                    if (res.dist[j] != INF) {
                        visitado[j] = true;
                        comp.push_back(j);
                    }
                }
                componentes.push_back(comp);
            }
        }
        return componentes;
    }

    // Verifica si el grafo no dirigido es un Árbol (conexo y m == n - 1)
    bool esArbol() const {
        if (dirigido || m != n - 1) return false;
        return obtenerComponentesConexas().size() == 1;
    }

    // Ordenamiento Topológico (Kahn) para DAGs implementado SIN <queue>
    vector<int> ordenTopologico() const {
        vector<int> in_deg = in_degree;
        vector<int> cola;
        cola.reserve(n);
        size_t frente = 0;

        for (int i = 0; i < n; i++) {
            if (in_deg[i] == 0) {
                cola.push_back(i); // Encolar vértices sin dependencias
            }
        }

        while (frente < cola.size()) {
            int u = cola[frente++]; // Desencolar en O(1)

            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].destino;
                in_deg[v]--;
                if (in_deg[v] == 0) {
                    cola.push_back(v);
                }
            }
        }
        // El vector 'cola' ya contiene todos los elementos desencolados en orden topológico
        return cola;
    }
};

// Búsqueda lineal del índice de una palabra usando únicamente std::vector
int obtenerIndicePalabra(const vector<string>& palabras, const string& buscada) {
    for (size_t i = 0; i < palabras.size(); i++) {
        if (palabras[i] == buscada) return i;
    }
    return -1;
}
