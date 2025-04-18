#ifndef ARRAY_CPP
#define ARRAY_CPP

#include "Array.h"
#include <iostream>

template<typename T>
void Array::print(T* A, int n) {
	std::cout << "[";
	for (int i = 0; i < n; i++) {
		std::cout << (A[i] < 10 ? "0" : "") << A[i] << (i == n - 1 ? "]\n" : ", ");
	}
}

template<typename T>
void Array::printFragment(T* A, int p, int q) {
	std::cout << "[";
	for (int i = p; i <= q; i++) {
		std::cout << (A[i] < 10 ? "0" : "") << A[i] << (i == q ? "]\n" : ", ");
	}
}

template<typename T>
bool Array::isSorted(T* A, int n) {
	for (int i = 1; i < n; i++) {
		if (A[i - 1] > A[i]) {
			return false;
		}
	}
	return true;
}

#endif