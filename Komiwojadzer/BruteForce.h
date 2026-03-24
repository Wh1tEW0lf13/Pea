//
// Created by Wh1tEW0lf13 on 10.03.2026.
//

#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
class BruteForce
{
private:
    // Dodaj te deklaracje do klasy BruteForce
    bool next_permutation_JT(int* citiesToVisit, int* directions, int n);
    int** _cities;
    int _size;
    bool next_permutation(int * citiesToVisit);
    void swap(int* matrix, int pos1, int pos2);
    void riverse(int* matrix, int start, int end);
public:
    BruteForce(int** cities, int size);
    void algorythm();
    void algorythmJT();
    ~BruteForce();
};

#endif //BRUTEFORCE_H
