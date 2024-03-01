#include "Vector.h"

template<typename T>
Vector<T>::~Vector()
{
	delete[] data;
}

template<typename T>
void Vector<T>::resize(int new_size)
{
	T* new_data = new T[new_size];
	for (int i = 0; i < new_size; i++)
	{
		if (i < size) {
			new_data[i] = data[i];
		}
	}
	delete[] data;
	data = new_data;
	max_size = new_size;
}

template<typename T>
void Vector<T>::add(T new_data)
{
	if (size == max_size)
	{
		resize(max_size * 5);
	}
	data[size++] = new_data;
}

template<typename T>
int Vector<T>::getSize() const
{
	return size;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
	return data[index];
}
