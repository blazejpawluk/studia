#ifndef COUNT_CPP
#define COUNT_CPP

#include "Count.h"
#include <iostream>
#include <algorithm>

Count::Count() {
	comps = 0;
	swaps = 0;
}

template<typename T>
void Count::swapInArray(T* A, int i, int j) {
	swaps++;
	std::swap(A[i], A[j]);
}

template<typename T>
bool Count::lt(T a, T b) {
	comps++;
	return a < b;
}

template<typename T>
bool Count::le(T a, T b) {
	comps++;
	return a <= b;
}

template<typename T>
bool Count::eq(T a, T b) {
	comps++;
	return a == b;
}

template<typename T>
bool Count::ge(T a, T b) {
	comps++;
	return a >= b;
}

template<typename T>
bool Count::gt(T a, T b) {
	comps++;
	return a > b;
}

int Count::getComps() {
	return comps;
}

int Count::getSwaps() {
	return swaps;
}

#endif