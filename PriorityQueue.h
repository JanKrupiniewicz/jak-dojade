#pragma once
#include "City.h"

class PriorityQueue
{
private:
	struct Node {
		SaveRoad my_road;
		Node* next;
	};
	Node* head;
	Node* tail;
public:
	PriorityQueue();
	~PriorityQueue();
	bool empty() const;
	void add(SaveRoad new_road);
	void remove();
	SaveRoad get() const;

};