#include "Stack.h"

template<typename T>
Stack<T>::~Stack()
{
	while (stack != nullptr)
	{
		remove();
	}
}

template<typename T>
bool Stack<T>::empty() const
{
	return stack == nullptr;
}

template<typename T>
T* Stack<T>::get()
{
	if (empty()) {
		return nullptr;
	}
	return &(stack->data);
}

template<typename T>
void Stack<T>::add(const T &data)
{
	Node* new_node = new Node;
	new_node->data = data;
	new_node->next = stack;
	stack = new_node;
}

template<typename T>
void Stack<T>::remove()
{
	if (empty())
	{
		return;
	}
	Node* temp = stack;
	stack = stack->next;
	delete temp;
}