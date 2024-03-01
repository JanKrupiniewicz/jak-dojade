#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() : head(nullptr), tail(nullptr) {}

PriorityQueue::~PriorityQueue()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

bool PriorityQueue::empty() const
{
    return (head == nullptr);
}

void PriorityQueue::add(SaveRoad new_road)
{
    Node* new_node = new Node;
    new_node->my_road = new_road;
    new_node->next = nullptr;

    if (head == nullptr)
    {
        head = tail = new_node;
    }
    else if (head->my_road.travel_time >= new_road.travel_time)
    {
        new_node->next = head;
        head = new_node;
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr && current->next->my_road.travel_time < new_road.travel_time)
        {
            current = current->next;
        }
        if (current->next == nullptr)
        {
            if (tail->my_road.travel_time > new_road.travel_time)
            {
                current->next = tail;
                new_node->next = current->next;
                new_node = current;
            }
            else
            {
                new_node->next = current->next;
                current->next = new_node;
                tail = new_node;
            }
        }
        else
        {
            new_node->next = current->next;
            current->next = new_node;
        }
    }
}

void PriorityQueue::remove()
{
    if (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr)
        {
            tail = nullptr;
        }
    }
}

SaveRoad PriorityQueue::get() const
{
    return (head != nullptr) ? head->my_road : throw "ERR";
}
