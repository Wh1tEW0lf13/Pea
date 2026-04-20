#include "PriorityQueue.h"
#include "BestFirstSearch.h"
//
// Created by Wh1tEW0lf13 on 15.04.2026.
//

PriorityQueue::Node::Node(BestFirstSearch::StateNodeQueue* val) : data(val), next(nullptr) {}

PriorityQueue::PriorityQueue() {
    head = nullptr;
}

void PriorityQueue::enqueue(BestFirstSearch::StateNodeQueue* val) {
    Node* newNode = new Node(val);
    if (head == nullptr || val->cost < head->data->cost) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next != nullptr && current->next->data->cost <= val->cost) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void PriorityQueue::dequeue() {
    if (isEmpty()) {
        return;
    }

    Node* oldHead = head;
    head = oldHead->next;

    delete oldHead;
}

BestFirstSearch::StateNodeQueue* PriorityQueue::front() {
    if (isEmpty()) {
        return nullptr;
    }
    return head->data;
}

bool PriorityQueue::isEmpty() {
    return head == nullptr;
}

