#pragma once
#define MAX_QUEUE_SIZE 1000


struct Wsp {
    int x;
    int y;
};

class Queue {
private:
    Wsp* wspArr;
    int* timeArr;
    int size;
    int first;
    int last;

public:
    Queue();
    ~Queue();
    bool empty() const;
    bool full() const;
    void add(int x, int y, int travel_time);
    void remove();
    Wsp getWsp() const;
    int getTime() const;

};
