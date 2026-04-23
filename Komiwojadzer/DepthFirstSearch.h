#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include <climits>

class DepthFirstSearch {
private:
    int N;
    int minTotalCost;
    int* bestPath;
    int** _initialMatrix;
    const int INF = INT_MAX;

    void copyMatrix(int** src, int** dest);
    int reduceMatrix(int** matrix);
    void solveRecursive(int** currentMatrix, int currentBound, int currentVertex, int level, int* currentPath);
public:

    DepthFirstSearch(int size, int **initialMatrix);
    ~DepthFirstSearch();

    void algorithm();
};

#endif // TSPSOLVER_H