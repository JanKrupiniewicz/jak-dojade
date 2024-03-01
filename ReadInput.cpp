#include "ReadInput.h"
#include "City.h"
#include "Vector.h"
#include "Vector.cpp"
#define MAX_CITIES_VERTEX 150000
#define MAX_CITY_NAME 32

ReadInput::ReadInput(int n, int m) 
    : sizeX(n), sizeY(m), cityDictionary(n, m), numbCities(0), numbFlights(0), numbQuestions(0)
{
    vertices = new CityVertex[MAX_CITIES_VERTEX];
    map = new char* [sizeX];
    for (int i = 0; i < sizeX; i++)
        map[i] = new char[sizeY];
}

void ReadInput::readName(int x, int y, City* city)
{
    while (x >= 0 && map[x][y] >= '0') {
        x--;
    }
    x++;

    int size = 0;
    for (int i = 0; x + i < sizeX && map[x + i][y] >= '0'; i++) {
        city->get_name()[i] = map[x + i][y];
        size++;
    }
    city->get_name()[size] = 0;
    city->update_hashcode();
}

void ReadInput::findName(int x, int y, City* city)
{
    if (y + 1 < sizeY && map[x][y + 1] >= '0')
    {
        readName(x, y + 1, city);
    }
    else if (y - 1 >= 0 && map[x][y - 1] >= '0')
    {
        readName(x, y - 1, city);
    }
    else if (x - 1 >= 0 && y - 1 >= 0 && map[x - 1][y - 1] >= '0')
    {
        readName(x - 1, y - 1,  city);
    }
    else if (x - 1 >= 0 && map[x - 1][y] >= '0')
    {
        readName(x - 1, y, city);
    }
    else if (x - 1 >= 0 && y + 1 < sizeY && map[x - 1][y + 1] >= '0')
    {
        readName(x - 1, y + 1, city);
    }
    else if (x + 1 < sizeX && y - 1 >= 0 && map[x + 1][y - 1] >= '0')
    {
        readName(x + 1, y - 1, city);
    }
    else if (x + 1 < sizeX && map[x + 1][y] >= '0')
    {
        readName(x + 1, y, city);
    }
    else if (x + 1 < sizeX && y + 1 < sizeY && map[x + 1][y + 1] >= '0')
    {
        readName(x + 1, y + 1,  city);
    }
}

char* ReadInput::getCityNames()
{
    char* word = new char[MAX_CITY_NAME];
    int length = 0;
    while (true)
    {
        char c = getchar();
        if (c == ' ')
        {
            break;
        }
        word[length] = c;
        length++;
    }
    word[length] = '\0';
    return word;
}

void ReadInput::operateQuestions()
{
    cityDictionary.setNumberCities(numbCities);
    getchar();
    cin >> numbQuestions;
    for (int i = 0; i < numbQuestions; i++)
    {
        getchar();
        char* source = getCityNames();
        char* destination = getCityNames();
        int q_type; cin >> q_type;
        City* start_c = cityDictionary.get_city(source);
        City* end_c = cityDictionary.get_city(destination);
        cityDictionary.dijkstraAlghoritm(start_c, end_c, q_type);
        cout << '\n';
    }
}

void ReadInput::passAirConnetions()
{
    cin >> numbFlights;
    for (int i = 0; i < numbFlights; i++)
    {
        getchar();
        char* source = getCityNames();
        char* destination = getCityNames();
        int travel_time; cin >> travel_time;
        City* srcCity = cityDictionary.get_city(source);
        City* dstCity = cityDictionary.get_city(destination);
        Road* new_road = new Road(dstCity, travel_time);
        srcCity->addRoad(new_road);

        delete[] source;
        delete[] destination;
    }
}

void ReadInput::passMap() 
{
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++) {
            map[x][y] = getchar();
            if (map[x][y] == '*') {
                vertices[numbCities].add_vertex(x, y, numbCities);
                numbCities++;
            }
        }
        getchar();
    }

    for (int i = 0; i < numbCities; i++) {

        int wsp_x = vertices[i].x;
        int wsp_y = vertices[i].y;
        City* new_city = new City(vertices[i]);
        findName(wsp_x, wsp_y, new_city);
        cityDictionary.add_city(new_city, wsp_x, wsp_y);
    }

    for (int i = 0; i < numbCities; i++) {
        City* curr = cityDictionary.get_city(vertices[i].x, vertices[i].y);
        findNeighbors(curr);
    }
}

void ReadInput::checkRoads(int& x, int& y, int& time, Queue* searchR, City* city, Vector<Wsp>& my_cities, Vector<Wsp>& my_roads)
{
    if (0 > x || x >= sizeX || 0 > y || y >= sizeY)
    {
        return;
    }
    else if (map[x][y] == '#')
    {
        Wsp new_wsp{}; new_wsp.x = x; new_wsp.y = y;
        map[x][y] = '!';
        searchR->add(x, y, time + 1);
        my_roads.add(new_wsp);
    }
    else if (map[x][y] == '*')
    {
        Road* new_road = new Road{ cityDictionary.get_city(x, y),time + 1 };
        Wsp new_wsp{}; new_wsp.x = x; new_wsp.y = y;
        map[x][y] = '$';
        city->addRoad(new_road);
        my_cities.add(new_wsp);
    }
}

void ReadInput::findNeighbors(City* city)
{
    Road* new_road = new Road{ city , 0 };
    city->addRoad(new_road);

    Queue searchR;
    Vector<Wsp> my_roads;
    Vector<Wsp> my_cities;
    searchR.add(city->getX(), city->getY(), 0);

    while (!searchR.empty())
    {
        Wsp curr = searchR.getWsp();
        int travel_time = searchR.getTime();
        searchR.remove();

        curr.x--;
        checkRoads(curr.x, curr.y, travel_time, &searchR, city, my_cities, my_roads);
        curr.x++;

        curr.x++;
        checkRoads(curr.x, curr.y, travel_time, &searchR, city, my_cities, my_roads);
        curr.x--;

        curr.y--;
        checkRoads(curr.x, curr.y, travel_time, &searchR, city, my_cities, my_roads);
        curr.y++;

        curr.y++;
        checkRoads(curr.x, curr.y, travel_time, &searchR, city, my_cities, my_roads);
        curr.y--; 
    }
    
    for (int i = 0; i < my_roads.getSize(); i++)
    {
        map[my_roads[i].x][my_roads[i].y] = '#';
    }
    for (int i = 0; i < my_cities.getSize(); i++)
    {
        map[my_cities[i].x][my_cities[i].y] = '*';
    }
}

ReadInput::~ReadInput() {
    for (int i = 0; i < sizeX; i++) {
        delete[] map[i];
    }
    delete[] map;
    delete[] vertices;
}