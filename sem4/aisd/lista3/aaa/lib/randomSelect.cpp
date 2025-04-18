#ifndef RANDOM_SELECT
#define RANDOM_SELECT

#include "Algorithms.h"
#include "Count.h"
#include "Array.h"
#include <random>
#include <iostream>

std::random_device rd;
std::mt19937 gen(rd());

Array aRS;

template<typename T>
int RandomSelect::partition(T* A, int p, int q) {
	T pivot = A[q];
	int i = p - 1;

	for (int j = p; j < q; j++) {
		if (c.le(A[j], pivot)) {
			i++;
			c.swapInArray(A, i, j);
		}
	}

	i++;
	c.swapInArray(A, i, q);
	return i;
}

template<typename T>
T RandomSelect::randomSelectRec(T* A, int p, int q, int i) {
	if (p == q) {
		return A[q];
	}

	if (n < 30) {
		std::cout << "-> looking for " << i << " statistic position in: ";
		aRS.printFragment(A, p, q);
	}

	std::uniform_int_distribution<> dis(p, q);
	c.swapInArray(A, dis(gen), q);
	int r = partition(A, p, q);

	if (n < 30) {
		std::cout << "  -> pivot=" << (A[r] < 10 ? "0" : "") << A[r] << ", after partition: ";
		aRS.printFragment(A, p, q);
	}

	int k = r - p + 1;

	if (i == k) {
		return A[r];
	} else if (i < k) {
		return randomSelectRec(A, p, r - 1, i);
	} else {
		return randomSelectRec(A, r + 1, q, i - k);
	}
}

template<typename T>
int RandomSelect::randomSelectIndexRec(T* A, int p, int q, int i) {
	if (p == q) {
		return q;
	}

	if (n < 30) {
		std::cout << "-> looking for " << i << " statistic position in: ";
		aRS.printFragment(A, p, q);
	}

	std::uniform_int_distribution<> dis(p, q);
	c.swapInArray(A, dis(gen), q);
	int r = partition(A, p, q);

	if (n < 30) {
		std::cout << "  -> pivot=" << (A[r] < 10 ? "0" : "") << A[r] << ", after partition: ";
		aRS.printFragment(A, p, q);
	}

	int k = r - p + 1;

	if (i == k) {
		r;
	} else if (i < k) {
		return randomSelectRec(A, p, r - 1, i);
	} else {
		return randomSelectRec(A, r + 1, q, i - k);
	}
}

template<typename T>
T RandomSelect::randomSelect(T* A, int n, int i) {
	c = Count();
	this->n = n;
	return randomSelectRec(A, 0, n - 1, i);
}

template<typename T>
int RandomSelect::randomSelectIndex(T* A, int n, int i) {
	c = Count();
	this->n = n;
	return randomSelectIndexRec(A, 0, n - 1, i);
}

#endif