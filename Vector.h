#pragma once

template<typename T>
class Vector
{
private:
	T* data;
	int size;
	int max_size;

	void resize(int new_size);
public:

	Vector();
	~Vector();
	void add(T new_data);
	int getSize() const;
	T& operator[](int index);
};

template<typename T>
Vector<T>::Vector()
	: size(0), max_size(2)
{
	data = new T[max_size];
};