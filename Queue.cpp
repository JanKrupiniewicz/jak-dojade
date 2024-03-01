#include "Queue.h"

Queue::Queue() : size(MAX_QUEUE_SIZE), first(0), last(0) {
    wspArr = new Wsp[size];
    timeArr = new int[size];
}

Queue::~Queue() {
    delete[] wspArr;
    delete[] timeArr;
}

bool Queue::empty() const {
    return (first == last);
}

bool Queue::full() const {
    return (last - first == size);
}

void Queue::add(int x, int y, int travel_time) {
    if (!full()) {
        wspArr[last % size].x = x;
        wspArr[last % size].y = y;
        timeArr[last % size] = travel_time;
        last++;
    }
}

void Queue::remove() {
    if (!empty()) {
        first++;
    }
}

int Queue::getTime() const {
    return timeArr[first % size];
}

Wsp Queue::getWsp() const {
    return wspArr[first % size];
}