#pragma once

template<typename T>
class List;

template<typename T>
class ListIterator {
private:
	typename List<T>::Node* current;
public:
	ListIterator(typename List<T>::Node* node) 
		:current(node) {}

	ListIterator<T>& operator++() {
		current = current->next;
		return *this;
	}

	bool operator!=(const ListIterator<T>& other) const {
		return (current == other.current) ? 0 : 1;
	}

	T& operator*() const {
		return current->value;
	}
};

template<typename T>
class List
{
public:
	struct Node {
		T value;
		Node* next;
	};

	List();
	~List();
	void add(const T& value);
	void remove(const T& value);
	int getSize() const;
	T get(int index) const;

	typedef ListIterator<T> iterator;
	iterator begin() {
		return iterator(head);
	}
	iterator end() {
		return iterator(nullptr);
	}

private:
	Node* head;
	Node* tail;
	int size;
};

