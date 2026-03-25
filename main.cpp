#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <string>
#include <iomanip>

#include "Komiwojadzer/BruteForce.h"
#include "Komiwojadzer/Random.h"
#include "Komiwojadzer/NearestNeighbor.h"
#include "Komiwojadzer/RepetitiveNearestNeighbour.h"
#include "Komiwojadzer/Results.h"

void freeMatrix(int**& matrix, int size) {
    if (matrix != nullptr) {
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

int choseAlgorythm(int alg, int size, int** cities, int permutations) {
    if (cities == nullptr) {
        std::cout << "Blad: Brak zaladowanych danych!\n";
        return -1;
    }

    switch (alg) {
        case 0: {
            BruteForce brute_force(cities, size);
            brute_force.algorythm();
            break;
        }
        case 1: {
            NearestNeighbor nearest_neighbor(cities, size, 0);
            nearest_neighbor.algorythm();
            break;
        }
        case 2: {
            RepetitiveNearestNeighbor repetitive_nearest_neighbor(cities, size);
            repetitive_nearest_neighbor.algorythm();
            break;
        }
        case 3: {
            Random monte_carlo(cities, size, permutations);
            monte_carlo.algorythm();
            break;
        }
        default: {
            std::cout << "Zly algorytm.\n";
            return -1;
        }
    }
    return 1;
}

int getMatrixFromFile(int**& matrix, std::string filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku " << filePath << "!\n";
        return 0;
    }

    int new_size = 0;
    file >> new_size;
    matrix = new int*[new_size];
    for (int i = 0; i < new_size; i++) {
        matrix[i] = new int[new_size];
        for (int j = 0; j < new_size; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
    Results::saveMatrixToFile(matrix, new_size);
    return new_size;
}

int main(int argc, char *argv[]) {
    int** cities = nullptr;
    int size = 0;
    int permutations = -1;
    int alg = -1;
    int mode = -1;

    while (mode != 0) {
        std::string file_path;
        std::cout << "\n===============================\n";
        std::cout << "1 - Sciezka do pliku\n";
        std::cout << "2 - Wygeneruj dane\n";
        std::cout << "3 - Wyswietl zaladowane dane\n";
        std::cout << "4 - Wlacz algorytm (0: Brute_force, 1: NN, 2: RNN, 3: Losowy)\n";
        std::cout << "5 - Wczytaj ostatnia macierz\n";
        std::cout << "0 - Zakoncz program\n";
        std::cout << "Wybierz mode od 0 do 5: ";
        std::cin >> mode;
        std::cout << std::endl;

        switch (mode) {
            case 1:
                std::cout << "Podaj sciezke do pliku: ";
                std::cin >> file_path;
                freeMatrix(cities, size);
                size = getMatrixFromFile(cities, file_path);
                if (size > 0) std::cout << "Dane zaladowane pomyslnie.\n";
                break;

            case 2:
                std::cout << "Podaj wielkosc: ";
                std::cin >> size;
                if (size <= 0) {
                    std::cout << "Rozmiar musi byc dodatni.\n";
                    break;
                }

                freeMatrix(cities, size);

                {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<int> dist(1, 100);

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
                }
                Results::saveMatrixToFile(cities, size);
                std::cout << "Dane wygenerowane pomyslnie.\n";
                break;

            case 3:
                if (cities == nullptr) {
                    std::cout << "Brak danych! Najpierw zaladuj plik lub wygeneruj macierz.\n";
                } else {
                    std::cout << "Aktualna macierz " << size << "x" << size << ":\n";
                    for (int i = 0; i < size; i++) {
                        for (int j = 0; j < size; j++) {
                            std::cout << std::setw(4) << cities[i][j] << " ";
                        }
                        std::cout << "\n";
                    }
                }
                break;

            case 4:
                if (cities == nullptr) {
                    std::cout << "Najpierw musisz zaladowac lub wygenerowac dane!\n";
                    break;
                }
                std::cout << "Podaj algorytm: 0 - Brute_force, 1 - NN, 2 - RNN, 3 - losowy: ";
                std::cin >> alg;

                if (alg == 3) {
                    std::cout << "Podaj permutacje: ";
                    std::cin >> permutations;
                } else {
                    permutations = 0;
                }

                choseAlgorythm(alg, size, cities, permutations);
                break;

            case 5:
                freeMatrix(cities, size);
                size = getMatrixFromFile(cities, "matrix.txt");
                if (size > 0) std::cout << "Ostatnia macierz zaladowana.\n";
                break;

            case 0:
                std::cout << "Konczenie dzialania programu...\n";
                break;

            default:
                std::cout << "Zla opcja. Sprobuj ponownie.\n";
                break;
        }
    }

    freeMatrix(cities, size);

    return 0;
}