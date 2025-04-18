#ifndef BIN_SEARCH
#define BIN_SERACH

#include "Algorithms.h"

template<typename T>
int BinSearch::binSearchRec(T* A, int p, int q, int v) {
	if (p > q) {
		return -1;
	}

	int s = (p + q) / 2;

	if (c.eq(A[s], v)) {
		return s;
	} else if (c.gt(A[s], v)) {
		return binSearchRec(A, p, s - 1, v);
	} else {
		return binSearchRec(A, s + 1, q, v);
	}
}

template<typename T>
int BinSearch::binSearch(T* A, int n, int v) {
	c = Count();
	return binSearchRec(A, 0, n - 1, v);
}

#endif