//
// Created by Wh1tEW0lf13 on 16.03.2026.
//

#include "Results.h"
#include <chrono>
#include <fstream>
#include <iostream>
Results::Results(std::string algorythmName, int size, int numberOfPermutations, int minPath, int* minPathVertexes, int time) {
    _minPath = minPath;
    _algorithmName = algorythmName;
    _numberOfPermutations = numberOfPermutations;
    _size = size;
    _minPathVertexes = minPathVertexes;
    _timeResult = time;
}
int Results::saveResultsToFile() {
    std::ofstream file("wynik.csv", std::ios::app);
    if (!file.is_open()) {
        std::cout << "Nie mozna otworzyc pliku!" << std::endl;
        return -1;
    }
    std::cout<<"Path: "<<std::to_string(_minPath)<<'\n';
    for (int i = 0; i < _size - 1; i++) {
        std::cout<<_minPathVertexes[i]<<" -> ";
    }
    std::cout<<_minPathVertexes[_size - 1]<<'\n';
    std::cout<<"Time: "<<std::to_string(_timeResult)<< " us";
    file << _algorithmName +"," + std::to_string(_size) +","+ std::to_string(_numberOfPermutations) +","+ std::to_string(_minPath) + "," + std::to_string(_timeResult) + '\n';
    file.close();
    return 1;
}

int Results::saveMatrixToFile(int** matrix, int size) {
    std::ofstream file("matrix.txt");
    file << size;
    file << '\n';
    std::cout<<"Size: "<<size<<'\n';
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j] << ' ';
            file << matrix[i][j] << " ";
        }
        std::cout << '\n';
        file << '\n';
    }
    file.close();
    return 1;
}

Results::~Results() = default;

