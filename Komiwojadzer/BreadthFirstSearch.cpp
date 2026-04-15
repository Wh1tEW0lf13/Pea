//
// Created by Wh1tEW0lf13 on 15.04.2026.
//

#include "BreadthFirstSearch.h"

#include <climits>

#include "Queue.h"

BreadthFirstSearch::BreadthFirstSearch(int **cities, int size) {
    _cities = cities;
    _size = size;
}

void BreadthFirstSearch::algorythm() {
    Queue* queue = new Queue();

    int minTourCost = INT_MAX;
    int * bestPath;

    StateNode* root = createRootNode()
}
