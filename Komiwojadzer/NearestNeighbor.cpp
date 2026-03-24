//
// Created by Wh1tEW0lf13 on 12.03.2026.
//

#include "NearestNeighbor.h"
#include <iostream>

#include "Results.h"
#include "Timer.h"

NearestNeighbor::NearestNeighbor(int ** cities, int size, int startCity) {
    _cities = cities;
    _size = size;
    _startCity = startCity;
}

void NearestNeighbor::algorythm() {
    Timer timer;
    timer.reset();
    timer.start();
    bool* visited = new bool[_size];
    int * path = new int[_size];
    path[0] = 0;
    for (int j = 0; j < _size; j++) {
        visited[j] = false;
    }
    int distance = 0;
    int nextCity = 0;
    int actualCity = _startCity;
    visited[_startCity] = true;
    for (int step = 0; step < _size - 1; step++) {
        int minDistance = INT_MAX;
        for (int j = 0; j < _size; j++) {
            if (!visited[j] && minDistance > _cities[actualCity][j]) {
                minDistance = _cities[actualCity][j];
                nextCity = j;
            }
        }
        path[step + 1] = nextCity;
        distance += minDistance;
        actualCity = nextCity;
        visited[actualCity] = true;
    }
    distance += _cities[actualCity][_startCity];
    timer.stop();
    Results results("NearestNeighbor", _size, 0 , distance, path, timer.getTime());
    results.saveResultsToFile();

    delete [] visited;
    delete [] path;
}
