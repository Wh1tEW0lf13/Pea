//
// Created by Wh1tEW0lf13 on 15.04.2026.
//

#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H



class BreadthFirstSearch {
public:
    struct StateNodeQueue {
        int **matrix = nullptr;
        int cost;
        int level = 0;
        int vertex;
        int *visited;
    };
    BreadthFirstSearch(int** cities, int size);
    void algorythm();
    ~BreadthFirstSearch() = default;
private:
    int** _cities;
    int _size;
    StateNodeQueue* createRootNode(int ** initialMatrix);
    StateNodeQueue* createChildNode(StateNodeQueue* parent, int from, int to);
    int reduceMatrix(int** matrix);
    bool isVisited(int* node, int value, int current_level);
};



#endif //BREADTHFIRSTSEARCH_H
