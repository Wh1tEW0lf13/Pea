//
// Created by Wh1tEW0lf13 on 15.03.2026.
//

#ifndef MONTECARLO_H
#define MONTECARLO_H
#include "Results.h"


class Random {
private:
    int **_cities;
    int _size;
    int _numberOfPermutations;
public:
    Random(int **cities, int size, int numberOfPermutations);
    void algorythm();
};



#endif //MONTECARLO_H
