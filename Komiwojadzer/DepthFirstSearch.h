//
// Created by Wh1tEW0lf13 on 16.04.2026.
//

#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H



class DepthFirstSearch {
private:
    int _size;
    int **_cities;
    int reduceMatrix(int** matrix);
    bool isVisited(int* path, int vertex);
public:
    struct StateNodeStack {
        int **matrix = nullptr;
        int cost;
        int level = 0;
        int vertex;
        int *visited;
    };
    DepthFirstSearch(int **cities, int size);
    void algorythm();
private:
    StateNodeStack* createRootNode(int ** initialMatrix);
    StateNodeStack* createChildNode(StateNodeStack* parent, int from, int to);
};



#endif //DEPTHFIRSTSEARCH_H
