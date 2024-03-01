#define _CRT_SECURE_NO_WARNINGS
#include "City.h"
#include <string.h>
#include <iostream>


City::City(CityVertex vertex, const char* city_name) {
	hash_code = generate_hashcode(name);
	this->vertex = vertex;
	strncpy(name, city_name, MAX_CITY_NAME);
	name[MAX_CITY_NAME - 1] = '\0';
}

City::City(CityVertex vertex)
{
	this->vertex = vertex;
}

City::City(const char* city_name)
{
	strncpy(name, city_name, MAX_CITY_NAME);
	name[MAX_CITY_NAME - 1] = '\0';
}

void City::update_hashcode()
{
	hash_code = generate_hashcode(name);
}

int City::generate_hashcode(const char* city_name) {
	int code = 0;
	for (int i = 0; city_name[i] != 0; i++)
	{
		code += city_name[i];
	}
	return code %= MAX_CITIES;
}

void City::addRoad(Road* new_road) {
	neighbors.add(new_road);
}

List<Road*>* City::getNeighbors() {
	return &neighbors;
}

int City::getX() const {
	return vertex.x;
}

int City::getY() const {
	return vertex.y;
}

int City::getID() const {
	return vertex.id;
}

int City::get_hashcode() const {
	return hash_code;
}

char* City::get_name() {
	return name;
}
