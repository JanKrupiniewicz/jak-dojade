#pragma once
#include "List.h"
#include "List.cpp"

#define MAX_CITIES 10000
#define MAX_CITY_NAME 32

class City;

struct CityVertex {
	int x, y, id;

	CityVertex() = default;

	void add_vertex(int x, int y, int id) {
		this->x = x;
		this->y = y;
		this->id = id;
	}
};

struct SaveRoad {
	CityVertex last;
	CityVertex current;
	int travel_time;

	SaveRoad() = default;
};

struct Road {
	City* destination;
	int travel_time;

	Road() = default;

	Road(City* destination, int travel_time) {
		this->destination = destination;
		this->travel_time = travel_time;
	}
};

class City {
	CityVertex vertex;
	List<Road*> neighbors;
	char name[MAX_CITY_NAME];
	int hash_code;
public:
	City() = default;
	City(CityVertex vertex, const char* city_name);
	City(CityVertex vertex);
	City(const char* city_name);
	void update_hashcode();
	static int generate_hashcode(const char* city_name);
	int get_hashcode() const;
	char* get_name();
	int getX() const;
	int getY() const;
	int getID() const;
	void addRoad(Road* new_road);
	List<Road*>* getNeighbors();
};
