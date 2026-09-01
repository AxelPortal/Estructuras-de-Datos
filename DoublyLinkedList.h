//
// Created by axelr on 25/08/2026.
//

#ifndef ESTRUCTURAS_DOUBLYLINKEDLIST_H
#define ESTRUCTURAS_DOUBLYLINKEDLIST_H

#include<iostream>
using namespace std;

template<typename data_type>
struct DoublyLinkedNode {
    data_type data;
    DoublyLinkedNode* next;
    DoublyLinkedNode* prev;

    DoublyLinkedNode() {
        next = prev = nullptr;
    }

    DoublyLinkedNode(data_type data, DoublyLinkedNode<data_type>* next = nullptr, DoublyLinkedNode<data_type>* prev = nullptr) : data(data), next(next), prev(prev) {}

};

template<typename data_type>
struct DoublyLinkedList {
    DoublyLinkedNode<data_type>* head;
    DoublyLinkedNode<data_type>* tail;

    DoublyLinkedList() {
        head = tail = nullptr;
    };

    void push_front(data_type value) {
        DoublyLinkedNode<data_type>* new_node = new DoublyLinkedNode<data_type>(value, head);
        if (head == nullptr) {
            tail = new_node;
        }
        else {
            head -> prev = new_node;
        }
        head = new_node;
    }

    void push_back(data_type value) {
        DoublyLinkedNode<data_type>* new_node = new DoublyLinkedNode<data_type>(value, nullptr,tail);

        if (head==nullptr) {
           head = new_node;
        }
        else {
            tail -> next = new_node;
        }
        tail=new_node;
    }

    void erase(DoublyLinkedNode<data_type>* node) {
        // Eliminamos un nodo "node" no nulo
        if (node == head) {
            pop_front();
        }
        else if (node == tail) {
            pop_back();
        }
        else {
            DoublyLinkedNode<data_type>* predecessor = node -> prev;
            DoublyLinkedNode<data_type>* successor = node -> next;
            predecessor -> next = successor;
            successor -> prev = predecessor;
            delete node;
        }
    }

    void delete_first(data_type key) {
        DoublyLinkedNode<data_type>* current = head;
        while (current != nullptr) {
            if (current -> data == key) {
                erase(current);
                break;
            }
            current = current -> next;
        }
    }

    void pop_front() {
        DoublyLinkedNode<data_type>* node = head;
        if (head == tail) {
            delete node;
            head = tail = nullptr;
        }
        else {
            head = head -> next;
            head -> prev = nullptr;
            delete node;
        }
    }

    void pop_back() {
        DoublyLinkedNode<data_type>* node = tail;
        if (head == tail) {
            delete node;
            head = tail = nullptr;
        }
        else {
            tail = tail -> prev;
            tail -> next = nullptr;
            delete node;
        }
    }
    void reverse() {
    DoublyLinkedNode<data_type>* current = head;

    while (current != nullptr) {
        DoublyLinkedNode<data_type>* temp = current->next;

        current->next = current->prev;
        current->prev = temp;

        current = temp;
    }

    DoublyLinkedNode<data_type>* temp = head;
    head = tail;
    tail = temp;
}

    void print() {
        DoublyLinkedNode<data_type>* current = head;
        while (current != nullptr) {
            cout << current -> data << " ";
            current = current -> next;
        }
        cout << '\n';
    }
    void unlink(DoublyLinkedNode<data_type>* node) {
        if (node->prev) node->prev->next = node->next;
        else head = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;
    }

            void insert_before(DoublyLinkedNode<data_type>* node, DoublyLinkedNode<data_type>* ref) {
        if (ref->prev == node) return; // Ya está a la izquierda

        unlink(node);

        node->prev = ref->prev;
        node->next = ref;

        if (ref->prev) ref->prev->next = node;
        else head = node;

        ref->prev = node;
    }




    // Intercambia la posición de dos nodos en O(1)
    void swap_nodes(DoublyLinkedNode<data_type>* u, DoublyLinkedNode<data_type>* v) {
        if (u == v) return;

        // Casos donde son adyacentes
        if (u->next == v) {
            unlink(u);
            // Insertar u después de v
            u->prev = v;
            u->next = v->next;
            if (v->next) v->next->prev = u;
            else tail = u;
            v->next = u;
        } else if (v->next == u) {
            unlink(v);
            // Insertar v después de u
            v->prev = u;
            v->next = u->next;
            if (u->next) u->next->prev = v;
            else tail = v;
            u->next = v;
        } else {
            // Nodos no adyacentes
            DoublyLinkedNode<data_type>* u_prev = u->prev;
            DoublyLinkedNode<data_type>* u_next = u->next;
            DoublyLinkedNode<data_type>* v_prev = v->prev;
            DoublyLinkedNode<data_type>* v_next = v->next;

            unlink(u);
            unlink(v);

            // Colocar v en el lugar original de u
            v->prev = u_prev;
            v->next = u_next;
            if (u_prev) u_prev->next = v;
            else head = v;
            if (u_next) u_next->prev = v;
            else tail = v;

            // Colocar u en el lugar original de v
            u->prev = v_prev;
            u->next = v_next;
            if (v_prev) v_prev->next = u;
            else head = u;
            if (v_next) v_next->prev = u;
            else tail = u;
        }
};



#endif //ESTRUCTURAS_DOUBLYLINKEDLIST_H
