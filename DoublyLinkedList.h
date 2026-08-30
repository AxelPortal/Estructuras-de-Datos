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

    void print() {
        DoublyLinkedNode<data_type>* current = head;
        while (current != nullptr) {
            cout << current -> data << " ";
            current = current -> next;
        }
        cout << '\n';
    }
};



#endif //ESTRUCTURAS_DOUBLYLINKEDLIST_H