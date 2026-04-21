//
// Created by Wh1tEW0lf13 on 16.04.2026.
//

#include "DepthFirstSearch.h"
#include <climits>

#include "Results.h"
#include "Stack.h"
#include "Timer.h"

DepthFirstSearch::DepthFirstSearch(int **cities, int size) {
    _cities = cities;
    _size = size;
}

void DepthFirstSearch::algorythm() {
    bool pass = true;
    Timer timer;
    timer.start();
    Stack* stack = new Stack();
    int currentQueueSize = 0;
    const int MAX_QUEUE_NODES = 10000000;

    int * bestPath = new int[_size + 1]();
    int minTourCost = INT_MAX;


    StateNodeStack* root = createRootNode(_cities);

    stack->push(root);
    currentQueueSize ++;
    while (!stack->isEmpty()) {
        if (timer.getCurrentTime() > 240000000 || currentQueueSize > MAX_QUEUE_NODES) {
            pass = false;
            break;
        }
        StateNodeStack* current = stack->topNode();
        stack->pop();
        currentQueueSize --;

        if (current->cost >= minTourCost) {
            freeNode(current);
            continue;
        }

        int N = _size;
        if (current->level == N - 1) {
            if (_cities[current->vertex][0] != INT_MAX) {
                int exactTotalCost = 0;
                for (int i = 0; i < N - 1; i++) {
                    exactTotalCost += _cities[current->visited[i]][current->visited[i+1]];
                }
                exactTotalCost += _cities[current->vertex][0];
                if (exactTotalCost < minTourCost) {
                    minTourCost = exactTotalCost;
                    for (int i = 0; i < N; i++) {
                        bestPath[i] = current->visited[i];
                    }
                    bestPath[N] = 0;
                }
            }
        }
        else {
            for (int j = 0; j < N; j++)
            {
                if (current->matrix[current->vertex][j] != INT_MAX && !isVisited(current->visited, j, current->level)) {
                    StateNodeStack* child = createChildNode(current, current->vertex, j);

                    if (child->cost < minTourCost) {
                        stack->push(child);
                        currentQueueSize ++;
                    }else {
                        freeNode(child);
                    }
                }
            }
        }
        freeNode(current);
    }
    while (!stack->isEmpty()) {
        StateNodeStack* remainingNode = stack->topNode();
        stack->pop();
        freeNode(remainingNode);
    }
    delete stack;
    timer.stop();
    Results results("DFS", _size, pass, minTourCost, bestPath, timer.getTime());
    results.saveResultsToFile();
    delete[] bestPath;
}

DepthFirstSearch::StateNodeStack* DepthFirstSearch::createRootNode(int** initialMatrix) {
    StateNodeStack* root = new StateNodeStack();
    root->visited = new int[_size];
    root->visited[0] = 0;
    root->level = 0;
    root->vertex = 0;
    root->matrix = new int*[_size];
    for (int i = 0; i < _size; i++) {
        root->matrix[i] = new int[_size];
        for (int j = 0; j < _size; j++) {
            root->matrix[i][j] = initialMatrix[i][j];
        }
    }

    root->cost = reduceMatrix(root->matrix);

    return root;
}

DepthFirstSearch::StateNodeStack* DepthFirstSearch::createChildNode(StateNodeStack* parent,
    int from, int to) {
    StateNodeStack* child = new StateNodeStack;

    child->level = parent->level + 1;
    child->vertex = to;

    child->visited = new int[_size + 1];
    for (int i = 0; i <= parent->level; i++) {
        child->visited[i] = parent->visited[i];
    }
    child->visited[parent->level + 1] = to;

    child->matrix = new int*[_size];
    for (int i = 0; i < _size; i++) {
        child->matrix[i] = new int[_size];
        for (int j = 0; j < _size; j++) {
            child->matrix[i][j] = parent->matrix[i][j];
        }
    }

    for (int k = 0; k < _size; k++) {
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
            for (int i = 0; i < N; i++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minCol;
                }
            }
        }
    }
    return reducedCost;
}

bool DepthFirstSearch::isVisited(int* path, int vertex, int current_level) {
    for (int i = 0; i <= current_level; i++) {
        if (path[i] == vertex)
            return true;
    }
    return false;
}

void DepthFirstSearch::freeNode(StateNodeStack* node) {
    if (node == nullptr) return;

    // Usuwanie tablicy visited
    delete[] node->visited;

    // Usuwanie macierzy
    if (node->matrix != nullptr) {
        for (int i = 0; i < _size; i++) {
            delete[] node->matrix[i];
        }
        delete[] node->matrix;
    }

    // Na koniec usuwamy sam węzeł
    delete node;
}