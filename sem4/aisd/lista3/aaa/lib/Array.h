#ifndef ARRAY_H
#define ARRAY_H

class Array {
public:
	template<typename T>
	void print(T* A, int n);

	template<typename T>
	void printFragment(T* A, int p, int q);

	template<typename T>
	bool isSorted(T* A, int n);
};

#include "Array.cpp"

#endif