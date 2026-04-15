//
// Created by Wh1tEW0lf13 on 15.04.2026.
//

#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H



class BreadthFirstSearch {
public:
    struct StateNode {
        int **matrix = nullptr;
        int cost;
        int level = 0;
        int vertex;
        int *visited;
    };
    BreadthFirstSearch(int** cities, int size);
    void algorythm();
    ~BreadthFirstSearch();
private:
    int** _cities;
    int _size;
    StateNode* createRootNode(int ** initialMatrix);
    StateNode* createChildNode(StateNode* parent, int from, int to);
    int reduceMatrix(int** matrix);
};



#endif //BREADTHFIRSTSEARCH_H
