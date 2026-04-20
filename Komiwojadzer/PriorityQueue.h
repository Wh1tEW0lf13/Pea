//
// Created by Wh1tEW0lf13 on 18.04.2026.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "BestFirstSearch.h"


class PriorityQueue {
    struct Node {
        BestFirstSearch::StateNodeQueue* data;
        Node* next;
        Node(BestFirstSearch::StateNodeQueue* val);
    };
public:
    PriorityQueue();
    ~PriorityQueue() {
        while (!isEmpty()) {
            Node* oldHead = head;
            head = oldHead->next;

            // BARDZO WAŻNE: Musimy usunąć też stan, który trzymamy w środku!
            // Zakłada to, że StateNodeQueue ma poprawny destruktor (który zrobiliśmy wcześniej)
            delete oldHead->data;

            // Na koniec usuwamy sam węzeł kolejki
            delete oldHead;
        }
    }
    void enqueue(BestFirstSearch::StateNodeQueue* val);
    void dequeue();
    BestFirstSearch::StateNodeQueue* front();
    bool isEmpty();
private:
    Node* head;
};



#endif //PRIORITYQUEUE_H
