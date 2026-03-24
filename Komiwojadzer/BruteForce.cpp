#include "BruteForce.h"

#include <iostream>

#include "Results.h"
#include "Timer.h"

BruteForce::BruteForce(int** cities, const int size) {
        _cities = cities;
        _size = size;
}

void BruteForce::swap(int *matrix, int pos1, int pos2) {
    int temp = matrix[pos1];
    matrix[pos1] = matrix[pos2];
    matrix[pos2] = temp;
}

void BruteForce::riverse(int* matrix, int start, int end) {
    while (start < end) {
        swap(matrix, start, end);
        start++;
        end--;
    }
}

bool BruteForce::next_permutation(int * citiesToVisit) {
    int i = _size - 3; // by nie wyjść poza tablice
    while (i >= 0 && citiesToVisit[i] >= citiesToVisit[i + 1]) {
        i--;    // wszystkie permutacje wykorzystane?
    }
    if (i < 0) return false;
    int j = _size - 2;
    while (citiesToVisit[j] <= citiesToVisit[i]) {
        j--;
    }
    swap(citiesToVisit,i, j); // zamiana pozycji
    riverse(citiesToVisit, i+1, _size - 2); //
    return true;
}
void BruteForce::algorythm() {
    Timer timer;
    timer.reset();
    timer.start();
    int min = INT_MAX;
    int* path = new int[_size];
    path[0] = 0;
    int* citiesToVisit = new int[_size - 1];
    for (int i = 1; i < _size; i++) {
        citiesToVisit[i-1] = i;
    }
    do {
        int distance = 0;
        int actualCity = 0;
        for (int i = 0; i < _size - 1; i++) {
            int nextCity = citiesToVisit[i];
            distance += _cities[actualCity][nextCity];
            actualCity = nextCity;
        }
        distance += _cities[actualCity][0];
        if (min > distance) {
            min = distance;
            for (int i = 0; i < _size - 1; i++) {
                path[i + 1] = citiesToVisit[i];
            }
        }
    }while (next_permutation(citiesToVisit));
    timer.stop();
    Results results("BruteForce", _size, 0, min, path, timer.getTime());
    results.saveResultsToFile();
    delete [] citiesToVisit;
    delete [] path;
}

bool BruteForce::next_permutation_JT(int* citiesToVisit, int* directions, int n) {
    int mobile_val = -1;
    int mobile_idx = -1;

    for (int i = 0; i < n; i++) {
        int adjacent_idx = i + directions[i];

        // Sprawdzamy, czy sąsiad jest w granicach tablicy
        if (adjacent_idx >= 0 && adjacent_idx < n) {

            if (citiesToVisit[i] > citiesToVisit[adjacent_idx]) {
                if (citiesToVisit[i] > mobile_val) {
                    mobile_val = citiesToVisit[i];
                    mobile_idx = i;
                }
            }
        }
    }

    if (mobile_idx == -1) return false;

    int adjacent_idx = mobile_idx + directions[mobile_idx];

    swap(citiesToVisit, mobile_idx, adjacent_idx);

    //zmieniamy kierunki
    int temp_dir = directions[mobile_idx];
    directions[mobile_idx] = directions[adjacent_idx];
    directions[adjacent_idx] = temp_dir;

    // Odwrócenie kierunków dla wszystkich elementów większych niż mobile_val
    for (int i = 0; i < n; i++) {
        if (citiesToVisit[i] > mobile_val) {
            directions[i] = -directions[i]; // Zmiana z -1 na 1 lub z 1 na -1
        }
    }

    return true;
}

void BruteForce::algorythmJT() {
    Timer timer;
    timer.reset();
    timer.start();

    int min = INT_MAX;
    int* path = new int[_size];
    path[0] = 0;

    int n = _size - 1;
    int* citiesToVisit = new int[n];
    int* directions = new int[n];

    for (int i = 0; i < n; i++) {
        citiesToVisit[i] = i + 1;
        directions[i] = -1; //-1 to znaczy że patrzy w lewo
    }

    do {
        int distance = 0;
        int actualCity = 0;

        for (int i = 0; i < n; i++) {
            int nextCity = citiesToVisit[i];
            distance += _cities[actualCity][nextCity];
            actualCity = nextCity;
        }
        distance += _cities[actualCity][0];

        if (min > distance) {
            min = distance;
            for (int i = 0; i < n; i++) {
                path[i + 1] = citiesToVisit[i];
            }
        }

    } while (next_permutation_JT(citiesToVisit, directions, n));

    timer.stop();
    Results results("BruteForce-Johnson-Trotter", _size, 0, min, path, timer.getTime());
    results.saveResultsToFile();

    delete [] directions;
    delete [] citiesToVisit;
    delete [] path;
}
BruteForce::~BruteForce() = default;
