//
// Created by DELL on 17.04.2026.
//

#include "Stack.h"

Stack::Node::Node(DepthFirstSearch::StateNodeStack *val) : data(val), next(nullptr) {}

Stack::Stack() {
    top = nullptr;
}

Stack::~Stack() {
    while (!isEmpty()) {
        DepthFirstSearch::StateNodeStack* state = topNode();
        pop();
        delete topNode();
    }
}

void Stack::push(DepthFirstSearch::StateNodeStack *val) {
    Node* newNode = new Node(val);
    newNode->next = top;
    top = newNode;
}

DepthFirstSearch::StateNodeStack* Stack::topNode() {
    if (isEmpty()) {
        return nullptr;
    }
    return top->data;
}

void Stack::pop() {
    if (isEmpty()) {
        return;
    }
    Node* temp = top;
    top = top->next;
    delete temp;
}

bool Stack::isEmpty() {
    return top == nullptr;
}


