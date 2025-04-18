#ifndef BIN_SEARCH
#define BIN_SERACH

#include "Algorithms.h"

template<typename T>
int BinSearch::binSearchRec(T* A, int p, int q, int x) {
	if (p > q) {
		return -1;
	}

	int s = (p + q) / 2;

	if (c.eq(A[s], x)) {
		return s;
	} else if (c.gt(A[s], x)) {
		return binSearchRec(A, p, s - 1, x);
	} else {
		return binSearchRec(A, s + 1, q, x);
	}
}

template<typename T>
int BinSearch::binSearch(T* A, int n, int x) {
	c = Count();
	return binSearchRec(A, 0, n - 1);
}

#endif