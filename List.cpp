#include "List.h"

template<typename T>
List<T>::List()
	: head(nullptr), tail(nullptr) , size(0) {}

template<typename T>
List<T>::~List() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

template<typename T>
void List<T>::add(const T& value) {
	Node* new_node = new Node{value, nullptr};
	if (head == nullptr) {
		head = new_node;
		tail = new_node;
	}
	else {
		tail->next = new_node;
		tail = new_node;
	}
	size++;
}

template<typename T>
void List<T>::remove(const T& value) {
	Node* current = head;
	Node* prev = nullptr;
	while (current != nullptr) {
		if (current->value == value) {
			if (prev == nullptr) {
				head = current->next;
			}
			else {
				prev->next = current->next;
			}
			if (tail == current) {
				tail = prev;
			}
		}
		prev = current;
		current = current->next;
	}
	size--;
}

template<typename T>
T List<T>::get(int index) const {
	Node* current = head;
	int i = 0;
	while (current != nullptr && i < index) {
		current = current->next;
		i++;
	}
	if (current == nullptr) {
		throw "ERR";
	}
	return current->value;
}


template<typename T>
int List<T>::getSize() const {
	return size;
}