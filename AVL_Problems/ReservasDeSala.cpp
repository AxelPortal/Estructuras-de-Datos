#include <iostream>
#include <algorithm>

using namespace std;

// Estructura que representa el intervalo de la reserva [s, e)
struct Reserva {
    int s, e;
    Reserva(int s, int e): s(s), e(e) {}

    // Se ordenan principalmente por el tiempo de inicio (s)
    bool operator<(const Reserva& other) const {
        return s < other.s;
    }
    bool operator>(const Reserva& other) const {
        return s > other.s;
    }
    bool operator==(const Reserva& other) const {
        return s == other.s;
    }
};

template<typename data_type>
struct AVL {
    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(data_type data = data_type(), int height = 0,
                 TreeNode* left = nullptr,
                 TreeNode* right = nullptr) :
            data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u->height;
    }

    int FB(TreeNode* u) {
        return h(u->left) - h(u->right);
    }

    bool search(data_type key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data == key) return true;
            if (current->data > key) current = current->left;
            else current = current->right;
        }
        return false;
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    TreeNode* min_element() { return min_element(root); }
    TreeNode* max_element() { return max_element(root); }

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
        else return u; // Evitar duplicados

        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }

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

    void erase(data_type value) {
        root = erase(root, value);
    }

    TreeNode* successor(data_type key) {
        TreeNode* current = root;
        TreeNode* succ = nullptr;
        while (current != nullptr) {
            if (current->data > key) {
                succ = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return succ;
    }

    TreeNode* predecessor(data_type key) {
        TreeNode* current = root;
        TreeNode* pred = nullptr;
        while (current != nullptr) {
            if (current->data < key) {
                pred = current;
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return pred;
    }

    // --- MÉTODOS AÑADIDOS PARA NAVEGACIÓN BBST ---

    // Retorna el primer nodo cuyo valor sea mayor o igual a key (lower_bound)
    TreeNode* lower_bound(data_type key) {
        TreeNode* current = root;
        TreeNode* res = nullptr;
        while (current != nullptr) {
            if (!(current->data < key)) { // current->data >= key
                res = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return res;
    }

    // Retorna el primer nodo cuyo valor sea estrictamente mayor a key (upper_bound)
    TreeNode* upper_bound(data_type key) {
        TreeNode* current = root;
        TreeNode* res = nullptr;
        while (current != nullptr) {
            if (key < current->data) { // current->data > key
                res = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return res;
    }

    // Retorna el nodo con el mayor valor que sea estrictamente menor o igual a key
    TreeNode* floor(data_type key) {
        TreeNode* current = root;
        TreeNode* res = nullptr;
        while (current != nullptr) {
            if (!(key < current->data)) { // current->data <= key
                res = current;
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return res;
    }
};

int main() {
    // Optimización de lecturas
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    AVL<Reserva> avl;

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int s, e;
            cin >> s >> e;
            Reserva nueva(s, e);

            bool chocan = false;

            // 1. Buscar la primera reserva con inicio >= s
            auto node = avl.lower_bound(nueva);

            // Verificar si choca con la reserva siguiente
            if (node != nullptr && node->data.s < e) {
                chocan = true;
            }

            // Verificar si choca con la reserva anterior
            if (!chocan) {
                auto prev_node = avl.predecessor(nueva);
                if (prev_node != nullptr && prev_node->data.e > s) {
                    chocan = true;
                }
            }

            if (chocan) {
                cout << "NO\n";
            } else {
                avl.insert(nueva);
                cout << "SI\n";
            }

        } else if (op == 2) {
            int s;
            cin >> s;
            avl.erase(Reserva{s, 0});

        } else if (op == 3) {
            int t;
            cin >> t;

            // Buscar la reserva con el mayor inicio s tal que s <= t
            auto prev_node = avl.floor(Reserva(t, 0));

            if (prev_node != nullptr && t < prev_node->data.e) {
                cout << prev_node->data.s << " " << prev_node->data.e << "\n";
            } else {
                cout << "LIBRE\n";
            }
        }
    }

    return 0;
}