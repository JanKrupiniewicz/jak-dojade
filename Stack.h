#pragma once

template<typename T>
class Stack
{
private:
	struct Node {
		Node* next;
		T data;
	};
	Node* stack;

public:
	Stack();
	~Stack();
	bool empty() const;
	T* get();
	void add(const T& data);
	void remove();
};

template<typename T>
Stack<T>::Stack()
{
	stack = nullptr;
}