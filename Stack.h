//
// Created by axelr on 7/09/2026.
//

#ifndef ESTRUCTURAS_STACK_H
#define ESTRUCTURAS_STACK_H

template<typename data_type>
struct StackNode {
    data_type data;
    StackNode* next;

    StackNode(data_type data) : data(data), next(nullptr) {}
};

template<typename data_type>
struct Stack {

    StackNode<data_type>* _top;

    Stack() {
        _top = nullptr;
    }

    void push(data_type value) {
        StackNode* new_node = new StackNode(value);
        new_node -> next = _top;
        _top = new_node;
    }

    void pop() {
        if (_top != nullptr) {
            StackNode<data_type>* temp = _top;
            _top = _top->next;
            delete temp;
        }
    }

    data_type top() {
        if (_top==nullptr)
            return data_type();
        return _top -> data;
    }

    bool empty() {
        return _top == nullptr;
    }

    ~Stack() {
        while (_top != nullptr) {
            StackNode<data_type>* temp = _top;
            _top = _top->next;
            delete temp;
        }
    }
};




#endif //ESTRUCTURAS_STACK_H