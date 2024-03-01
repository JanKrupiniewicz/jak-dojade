#ifndef AISD2_1_ReadInput_H
#define AISD2_1_ReadInput_H

#include <iostream>
#include "CityDictionary.h"
#include "Queue.h"

using namespace std;

class ReadInput {
private:
    char** map;
    int sizeX, sizeY;
    int numbFlights;
    int numbCities;
    int numbQuestions;
    char** cities;
    CityVertex* vertices;
    CityDictionary cityDictionary;

    void findNeighbors(City* city);
    void checkRoads(int& x, int& y, int& time, Queue* searchR, City* city, Vector<Wsp>& my_cities, Vector<Wsp>& my_roads);
    void readName(int x, int y, City* city);
    void findName(int x, int y, City* city);
    char* getCityNames();

public:
    ReadInput(int n, int m);
    ~ReadInput();
    void passMap();
    void passAirConnetions();
    void operateQuestions();

};


#endif
