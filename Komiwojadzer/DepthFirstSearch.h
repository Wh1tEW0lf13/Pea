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
    bool isVisited(int* path, int vertex, int current_level);
public:
    struct StateNodeStack {
        int **matrix = nullptr;
        int cost;
        int level = 0;
        int vertex;
        int *visited;
        int size = 0;
        ~StateNodeStack() {
            // Usuwamy jednowymiarową tablicę visited
            if (visited != nullptr) {
                delete[] visited;
            }

            // Usuwamy dwuwymiarową tablicę (macierz)
            if (matrix != nullptr) {
                for (int i = 0; i < size; i++) {
                    delete[] matrix[i]; // Usuwa poszczególne wiersze
                }
                delete[] matrix; // Usuwa główną tablicę wskaźników
            }
        }
    };
    DepthFirstSearch(int **cities, int size);
    ~DepthFirstSearch() = default;
    void algorythm();
private:
    StateNodeStack* createRootNode(int ** initialMatrix);
    StateNodeStack* createChildNode(StateNodeStack* parent, int from, int to);
};



#endif //DEPTHFIRSTSEARCH_H
