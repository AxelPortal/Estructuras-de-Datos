//
// Created by axelr on 7/09/2026.
//

#ifndef ESTRUCTURAS_DEQUE_H
#define ESTRUCTURAS_DEQUE_H

template<typename data_type>
struct DequeNode {
    data_type data;
    DequeNode* next;
    DequeNode* prev;

    DequeNode() : next(nullptr), prev(nullptr) {}

    DequeNode(data_type data) : data(data), next(nullptr), prev(nullptr) {}
};


template<typename data_type>
struct Deque {


    DequeNode* _front;
    DequeNode* _back;

    Deque() {
        _front = nullptr;
        _back = nullptr;
    }

    void push_back(data_type value) {
        if (_front == nullptr) {
            _front = new DequeNode(value);
            _back = _front;
        }
        else {
            _back -> next = new DequeNode(value);
            _back -> next -> prev = _back;
            _back = _back -> next;
        }
    }

    void push_front(data_type value) {
        if (_front == nullptr) {
            _front = new DequeNode(value);
            _back = _front;
        }
        else {
            _front -> prev = new DequeNode(value);
            _front -> prev -> next = _front;
            _front = _front -> prev;
        }
    }

    void pop_back() {
        if (_back == nullptr)
            return;

        DequeNode<data_type>* temp = _back;

        if (_front == _back) {
            _front = nullptr;
            _back = nullptr;
        }
        else {
            _back = _back->prev;
            _back->next = nullptr;
        }

        delete temp;
    }

    void pop_front() {
        if (_front == nullptr)
            return;

        DequeNode<data_type>* temp = _front;

        if (_front == _back) {
            _front = nullptr;
            _back = nullptr;
        }
        else {
            _front = _front->next;
            _front->prev = nullptr;
        }

        delete temp;
    }

    data_type front() {
        return _front == nullptr ? data_type() : _front->data;
    }

    data_type back() {
        return _back == nullptr ? data_type() : _back->data;
    }

    bool empty() {
        return _front == nullptr;
    }

    ~Deque() {
        while (_front != nullptr) {
            DequeNode<data_type>* temp = _front;
            _front = _front->next;
            delete temp;
        }

        _back = nullptr;
    }
};


#endif //ESTRUCTURAS_DEQUE_H