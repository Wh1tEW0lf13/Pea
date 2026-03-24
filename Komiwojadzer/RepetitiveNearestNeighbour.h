//
// Created by Wh1tEW0lf13 on 14.03.2026.
//

#ifndef REPETITIVENEARESTNEIGHBOUR_H
#define REPETITIVENEARESTNEIGHBOUR_H



class RepetitiveNearestNeighbor {
private:
    int **_cities;
    int _size;
    void findAllPaths(int currentCity, int startCity, bool* visited, int currentDistance, int visitedCount, int& minResult, int* currentPath, int* bestPath);
public:
    RepetitiveNearestNeighbor(int **cities, int _size);
    void algorythm();
};



#endif //REPETITIVENEARESTNEIGHBOUR_H
