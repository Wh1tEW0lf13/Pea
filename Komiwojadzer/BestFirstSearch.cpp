//
// Created by Wh1tEW0lf13 on 15.04.2026.
// Wersja: Algorytm Little'a (Branch and Bound oparty na krawędziach)
//

#include "BestFirstSearch.h" // Upewnij się, że zmienisz nazwę pliku nagłówkowego
#include "PriorityQueue.h"
#include <climits>
#include "Results.h"
#include "Timer.h"

BestFirstSearch::BestFirstSearch(int **cities, int size) {
    _cities = cities;
    _size = size;
}

void BestFirstSearch::algorythm() {
    Timer timer;
    bool pass = true;
    timer.start();
    PriorityQueue* pq = new PriorityQueue();
    int minTourCost = INT_MAX;
    int* bestPath = new int[_size + 1]();

    StateNodeQueue* root = createRootNode(_cities);
    pq->enqueue(root);

    while (!pq->isEmpty()) {
        if (timer.getTime() > 7200) {
            pass = false;
            break;
        }
        StateNodeQueue* current = pq->front();
        pq->dequeue();

        // Odcięcie (Pruning)
        if (current->cost >= minTourCost) {
            delete current;
            continue;
        }

        // Jeśli wybraliśmy już wszystkie N krawędzi, to mamy pełen cykl
        if (current->numEdges == _size) {
            if (current->cost < minTourCost) {
                minTourCost = current->cost;
                buildPathFromEdges(current->includedEdges, bestPath);
            }
            delete current;
            continue;
        }

        // KROK 1: Obliczanie kar (penalty) dla zer i wybór krawędzi do podziału
        int maxPenalty = -1;
        int branchU = -1;
        int branchV = -1;

        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) {
                if (current->matrix[i][j] == 0) {
                    int minRow = INT_MAX;
                    int minCol = INT_MAX;

                    // Szukamy minimum w wierszu (oprócz obecnego zera)
                    for (int k = 0; k < _size; k++) {
                        if (k != j && current->matrix[i][k] < minRow) minRow = current->matrix[i][k];
                    }
                    // Szukamy minimum w kolumnie (oprócz obecnego zera)
                    for (int k = 0; k < _size; k++) {
                        if (k != i && current->matrix[k][j] < minCol) minCol = current->matrix[k][j];
                    }

                    int penalty = 0;
                    if (minRow == INT_MAX || minCol == INT_MAX) {
                        penalty = INT_MAX; // Krawędź krytyczna
                    } else {
                        penalty = minRow + minCol;
                    }

                    if (penalty > maxPenalty) {
                        maxPenalty = penalty;
                        branchU = i;
                        branchV = j;
                    }
                }
            }
        }

        // Jeśli z jakiegoś powodu nie znaleźliśmy zera, przerywamy gałąź
        if (branchU == -1) {
            delete current;
            continue;
        }


        // KROK 2: Tworzenie lewego dziecka (UŻYWAMY krawędzi branchU -> branchV)
        StateNodeQueue* withEdgeNode = createNodeWithEdge(current, branchU, branchV);
        if (withEdgeNode->cost < minTourCost) {
            pq->enqueue(withEdgeNode);
        } else {
            delete withEdgeNode;
        }

        // KROK 3: Tworzenie prawego dziecka (NIE używamy krawędzi branchU -> branchV)
        StateNodeQueue* withoutEdgeNode = createNodeWithoutEdge(current, branchU, branchV);
        if (withoutEdgeNode->cost < minTourCost) {
            pq->enqueue(withoutEdgeNode);
        } else {
            delete withoutEdgeNode;
        }
        delete current;
    }

    delete pq;
    timer.stop();
    Results results("BestFS", _size,pass , minTourCost, bestPath, timer.getTime());
    results.saveResultsToFile();

    delete[] bestPath;
}

BestFirstSearch::StateNodeQueue* BestFirstSearch::createRootNode(int** initialMatrix) {
    StateNodeQueue* root = new StateNodeQueue();
    root->size = _size;
    root->numEdges = 0;
    root->includedEdges = new Edge[_size];

    root->matrix = new int*[_size];
    for (int i = 0; i < _size; i++) {
        root->matrix[i] = new int[_size];
        for (int j = 0; j < _size; j++) {
            if (i != j)
                root->matrix[i][j] = initialMatrix[i][j];
            else
                root->matrix[i][j] = INT_MAX;
        }
    }

    root->cost = reduceMatrix(root->matrix);
    return root;
}

