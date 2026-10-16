//
// Created by axelr on 16/10/2026.
//

#include <bits/stdc++.h>
using namespace std;

template<typename data_type>
struct AVL {
    struct TreeNode {
        int height;
        data_type data;
        int size; // Mantiene el tamaño del subárbol
        TreeNode* left;
        TreeNode* right;
        TreeNode(data_type data = data_type(), int height = 0,
                 TreeNode* left = nullptr, TreeNode* right = nullptr) :
            data(data), height(height), size(1), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    int sz(TreeNode* u) {
        return u == nullptr ? 0 : u->size;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u->height;
    }

    void update(TreeNode* u) {
        if (u == nullptr) return;
        u->height = 1 + max(h(u->left), h(u->right));
        u->size = 1 + sz(u->left) + sz(u->right);
    }

    int FB(TreeNode* u) {
        return u == nullptr ? 0 : h(u->left) - h(u->right);
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

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

    // Permite elementos duplicados enviándolos al subárbol izquierdo
    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) return new TreeNode(value, 0);

        if (value <= u->data) u->left = insert(u->left, value);
        else u->right = insert(u->right, value);

        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }

    // Elimina una sola ocurrencia del valor
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

    // Cuenta cuántos elementos son menores o iguales a X
    int count_less_or_equal(data_type x) {
        TreeNode* current = root;
        int count = 0;
        while (current != nullptr) {
            if (current->data <= x) {
                count += 1 + sz(current->left);
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return count;
    }

    // Consulta la cantidad de elementos en el rango [l, r]
    int count_range(data_type l, data_type r) {
        return count_less_or_equal(r) - count_less_or_equal(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    AVL<long long> avl;

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            long long x;
            cin >> x;
            avl.insert(x);
        } else if (op == 2) {
            long long x;
            cin >> x;
            avl.erase(x);
        } else if (op == 3) {
            long long l, r;
            cin >> l >> r;
            cout << avl.count_range(l, r) << "\n";
        }
    }

    return 0;
}