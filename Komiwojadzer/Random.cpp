//
// Created by Wh1tEW0lf13 on 15.03.2026.
//

#include "Random.h"
#include <random>

#include "Timer.h"

Random::Random(int ** cities, int size, int numberOfPermutations) {
    _cities = cities;
    _size = size;
    _numberOfPermutations = numberOfPermutations;
}

void Random::algorythm() {
    Timer timer;
    timer.reset();
    std::random_device rd;
    std::mt19937 gen(rd());
    timer.start();
    int min = INT_MAX;
    int* currentCity = new int[_size];
    int* bestPath = new int[_size];
    for (int i = 0; i < _numberOfPermutations; i++) {
        for (int j = 0; j < _size; j++) {
            currentCity[j] = j;
        }
        for (int j = _size - 1; j > 0; j--) {
            std::uniform_int_distribution<> distrib(0, j);
            int randomIndex = distrib(gen);
            int temp = currentCity[j];
            currentCity[j] = currentCity[randomIndex];
            currentCity[randomIndex] = temp;
        }
        int currentDistance = 0;
        for (int j = 0; j < _size - 1; j++) {
            currentDistance += _cities[currentCity[j]][currentCity[j+1]];
        }
        currentDistance += _cities[currentCity[_size-1]][currentCity[0]];
        if (currentDistance < min) {
            min = currentDistance;

            for (int k = 0; k < _size; k++) {
                bestPath[k] = currentCity[k];
            }
        }
    }
    timer.stop();
    Results results("Random", _size, _numberOfPermutations, min, bestPath, timer.getTime());
    results.saveResultsToFile();
    delete[] currentCity;

}