BestFirstSearch::StateNodeQueue* BestFirstSearch::createNodeWithoutEdge(StateNodeQueue* parent, int u, int v) {
    StateNodeQueue* child = new StateNodeQueue();
    child->numEdges = parent->numEdges;
    child->size = _size;
    child->includedEdges = new Edge[_size];
    for(int i = 0; i < parent->numEdges; i++) {
        child->includedEdges[i] = parent->includedEdges[i];
    }

    child->matrix = new int*[_size];
    for (int i = 0; i < _size; i++) {
        child->matrix[i] = new int[_size];
        for (int j = 0; j < _size; j++) {
            child->matrix[i][j] = parent->matrix[i][j];
        }
    }

    // Blokujemy tę krawędź
    child->matrix[u][v] = INT_MAX;

    int reductionCost = reduceMatrix(child->matrix);

    if (parent->cost == INT_MAX || reductionCost == INT_MAX) {
        child->cost = INT_MAX;
    } else {
        // Sprawdzamy czy dodanie nie wywoła overflow
        if (INT_MAX - parent->cost < reductionCost) {
            child->cost = INT_MAX;
        } else {
            child->cost = parent->cost + reductionCost;
        }
    }

    return child;
}

BestFirstSearch::StateNodeQueue* BestFirstSearch::createNodeWithEdge(StateNodeQueue* parent, int u, int v) {
    StateNodeQueue* child = new StateNodeQueue();
    child->size = _size;
    child->numEdges = parent->numEdges + 1;
    child->includedEdges = new Edge[_size];
    for(int i = 0; i < parent->numEdges; i++) {
        child->includedEdges[i] = parent->includedEdges[i];
    }
    // Dodajemy nową krawędź
    child->includedEdges[parent->numEdges].from = u;
    child->includedEdges[parent->numEdges].to = v;

    child->matrix = new int*[_size];
    for (int i = 0; i < _size; i++) {
        child->matrix[i] = new int[_size];
        for (int j = 0; j < _size; j++) {
            child->matrix[i][j] = parent->matrix[i][j];
        }
    }

    // Usuwamy wiersz 'u' i kolumnę 'v'
    for (int k = 0; k < _size; k++) {
        child->matrix[u][k] = INT_MAX;
        child->matrix[k][v] = INT_MAX;
    }

    // Zapobieganie powstawaniu przedwczesnych sub-cykli
    // Szukamy prawdziwego początku łańcucha kończącego się w u
    int startNode = u;
    bool changed = true;
    while(changed) {
        changed = false;
        for(int i = 0; i < parent->numEdges; i++) {
            if(parent->includedEdges[i].to == startNode) {
                startNode = parent->includedEdges[i].from;
                changed = true;
                break;
            }
        }
    }

    // Szukamy prawdziwego końca łańcucha zaczynającego się w v
    int endNode = v;
    changed = true;
    while(changed) {
        changed = false;
        for(int i = 0; i < parent->numEdges; i++) {
            if(parent->includedEdges[i].from == endNode) {
                endNode = parent->includedEdges[i].to;
                changed = true;
                break;
            }
        }
    }

    if (child->numEdges < _size - 1) {
        child->matrix[endNode][startNode] = INT_MAX;
    }

    int reductionCost = reduceMatrix(child->matrix);

    // <--- DODANE ZABEZPIECZENIE PRZED PRZEPEŁNIENIEM
    if (parent->cost == INT_MAX || reductionCost >= INT_MAX - parent->cost) {
        child->cost = INT_MAX;
    } else {
        child->cost = parent->cost + reductionCost;
    }

    return child;
}

int BestFirstSearch::reduceMatrix(int **matrix) {
    int reducedCost = 0;

    for (int i = 0; i < _size; i++) {
        int minRow = INT_MAX;
        for (int j = 0; j < _size; j++) {
            if (matrix[i][j] < minRow) minRow = matrix[i][j];
        }
        if (minRow != INT_MAX && minRow > 0) {
            reducedCost += minRow;
            for (int j = 0; j < _size; j++) {
                if (matrix[i][j] != INT_MAX) matrix[i][j] -= minRow;
            }
        }
    }

    for (int j = 0; j < _size; j++) {
        int minCol = INT_MAX;
        for (int i = 0; i < _size; i++) {
            if (matrix[i][j] < minCol) minCol = matrix[i][j];
        }
        if (minCol != INT_MAX && minCol > 0) {
            reducedCost += minCol;
            for (int i = 0; i < _size; i++) {
                if (matrix[i][j] != INT_MAX) matrix[i][j] -= minCol;
            }
        }
    }
    return reducedCost;
}

void BestFirstSearch::buildPathFromEdges(Edge* edges, int* bestPath) {
    // Ponieważ krawędzie zbieraliśmy w losowej kolejności (zależnie od kar),
    // musimy z nich posklejać ścieżkę w jedną spójną trasę.
    int currentCity = 0;
    bestPath[0] = 0;

    for (int step = 0; step < _size; step++) {
        for (int i = 0; i < _size; i++) {
            if (edges[i].from == currentCity) {
                currentCity = edges[i].to;
                bestPath[step + 1] = currentCity;
                break;
            }
        }
    }
}