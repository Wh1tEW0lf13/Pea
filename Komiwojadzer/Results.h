//
// Created by Wh1tEW0lf13 on 16.03.2026.
//

#ifndef RESULTS_H
#define RESULTS_H
#include <chrono>


class Results {
    std::string _algorithmName;
    int _size;
    int _numberOfPermutations;
    int _minPath;
    int* _minPathVertexes;
    long long _timeResult;

public:
    Results(std::string algorythmName, int size, int numberOfPermutations, int minPath, int* minPathVertexes, long long time);
    ~Results();
    std::chrono::milliseconds getTime();
    void start();
    void stop();
    void reset();
    int saveResultsToFile();
    static int saveMatrixToFile(int ** matrix, int size);
};



#endif //RESULTS_H
