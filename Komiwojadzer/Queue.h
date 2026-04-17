//
// Created by Wh1tEW0lf13 on 15.04.2026.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "BreadthFirstSearch.h"


class Queue {
private:
    struct Node {
        BreadthFirstSearch::StateNodeQueue* data;
        Node* next;
        Node(BreadthFirstSearch::StateNodeQueue* val);
    };
    Node* head;
    Node* tail;
public:
    Queue();
    ~Queue();
    void enqueue(BreadthFirstSearch::StateNodeQueue* val);
    void dequeue();
    BreadthFirstSearch::StateNodeQueue* front();
    bool isEmpty();

};



#endif //QUEUE_H
