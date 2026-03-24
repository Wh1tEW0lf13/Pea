#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include "Komiwojadzer/BruteForce.h"
#include "Komiwojadzer/Random.h"
#include "Komiwojadzer/NearestNeighbor.h"
#include "Komiwojadzer/RepetitiveNearestNeighbour.h"
#include "Komiwojadzer/Results.h"

int choseAlgorythm(int alg, int size, int** cities, int permutations) {
    switch (alg) {
        case 0: {
            BruteForce brute_force(cities, size);
            brute_force.algorythm();
            break;
        }
        case 1: {
            NearestNeighbor nearest_neighbor(cities,size, 0);
            nearest_neighbor.algorythm();
            break;
        }
        case 2: {
            RepetitiveNearestNeighbor repetitive_nearest_neighbor(cities,size);
            repetitive_nearest_neighbor.algorythm();
            break;
        }
        case 3: {
            Random monte_carlo(cities, size, permutations);
            monte_carlo.algorythm();
            break;
        }
        default: {
            std::cout<<"Bad arguments";
            return -1;
        }
    }
    return 1;
}

int getMatrixFromFile(int**& matrix, std::string filePath) {
    std::ifstream file(filePath);
    int size = 0;
    file >> size;
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
    Results::saveMatrixToFile(matrix, size);
    return size;
}

int main(int argc, char *argv[]) {
    int** cities;
    int size;
    if (std::string(argv[1]) == "--last" && (argc == 3 || argc == 4)) {
        size = getMatrixFromFile(cities, "matrix.txt");
        if (argc == 4) {
            choseAlgorythm(std::stoi(argv[2]), size, cities, std::stoi(argv[3]));
        }
        else
            choseAlgorythm(std::stoi(argv[2]), size, cities, 0);
        delete[] cities;
        return 0;
    }
    if (std::string(argv[1]) == "--showLast") {
        size = getMatrixFromFile(cities, "matrix.txt");
        for (int i = 0; i < size; i++) {
            delete[] cities[i];
        }
        delete[] cities;
        return 0;
    }
    if (std::string(argv[1]) == "--file" && (argc == 4 || argc == 5)) {
        size = getMatrixFromFile(cities, argv[2]);
    }

    else if (std::string(argv[1]) == "--random" && (argc == 4 || argc == 5)) {
        size = std::stoi(argv[2]);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist(1, 100);
        cities = new int*[size];

        for (int i = 0; i < size; i++) {
            cities[i] = new int[size];
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    cities[i][j] = -1;
                } else {
                    cities[i][j] = dist(gen);
                }
            }
        }
        Results::saveMatrixToFile(cities, size);
    }
    else {
        std::cout<<"Wrong arguments";
        return -1;
    }
    if (std::stoi(argv[3]) == 3)
        choseAlgorythm(std::stoi(argv[3]), size, cities, std::stoi(argv[4]));
    else
        choseAlgorythm(std::stoi(argv[3]), size, cities, 0);
    for (int i = 0; i < size; i++) {
        delete[] cities[i];
    }
    delete[] cities;
    return 0;
}