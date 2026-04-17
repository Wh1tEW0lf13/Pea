//
// Created by Wh1tEW0lf13 on 16.04.2026.
//

#include "DepthFirstSearch.h"
#include <climits>

#include "Stack.h"

DepthFirstSearch::DepthFirstSearch(int **cities, int size) {
    _cities = cities;
    _size = size;
}

void DepthFirstSearch::algorythm() {
    Stack* stack = new Stack();

    int minTourCost = INT_MAX;
    int * bestPath;

    StateNodeStack* root = createRootNode(_cities);

    stack->push(root);

    while (!stack->isEmpty()) {
        StateNodeStack* current = stack->topNode();
        stack->pop();

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
                    DepthFirstSearch::StateNodeStack* child = createChildNode(current, current->vertex, j);

                    if (child->cost < minTourCost) {
                        stack->push(child);
                    }else {
                        delete child;
                    }
                }
            }
        }
        delete current;
    }
}

DepthFirstSearch::StateNodeStack* DepthFirstSearch::createRootNode(int** initialMatrix) {
    StateNodeStack* root = new StateNodeStack();
    root->visited = new int[_size];
    root->visited[0] = 0;
    root->level = 0;
    root->vertex = 0;
    root->matrix = initialMatrix;

    root->cost = reduceMatrix(root->matrix);

    return root;
}

DepthFirstSearch::StateNodeStack* DepthFirstSearch::createChildNode(DepthFirstSearch::StateNodeStack* parent,
    int from, int to) {
    StateNodeStack* child = new StateNodeStack;

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

int DepthFirstSearch::reduceMatrix(int **matrix) {
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

bool DepthFirstSearch::isVisited(int* path, int vertex) {
    for (int i = 0; i < _size; i++) {
        if (path[i] == vertex)
            return true;
    }
    return false;
}