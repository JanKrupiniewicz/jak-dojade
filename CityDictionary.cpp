#define _CRT_SECURE_NO_WARNINGS
#include "CityDictionary.h"
#include "PriorityQueue.h"
#include "Vector.h"
#include "Stack.h"
#include "Vector.cpp"
#include "Stack.cpp"
#include <iostream>
#include <string.h>
#include <climits>

using std::cout;
using std::endl;

CityDictionary::CityDictionary(int sizeX, int sizeY)
	: numbCities(0), sizeX(sizeX), sizeY(sizeY)
{
	myCitiesXY = new City * *[sizeX];
	for (int i = 0; i < sizeX; i++)
	{
		myCitiesXY[i] = new City * [sizeY];
		for (int j = 0; j < sizeY; j++)
		{
			myCitiesXY[i][j] = nullptr;
		}
	}

    for (int i = 0; i < MAX_CITIES; i++)
    {
        myCities[i] = nullptr;
    }
}

void CityDictionary::add_city(City* city, int& x, int& y) 
{
	int new_hash = city->get_hashcode();
	if (myCities[new_hash] == NULL) {
		myCities[new_hash] = new List<City*>();
		myCities[new_hash]->add(city);
	}
	else {
		myCities[new_hash]->add(city);
	}
	myCitiesXY[x][y] = city;
}

City* CityDictionary::get_city(const char* city_name) 
{
    List<City*>* cities = myCities[City::generate_hashcode(city_name)];
	if (cities->getSize() == 1) 
    {
		return cities->get(0);
	}
	else if (cities->getSize() > 1)
    {
        for (List<City*>::iterator it = cities->begin(); it != cities->end(); ++it)
        {
            City* city = *it;
            if (strcmp(city->get_name(), city_name) == 0)
                return city;
        }
	}
	return nullptr;
}

void CityDictionary::findPath(int startID, SaveRoad dest, SaveRoad* my_path)
{
    if (startID == dest.current.id)
    {
        return;
    }

    Stack<CityVertex> vertexes;
    CityVertex vertex = dest.last;
    while (vertex.id != startID)
    {
        vertexes.add(vertex);
        vertex = my_path[vertex.id].last;
    }
    while (!vertexes.empty())
    {
        City* current_city = this->get_city(vertexes.get()->x, vertexes.get()->y);
        cout << current_city->get_name() << " ";
        vertexes.remove();
    }
}

void CityDictionary::dijkstraAlghoritm(City* start_c, City* end_c, int q_type)
{
    PriorityQueue RoadsQueue;
    SaveRoad* my_path = new SaveRoad[numbCities];
    CityVertex new_vertex;
    new_vertex.add_vertex(-1, -1, -1);
    for (int i = 0; i < numbCities; i++)
    {
        my_path[i].travel_time = INT_MAX;
        my_path[i].current = new_vertex;
        my_path[i].last = new_vertex;
    }

    my_path[start_c->getID()].current.id = start_c->getID();
    my_path[start_c->getID()].current.x = start_c->getX();
    my_path[start_c->getID()].current.y = start_c->getY();
    my_path[start_c->getID()].travel_time = 0;
    RoadsQueue.add(my_path[start_c->getID()]);

    while (!RoadsQueue.empty())
    {
        SaveRoad current_road = RoadsQueue.get();
        RoadsQueue.remove();

        if (current_road.current.id == end_c->getID())
        {
            cout << current_road.travel_time << " ";
            if (q_type == 1)
            {
                findPath(start_c->getID(), current_road, my_path);
            }
            delete[] my_path;
            return;
        }

        City* current_city = this->get_city(current_road.current.x, current_road.current.y);

        for (List<Road*>::iterator it = current_city->getNeighbors()->begin(); it != current_city->getNeighbors()->end() ; ++it)
        {
            Road* curr_path = *it;
            City* destCity = curr_path->destination;
            int travel_time = curr_path->travel_time;
            if (my_path[curr_path->destination->getID()].travel_time > my_path[current_road.current.id].travel_time + curr_path->travel_time)
            {
                my_path[curr_path->destination->getID()].travel_time = my_path[current_road.current.id].travel_time + curr_path->travel_time;
                CityVertex myVertex;
                myVertex.add_vertex(current_city->getX(), current_city->getY(), current_city->getID());
                my_path[curr_path->destination->getID()].last = myVertex;
                myVertex.add_vertex(destCity->getX(), destCity->getY(), destCity->getID());
                my_path[curr_path->destination->getID()].current = myVertex;
                RoadsQueue.add(my_path[curr_path->destination->getID()]);
            }
        }
    }
}

City* CityDictionary::get_city(const int x, const int y) const {
	return myCitiesXY[x][y];
}

void CityDictionary::setNumberCities(const int new_number) {
	numbCities = new_number;
}

CityDictionary::~CityDictionary()
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			if (myCitiesXY[i][j] != nullptr)
			{
				delete myCitiesXY[i][j];
			}
		}
		delete[] myCitiesXY[i];
	}
	delete[] myCitiesXY;

	for (int i = 0; i < MAX_CITIES; i++) {
		if (myCities[i] != nullptr) {
			delete myCities[i];
		}
	}
}