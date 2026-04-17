//
// Created by DELL on 17.04.2026.
//

#ifndef STACK_H
#define STACK_H

#include "DepthFirstSearch.h"

class Stack {
public:
    Stack();
    ~Stack();
    void push(DepthFirstSearch::StateNodeStack* val);
    void pop();
    DepthFirstSearch::StateNodeStack* topNode();
    bool isEmpty();
    private:
    struct Node {
        DepthFirstSearch::StateNodeStack* data;
        Node* next;
        Node(DepthFirstSearch::StateNodeStack* val);
    };
    Node* top;
};



#endif //STACK_H
