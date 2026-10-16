#include <iostream>
#include <algorithm>

using namespace std;

// 1. Objeto para el Árbol de Ganadores (ordena por VOTOS desc, ID asc)
struct Cancion {
    int name;
    int votos;

    Cancion(int n = 0, int v = 0) : name(n), votos(v) {}

    bool operator<(const Cancion& c) const {
        if (votos != c.votos) return votos > c.votos; // Más votos va a la izquierda (mínimo)
        return name < c.name;                         // Menor ID va a la izquierda
    }
    bool operator>(const Cancion& c) const {
        if (votos != c.votos) return votos < c.votos;
        return name > c.name;
    }
    bool operator==(const Cancion& c) const {
        return name == c.name && votos == c.votos;
    }
};

// 2. Objeto para el Árbol de Búsqueda de Votos (ordena únicamente por ID asc)
struct InfoCancion {
    int name;
    int votos;

    InfoCancion(int n = 0, int v = 0) : name(n), votos(v) {}

    bool operator<(const InfoCancion& c) const { return name < c.name; }
    bool operator>(const InfoCancion& c) const { return name > c.name; }
    bool operator==(const InfoCancion& c) const { return name == c.name; }
};

template<typename data_type>
struct AVL {
    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(data_type data = data_type(), int height = 0,
                 TreeNode* left = nullptr, TreeNode* right = nullptr) :
            data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() { root = nullptr; }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u->height;
    }

    int FB(TreeNode* u) {
        return h(u->left) - h(u->right);
    }

    TreeNode* search(data_type key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data == key) return current;
            if (current->data > key) current = current->left;
            else current = current->right;
        }
        return nullptr;
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* min_element() { return min_element(root); }

    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u->right;
        u->right = v->left;
        v->left = u;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u->left;
        u->left = v->right;
        v->right = u;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {
            if (FB(u->left) < 0) u->left = rotate_left(u->left);
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            if (FB(u->right) > 0) u->right = rotate_right(u->right);
            return rotate_left(u);
        }
        return u;
    }

    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) return new TreeNode(value, 0);

        if (value < u->data) u->left = insert(u->left, value);
        else if (value > u->data) u->right = insert(u->right, value);
        else return u;

        return rebalance(u);
    }

    void insert(data_type value) { root = insert(root, value); }

    TreeNode* erase(TreeNode* u, data_type key) {
        if (u == nullptr) return u;

        if (key < u->data) {
            u->left = erase(u->left, key);
        } else if (key > u->data) {
            u->right = erase(u->right, key);
        } else {
            if (u->left == nullptr) {
                TreeNode* temp = u->right;
                delete u;
                return temp;
            } else if (u->right == nullptr) {
                TreeNode* temp = u->left;
                delete u;
                return temp;
            } else {
                TreeNode* temp = min_element(u->right);
                u->data = temp->data;
                u->right = erase(u->right, temp->data);
            }
        }

        return rebalance(u);
    }

    void erase(data_type value) { root = erase(root, value); }
};

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    AVL<Cancion> avl_canciones;    // Árbol para saber la ganadora en O(1)
    AVL<InfoCancion> avl_votos;    // Árbol para buscar los votos por ID en O(log N)

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) { // LLegada de voto
            int x;
            cin >> x;

            auto nodo = avl_votos.search(InfoCancion(x, 0));
            int v_ant = (nodo != nullptr) ? nodo->data.votos : 0;

            // Retirar la versión antigua de ambos árboles si ya existía
            if (v_ant > 0) {
                avl_canciones.erase(Cancion(x, v_ant));
                avl_votos.erase(InfoCancion(x, v_ant));
            }

            int v_nuevo = v_ant + 1;
            avl_canciones.insert(Cancion(x, v_nuevo));
            avl_votos.insert(InfoCancion(x, v_nuevo));

        } else if (op == 2) { // Retirar un voto
            int x;
            cin >> x;

            auto nodo = avl_votos.search(InfoCancion(x, 0));
            int v_ant = nodo->data.votos;

            // Eliminar versión antigua
            avl_canciones.erase(Cancion(x, v_ant));
            avl_votos.erase(InfoCancion(x, v_ant));

            int v_nuevo = v_ant - 1;
            if (v_nuevo > 0) {
                avl_canciones.insert(Cancion(x, v_nuevo));
                avl_votos.insert(InfoCancion(x, v_nuevo));
            }

        } else if (op == 3) { // Consultar ganadora
            auto ganador = avl_canciones.min_element();
            if (ganador != nullptr) {
                cout << ganador->data.name << " " << ganador->data.votos << "\n";
            }
        }
    }

    return 0;
}