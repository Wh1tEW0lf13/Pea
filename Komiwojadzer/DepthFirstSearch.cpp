#include "DepthFirstSearch.h"
#include "Results.h"
#include "Timer.h"
#include <iostream>
#include <climits> // Upewnij się, że masz to załączone dla INT_MAX

DepthFirstSearch::DepthFirstSearch(int size, int **initialMatrix) : N(size), minTotalCost(INT_MAX) {
    bestPath = new int[N];
    _initialMatrix = initialMatrix;
}

DepthFirstSearch::~DepthFirstSearch() {
    delete[] bestPath;
}
void DepthFirstSearch::copyMatrix(int** src, int** dest) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (src[i][j] == -1)
                dest[i][j] = INT_MAX;
            else
                dest[i][j] = src[i][j];
        }
    }
}

int DepthFirstSearch::reduceMatrix(int** matrix) {
    int reductionCost = 0;

    for (int i = 0; i < N; i++) {
        int rowMin = INT_MAX;
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] < rowMin) rowMin = matrix[i][j];
        }
        if (rowMin != INT_MAX && rowMin > 0) {
            reductionCost += rowMin;
            for (int j = 0; j < N; j++) {
                if (matrix[i][j] != INT_MAX) matrix[i][j] -= rowMin;
            }
        }
    }

    for (int j = 0; j < N; j++) {
        int colMin = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (matrix[i][j] < colMin) colMin = matrix[i][j];
        }
        if (colMin != INT_MAX && colMin > 0) {
            reductionCost += colMin;
            for (int i = 0; i < N; i++) {
                if (matrix[i][j] != INT_MAX) matrix[i][j] -= colMin;
            }
        }
    }
    return reductionCost;
}

void DepthFirstSearch::solveRecursive(int** currentMatrix, int currentBound, int currentVertex, int level, int* currentPath) {
    if (level == N - 1) {
        if (currentBound < minTotalCost) {
            minTotalCost = currentBound;
            for (int i = 0; i < N; i++) bestPath[i] = currentPath[i];
        }
        return;
    }

    for (int nextV = 0; nextV < N; nextV++) {
        if (currentMatrix[currentVertex][nextV] != INT_MAX) {
            int** nextMatrix = new int*[N];
            for (int i = 0; i < N; i++) nextMatrix[i] = new int[N];

            copyMatrix(currentMatrix, nextMatrix);
            int edgeWeight = currentMatrix[currentVertex][nextV];

            for (int k = 0; k < N; k++) {
                nextMatrix[currentVertex][k] = INT_MAX;
                nextMatrix[k][nextV] = INT_MAX;
            }
            nextMatrix[nextV][0] = INT_MAX;

            int reduction = reduceMatrix(nextMatrix);
            int nextBound = currentBound + edgeWeight + reduction;

            if (nextBound < minTotalCost) {
                currentPath[level + 1] = nextV;
                solveRecursive(nextMatrix, nextBound, nextV, level + 1, currentPath);
            }

            for (int i = 0; i < N; i++) delete[] nextMatrix[i];
            delete[] nextMatrix;
        }
    }
}

void DepthFirstSearch::algorithm() {
    Timer timer;
    timer.start();


    minTotalCost = INT_MAX;

    int* currentPath = new int[N];
    currentPath[0] = 0;

    int** matrixCopy = new int*[N];
    for(int i = 0; i < N; i++) matrixCopy[i] = new int[N];
    copyMatrix(_initialMatrix, matrixCopy);

    int initialBound = reduceMatrix(matrixCopy);

    if (initialBound < minTotalCost) {
        solveRecursive(matrixCopy, initialBound, 0, 0, currentPath);
    }

    timer.stop();
    Results results("DFS", N, 0, minTotalCost, bestPath, timer.getTime());
    results.saveResultsToFile();

    for(int i = 0; i < N; i++) delete[] matrixCopy[i];
    delete[] matrixCopy;
    delete[] currentPath;
}