//
// Created by Wh1tEW0lf13 on 15.04.2026.
//

#include "Queue.h"

Queue::Node::Node(BreadthFirstSearch::StateNodeQueue* val) : data(val), next(nullptr) {}

Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}
Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}
void Queue::enqueue(BreadthFirstSearch::StateNodeQueue* val) {
    Node* newNode = new Node(val);

    if (head == nullptr) {
        head = tail = newNode;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

void Queue::dequeue() {
    if (isEmpty()) {
        return;
    }

    Node* oldHead = head;

    head = oldHead->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete oldHead;
}
BreadthFirstSearch::StateNodeQueue* Queue::front() {
    if (isEmpty()) {
        return nullptr;
    }
    return head->data;
}
bool Queue::isEmpty() {
    return head == nullptr;
}