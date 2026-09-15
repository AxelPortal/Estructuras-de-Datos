//
// Created by marie on 15/09/2026.
//

#ifndef BST_BST_H
#define BST_BST_H
#include <bits/stdc++.h>
using namespace std;

template<typename data_type>
struct BST {
public:
    // =========================================================
    // 1. ESTRUCTURA DEL NODO
    // =========================================================
    struct TreeNode {
        data_type data;
        TreeNode *left;
        TreeNode *right;
        TreeNode *parent; // Puntero al padre vital para sucesor/predecesor

        TreeNode(data_type data = data_type(),
                 TreeNode* left = nullptr,
                 TreeNode* right = nullptr,
                 TreeNode* parent = nullptr) :
            data(data), left(left), right(right), parent(parent) {}
    };

    TreeNode *root;

    // =========================================================
    // 2. CONSTRUCTOR Y DESTRUCTOR
    // =========================================================
    BST() {
        root = nullptr;
    }

    ~BST() {
        clear(root);
    }

    // =========================================================
    // 3. ESTADO Y TAMAÑO
    // =========================================================
    bool is_empty() {
        return root == nullptr;
    }

    int size() {
        return size_aux(root);
    }

    // =========================================================
    // 4. BÚSQUEDA Y MÁXIMOS/MÍNIMOS
    // =========================================================
    bool search(data_type key) {
        return find_node(key) != nullptr;
    }

    TreeNode* find_node(data_type key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data == key) return current;
            if (current->data > key) current = current->left;
            else current = current->right;
        }
        return nullptr;
    }

    data_type min_element() {
        if (root == nullptr) return data_type();
        TreeNode* current = root;
        while (current->left != nullptr) current = current->left;
        return current->data;
    }

    data_type max_element() {
        if (root == nullptr) return data_type();
        TreeNode* current = root;
        while (current->right != nullptr) current = current->right;
        return current->data;
    }

    // =========================================================
    // 5. INSERCIÓN Y ELIMINACIÓN (Método CLRS con Transplant)
    // =========================================================
    void insert(data_type key) {
        TreeNode* newNode = new TreeNode(key);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        TreeNode* current = root;
        TreeNode* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (key < current->data) current = current->left;
            else if (key > current->data) current = current->right;
            else {
                delete newNode; // Evitar duplicados
                return;
            }
        }

        newNode->parent = parent;
        if (key < parent->data) parent->left = newNode;
        else parent->right = newNode;
    }

    void remove(data_type key) {
        TreeNode* target = find_node(key);
        if (target != nullptr) {
            erase(target); // Llama a la nueva lógica de eliminación
        }
    }

    // =========================================================
    // 6. RECORRIDOS E IMPRESIÓN
    // =========================================================
    void print_tree() { // Imprime la estructura simple (Post-orden sin texto extra)
        post_order_aux(root);
        cout << endl;
    }

    void pre_order() {
        pre_order_aux(root);
        cout << endl;
    }

    void in_order() {
        in_order_aux(root);
        cout << endl;
    }

    void post_order() {
        post_order_aux(root);
        cout << endl;
    }

    void in_order_traversal() {
        cout << "[ ";
        in_order_aux(root);
        cout << "]" << endl;
    }

    void print_subtree_inorder(TreeNode* node) {
        if (node == nullptr) return;
        cout << "[ ";
        in_order_aux(node);
        cout << "]" << endl;
    }

    void print_subtree_inorder(data_type key) {
        TreeNode* target = find_node(key);
        if (target != nullptr) {
            print_subtree_inorder(target);
        } else {
            cout << "[ Nodo " << key << " no encontrado ]" << endl;
        }
    }

    // =========================================================
    // 7. SUCESOR Y PREDECESOR
    // =========================================================
    TreeNode* get_successor(TreeNode* node) {
        if (node == nullptr) return nullptr;
        if (node->right != nullptr) {
            TreeNode* current = node->right;
            while (current->left != nullptr) current = current->left;
            return current;
        }
        TreeNode* p = node->parent;
        while (p != nullptr && node == p->right) {
            node = p;
            p = p->parent;
        }
        return p;
    }

    TreeNode* get_successor(data_type key) {
        return get_successor(find_node(key));
    }

    TreeNode* get_predecessor(TreeNode* node) {
        if (node == nullptr) return nullptr;
        if (node->left != nullptr) {
            TreeNode* current = node->left;
            while (current->right != nullptr) current = current->right;
            return current;
        }
        TreeNode* p = node->parent;
        while (p != nullptr && node == p->left) {
            node = p;
            p = p->parent;
        }
        return p;
    }

    TreeNode* get_predecessor(data_type key) {
        return get_predecessor(find_node(key));
    }

// =========================================================
// FUNCIONES PRIVADAS (Auxiliares recursivos y lógica interna)
// =========================================================
private:
    void pre_order_aux(TreeNode* node) {
        if (node != nullptr) {
            cout << node->data << " ";  
            pre_order_aux(node->left);  
            pre_order_aux(node->right); 
        }
    }

    void in_order_aux(TreeNode* node) {
        if (node != nullptr) {
            in_order_aux(node->left);   
            cout << node->data << " ";  
            in_order_aux(node->right);  
        }
    }

    void post_order_aux(TreeNode* node) {
        if (node != nullptr) {
            post_order_aux(node->left);   
            post_order_aux(node->right);  
            cout << node->data << " ";    
        }
    }

    int size_aux(TreeNode* node) {
        if (node == nullptr) return 0;
        return 1 + size_aux(node->left) + size_aux(node->right);
    }

    void clear(TreeNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Lógica para reemplazar subárboles (Apoyo para Erase)
    void transplant(TreeNode* u, TreeNode* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    // Lógica principal de eliminación CLRS
    void erase(TreeNode* z) {
        if (z->left == nullptr) {
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            transplant(z, z->left);
        } else {
            // Buscar sucesor
            TreeNode* y = z->right;
            while (y->left != nullptr) {
                y = y->left;
            }

            if (y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z; // Liberar memoria
    }
};

#endif //BST_BST_H
