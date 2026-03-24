//
// Created by Wh1tEW0lf13 on 12.03.2026.
//

#ifndef NEARESTNEIGHBOR_H
#define NEARESTNEIGHBOR_H



class NearestNeighbor {
private:
    int **_cities;
    int _size;
    int _startCity;
public:
    NearestNeighbor(int **cities, int _size, int _startCity);
    void algorythm();
};



#endif //NEARESTNEIGHBOR_H
