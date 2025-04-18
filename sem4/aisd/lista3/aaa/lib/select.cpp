#ifndef SELECT
#define SELECT

#include "Algorithms.h"
#include "Array.h"
#include <iostream>

Array aS;

template<typename T>
int Select::partition(T* A, int p, int q) {
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
void Select::sortFragment(T* A, int p, int q) {
	for (int j = p; j <= q; j++) {
		T key = A[j];
		int i = j - 1;
		while (i >= p && c.gt(A[i], key)) {
			c.swapInArray(A, i + 1, i);
			i--;
		}
	}
}

template<typename T>
T Select::selectRec(T* A, int p, int q, int i) {
	if (p == q) {
		return A[p];
	}

	if (n < 30) {
		std::cout << "-> looking for " << i << " statistic position in: ";
		aS.printFragment(A, p, q);
	}

	int size = q - p + 1;
	
	int N = size / 5 + (size % 5 == 0 ? 0 : 1);
	T B[N];

	for (int i = 0; i < size / 5; i++) {
		sortFragment(A, p + i * 5,  p + i * 5 + 4);
		B[i] = A[p + i * 5 + 2];
	}
	
	if (size % 5 != 0) {
		sortFragment(A, p + (size / 5) * 5, q);
		B[size / 5] = A[(p + (size / 5) * 5 + q) / 2];
	}

	if (n < 30) {
		std::cout << "  -> after sorting 5-element fragments: ";
		aS.printFragment(A, p, q);
	}

	T pivot = selectRec(B, 0, N - 1, N / 2);
	int index;
	for (int i = p; i <= q; i++) {
		if (c.eq(A[i], pivot)) {
			index = i;
			break;
		}
	}
	c.swapInArray(A, index, q);

	int r = partition(A, p, q);

	if (n < 30) {
		std::cout << "  -> pivot=" << (A[r] < 10 ? "0" : "") << A[r] << ", after partition: ";
		aS.printFragment(A, p, q);
	}

	int k = r - p + 1;

	if (i == k) {
		return A[r];
	} else if (i < k) {
		return selectRec(A, p, r - 1, i);
	} else {
		return selectRec(A, r + 1, q, i - k);
	}
}

template<typename T>
int Select::selectIndexRec(T* A, int p, int q, int i) {
	if (p == q) {
		return p;
	}

	if (n < 30) {
		std::cout << "-> looking for " << i << " statistic position in: ";
		aS.printFragment(A, p, q);
	}

	int size = q - p + 1;
	
	int N = size / 5 + (size % 5 == 0 ? 0 : 1);
	T B[N];

	for (int i = 0; i < size / 5; i++) {
		sortFragment(A, p + i * 5,  p + i * 5 + 4);
		B[i] = A[p + i * 5 + 2];
	}
	
	if (size % 5 != 0) {
		sortFragment(A, p + (size / 5) * 5, q);
		B[size / 5] = A[(p + (size / 5) * 5 + q) / 2];
	}

	if (n < 30) {
		std::cout << "  -> after sorting 5-element fragments: ";
		aS.printFragment(A, p, q);
	}

	T pivot = B[selectIndexRec(B, 0, N - 1, N / 2)];
	int index;
	for (int i = p; i <= q; i++) {
		if (c.eq(A[i], pivot)) {
			index = i;
			break;
		}
	}
	c.swapInArray(A, index, q);

	int r = partition(A, p, q);

	if (n < 30) {
		std::cout << "  -> pivot=" << (A[r] < 10 ? "0" : "") << A[r] << ", after partition: ";
		aS.printFragment(A, p, q);
	}

	int k = r - p + 1;

	if (i == k) {
		return r;
	}
	if (i < k) {
		return selectRec(A, p, r - 1, i);
	}
	return selectRec(A, r + 1, q, i - k);
}

template<typename T>
T Select::select(T* A, int n, int i) {
	c = Count();
	this->n = n;
	return selectRec(A, 0, n - 1, i);
}

template<typename T>
int Select::selectIndex(T* A, int n, int i) {
	c = Count();
	this->n = n;
	return selectIndexRec(A, 0, n - 1, i);
}

#endif