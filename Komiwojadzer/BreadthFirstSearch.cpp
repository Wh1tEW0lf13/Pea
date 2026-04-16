//
// Created by Wh1tEW0lf13 on 15.04.2026.
//
#include "BreadthFirstSearch.h"

#include <algorithm>
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

    StateNode* root = createRootNode(_cities);

    queue->enqueue(root);

    while (!queue->isEmpty()) {
        StateNode* current = queue->front();
        queue->dequeue();

        if (current->cost >= minTourCost) {
            delete current;
            continue;
        }

        int N = _size;
        if (current->level == N - 1) {
            int returnCost = current->matrix[current->vertex][0];
            if (returnCost != INT_MAX) {
                int totalCost = current->matrix[current->vertex][0];
                if (totalCost < minTourCost) {
                    minTourCost = totalCost;
                    for (int i = 0; i<N; i++) {
                        bestPath[i] = current->visited[i];
                    }
                    bestPath[N] = 0;
                }
            }
        }
        else {
            for (int j = 0; j < N; j++)
            {
                if (current->matrix[current->vertex][j] != INT_MAX && !isVisited(current->visited, j)){
                    BreadthFirstSearch::StateNode* child = createChildNode(current, current->vertex, j);

                    if (child->cost < minTourCost) {
                        queue->enqueue(child);
                    }else {
                        delete child;
                    }
                }
            }
        }
        delete current;
    }
}

BreadthFirstSearch::StateNode* BreadthFirstSearch::createRootNode(int** initialMatrix) {
    StateNode* root = new StateNode();
    root->visited = new int[_size];
    root->visited[0] = 0;
    root->level = 0;
    root->vertex = 0;
    root->matrix = initialMatrix;

    root->cost = reduceMatrix(root->matrix);

    return root;
}

BreadthFirstSearch::StateNode* BreadthFirstSearch::createChildNode(BreadthFirstSearch::StateNode* parent,
    int from, int to) {
    StateNode* child = new StateNode;

    child->level = parent->level + 1;
    child->vertex = to;

    child->visited = new int[_size + 1];
    for (int i = 0; i < parent->level; i++) {
        child->visited[i] = parent->visited[i];
    }
    child->visited[parent->level] = to;

    child->matrix = new int*[_size];
    for (int i = 0; i < _size; i++) {
        child->matrix[i] = new int[_size];
        for (int j = 0; j< _size; j++) {
            child->matrix[i][j] = parent->matrix[i][j];
        }
    }

    for (int k = 0; k < parent->level; k++) {
        child->matrix[from][k] = INT_MAX;
        child->matrix[k][to] = INT_MAX;
    }
    int startCity = child->visited[0];
    child->matrix[to][startCity] = INT_MAX;

    int reductionCost = reduceMatrix(child->matrix);
    child->cost = parent->cost + parent->matrix[from][to] + reductionCost;

    return child;
}

int BreadthFirstSearch::reduceMatrix(int **matrix) {
    int N = _size;
    int reducedCost = 0;

    for (int i = 0; i < N; i++) {
        int minRow = INT_MAX;
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] < minRow) {
                minRow = matrix[i][j];
            }
        }
        if (minRow != INT_MAX && minRow > 0) {
            reducedCost += minRow;
            for (int j = 0; j < N; j++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minRow;
                }
            }
        }
    }

    for (int j = 0; j < N; j++) {
        int minCol = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (matrix[i][j] < minCol) {
                minCol = matrix[i][j];
            }
        }
        if (minCol != INT_MAX && minCol > 0) {
            reducedCost += minCol;
        }
        if (minCol != INT_MAX && minCol > 0) {
            reducedCost += minCol;
            for (int i = 0; i < N; i++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minCol;
                }
            }
        }
    }
    return reducedCost;
}

bool BreadthFirstSearch::isVisited(int* path, int vertex) {
    for (int i = 0; i < _size; i++) {
        if (path[i] == vertex)
            return true;
    }
    return false;
}