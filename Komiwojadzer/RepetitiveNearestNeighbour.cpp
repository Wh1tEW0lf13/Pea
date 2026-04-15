//
// Created by Wh1tEW0lf13 on 14.03.2026.
//

#include "RepetitiveNearestNeighbour.h"
#include <iostream>

#include "Results.h"
#include "Timer.h"

RepetitiveNearestNeighbor::RepetitiveNearestNeighbor(int ** cities, int size) {
    _cities = cities;
    _size = size;
}
void RepetitiveNearestNeighbor::findAllPaths(int currentCity, int startCity, bool* visited, int currentDistance, int visitedCount, int& minResult, int* currentPath, int* bestPath) {
    // Jeśli odwiedziliśmy wszystkie miasta wracamy
    if (visitedCount == _size) {
        int totalDistance = currentDistance + _cities[currentCity][startCity];
        if (totalDistance < minResult) {
            minResult = totalDistance;
            for (int i = 0; i < _size; i++) {
                bestPath[i] = currentPath[i];
            }
        }
        return;
    }

    // Szukamy najmniejszej wagi
    int minWeightForStep = INT_MAX;
    for (int j = 0; j < _size; j++) {
        if (!visited[j] && _cities[currentCity][j] < minWeightForStep) {
            minWeightForStep = _cities[currentCity][j];
        }
    }
    // Sprawdzamy każdą ścieżkę o tej samej minimalnej wadze
    for (int j = 0; j < _size; j++) {
        if (!visited[j] && _cities[currentCity][j] == minWeightForStep) {
            visited[j] = true;
            currentPath[visitedCount] = j;
            findAllPaths(j, startCity, visited, currentDistance + minWeightForStep, visitedCount + 1, minResult, currentPath, bestPath);
            visited[j] = false;
        }
    }
}

void RepetitiveNearestNeighbor::algorythm() {
    Timer timer;
    timer.reset();
    timer.start();
    int globalMin = INT_MAX;
    int* currentPath = new int[_size];
    int* bestPath = new int[_size];

    for (int i = 0; i < _size; i++) {
        bool * visited = new bool[_size];
        for (int j = 0; j < _size; j++) {
            visited[j] = false;
        }
        visited[i] = true;
        currentPath[0] = i;
        findAllPaths(i, i, visited, 0, 1, globalMin, currentPath, bestPath);
        delete [] visited;
    }
    timer.stop();
    Results results("RepetitiveNN", _size, 0, globalMin, bestPath, timer.getTime());
    results.saveResultsToFile();
    delete [] currentPath;
    delete [] bestPath;
}