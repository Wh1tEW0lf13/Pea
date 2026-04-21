//
// Created by Wh1tEW0lf13 on 15.04.2026.
//
#include "BreadthFirstSearch.h"
#include <climits>
#include "Queue.h"
#include "Results.h"
#include "Timer.h"
#include <iostream>

BreadthFirstSearch::BreadthFirstSearch(int **cities, int size) {
    _cities = cities;
    _size = size;
}
int BreadthFirstSearch::calculateInitialBoundNN(int* initialBestPath) {
    bool* visited = new bool[_size](); // Inicjalizacja zerami (false)
    int currentCity = 0;
    visited[currentCity] = true;
    initialBestPath[0] = currentCity;
    int totalCost = 0;

    for (int step = 1; step < _size; step++) {
        int nearestCity = -1;
        int minDistance = INT_MAX;

        // Szukamy najbliższego nieodwiedzonego sąsiada
        for (int nextCity = 0; nextCity < _size; nextCity++) {
            if (!visited[nextCity] &&
                _cities[currentCity][nextCity] != INT_MAX &&
                _cities[currentCity][nextCity] < minDistance) {

                minDistance = _cities[currentCity][nextCity];
                nearestCity = nextCity;
                }
        }

        // Jeśli udało się znaleźć ścieżkę
        if (nearestCity != -1) {
            totalCost += minDistance;
            visited[nearestCity] = true;
            currentCity = nearestCity;
            initialBestPath[step] = currentCity;
        } else {
            // Graf niespójny lub brak przejścia - bezpieczny fallback
            delete[] visited;
            return INT_MAX;
        }
    }

    // Powrót do miasta startowego
    if (_cities[currentCity][0] != INT_MAX) {
        totalCost += _cities[currentCity][0];
        initialBestPath[_size] = 0;
    } else {
        delete[] visited;
        return INT_MAX; // Bezpieczny fallback
    }

    delete[] visited;
    return totalCost;
}

void BreadthFirstSearch::algorythm() {
    const int MAX_QUEUE_NODES = 20000000;
    int currentQueueSize = 0;
    Timer timer;
    bool pass = true;
    timer.start();
    Queue* queue = new Queue();

    int * bestPath = new int[_size + 1]();
    int minTourCost = calculateInitialBoundNN(bestPath);

    StateNodeQueue* root = createRootNode(_cities);

    queue->enqueue(root);
    currentQueueSize ++;
    while (!queue->isEmpty()) {
        if (timer.getCurrentTime() > 240000000 || currentQueueSize > MAX_QUEUE_NODES) {
            pass = false;
            break;
        }
        StateNodeQueue* current = queue->front();
        queue->dequeue();
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
                    StateNodeQueue* child = createChildNode(current, current->vertex, j);

                    if (child->cost < minTourCost) {
                        queue->enqueue(child);
                        currentQueueSize ++;
                    }else {
                        freeNode(child);
                    }
                }
            }
        }
        freeNode(current);
    }
    while (!queue->isEmpty()) {
        StateNodeQueue* remainingNode = queue->front();
        queue->dequeue();
        freeNode(remainingNode);
    }

    delete queue;
    timer.stop();
    Results results("BFS", _size, pass, minTourCost, bestPath, timer.getTime());
    results.saveResultsToFile();
}

BreadthFirstSearch::StateNodeQueue* BreadthFirstSearch::createRootNode(int** initialMatrix) {
    StateNodeQueue* root = new StateNodeQueue();
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

BreadthFirstSearch::StateNodeQueue* BreadthFirstSearch::createChildNode(StateNodeQueue* parent,
    int from, int to) {
    StateNodeQueue* child = new StateNodeQueue;

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
            for (int i = 0; i < N; i++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minCol;
                }
            }
        }
    }
    return reducedCost;
}

bool BreadthFirstSearch::isVisited(int* path, int vertex, int current_level) {
    for (int i = 0; i <= current_level; i++) {
        if (path[i] == vertex)
            return true;
    }
    return false;
}

void BreadthFirstSearch::freeNode(StateNodeQueue* node) {
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