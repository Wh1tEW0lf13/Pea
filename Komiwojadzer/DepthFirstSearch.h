//
// Created by Wh1tEW0lf13 on 16.04.2026.
//

#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H



class DepthFirstSearch {
private:
    int _size;
    int **_cities;
    struct StateNode {
        int **matrix = nullptr;
        int cost;
        int level = 0;
        int vertex;
        int *visited;
    };
    StateNode* createRootNode(int ** initialMatrix);
    StateNode* createChildNode(StateNode* parent, int from, int to);
    int reduceMatrix(int** matrix);
    bool isVisited(int* path, int vertex);
public:
    DepthFirstSearch(int **cities, int size);
    void algorythm();
};



#endif //DEPTHFIRSTSEARCH_H
