#pragma once
#include "City.h"

class ReadInput;

template<typename T>
class Vector;

class CityDictionary
{
private:
	List<City*>* myCities[MAX_CITIES];
	City*** myCitiesXY;
	int numbCities;
	int sizeX;
	int sizeY;

public:
	CityDictionary(int sizeX, int sizeY);
	~CityDictionary();
	void dijkstraAlghoritm(City* start_c, City* end_c, int q_type);
	void findPath(int startID, SaveRoad dest, SaveRoad* my_path);
	void add_city(City* city, int& x, int& y);
	City* get_city(const char* city_name);
	City* get_city(const int x, const int y) const;
	void setNumberCities(const int new_number);
};

