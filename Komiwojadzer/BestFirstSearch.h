//
// Created by Wh1tEW0lf13 on 18.04.2026.
//

#ifndef BESTFIRSTSEARCH_H
#define BESTFIRSTSEARCH_H



class BestFirstSearch {
private:
    struct Edge {
        int from;
        int to;
    };
    int** _cities;
    int _size;
    int reduceMatrix(int** matrix);
    bool isVisited(int* node, int value, int current_level);
    bool isEmpty();
public:
    BestFirstSearch(int** cities, int size);
    void algorythm();
    ~BestFirstSearch() = default;
    struct StateNodeQueue {
        int** matrix;
        int cost;
        Edge* includedEdges;
        int numEdges;
        int size;
        ~StateNodeQueue() {
            delete[] includedEdges;

            // Usuwanie dwuwymiarowej macierzy
            if (matrix != nullptr) {
                for (int i = 0; i < size; i++) {
                    delete[] matrix[i]; // Zwalnia poszczególne wiersze
                }
                delete[] matrix; // Zwalnia główną tablicę wskaźników
            }
        }
    };
private:
    StateNodeQueue* createRootNode(int ** initialMatrix);
    StateNodeQueue* createChildNode(StateNodeQueue* parent, int from, int to);
    StateNodeQueue* createNodeWithEdge(StateNodeQueue* parent, int u, int v);
    StateNodeQueue* createNodeWithoutEdge(StateNodeQueue* parent, int u, int v);
    void buildPathFromEdges(Edge* edges, int* bestPath);
    void deleteNode(StateNodeQueue* node);
};



#endif //BESTFIRSTSEARCH_H
