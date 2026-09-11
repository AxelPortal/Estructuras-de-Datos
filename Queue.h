//
// Created by axelr on 7/09/2026.
//

#ifndef ESTRUCTURAS_QUEUE_H
#define ESTRUCTURAS_QUEUE_H

template<typename data_type>
struct QueueNode {
    data_type data;
    QueueNode* next;

    QueueNode() {}

    QueueNode(data_type data) : data(data), next(nullptr) {}
};


template<typename data_type>
struct Queue {

    QueueNode* _front, *_back;

    Queue() {
        _front = nullptr;
        _back = nullptr;
    }

    void push(data_type value) {
        if (_front == nullptr) {
            _front = new QueueNode(value);
            _back = _front;
        }
        else {
            _back->next = new QueueNode(value);
            _back = _back -> next;
        }
    }

    void pop() {
        if (_front != nullptr) {

            if (_front == _back) {
                delete _front;
                _front = nullptr;
                _back = nullptr;
            }
            else {
                QueueNode<data_type>* temp = _front;
                _front = _front->next;
                delete temp;
            }
        }
    }

    data_type front() {
        return _front == nullptr ? data_type() : _front -> data;
    }

    bool empty() {
        return _front == nullptr;
    }

    ~Queue() {
        while (_front != nullptr) {
            QueueNode<data_type>* temp = _front;
            _front = _front->next;
            delete temp;
        }

        _back = nullptr;
    }
};


#endif //ESTRUCTURAS_QUEUE_H