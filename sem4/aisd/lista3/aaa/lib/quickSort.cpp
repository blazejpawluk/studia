#ifndef QUICK_SORT
#define QUICK_SORT

#include "Algorithms.h"

template<typename T>
int QuickSort::partition(T* A, int p, int q) {
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
std::pair<int, int> QuickSort::DPPartition(T* A, int l, int r) {
	if (A[l] > A[r]) {
		c.swapInArray(A, l, r);
	}

	T p = A[l], q = A[r];
	int pIndex = l, qIndex = r;
	int S = 0, L = 0;

	int i = l + 1;
	while (i != qIndex) {
		if (S >= L) {
			if (c.lt(A[i], p)) {
				if (i == pIndex + 1) {
					c.swapInArray(A, i, pIndex);
				} else {
					c.swapInArray(A, pIndex, pIndex + 1);
					c.swapInArray(A, i, pIndex);
				}
				pIndex++;
				i++;
				S++;
			} else if (c.gt(A[i], q)) {
				if (i == qIndex - 1) {
					c.swapInArray(A, i, qIndex);
				} else {
					c.swapInArray(A, qIndex, qIndex - 1);
					c.swapInArray(A, i, qIndex);
				}
				qIndex--;
				L++;
			} else {
				i++;
			}
		} else {
			if (c.gt(A[i], q)) {
				if (i == qIndex - 1) {
					c.swapInArray(A, i, qIndex);
				} else {
					c.swapInArray(A, qIndex, qIndex - 1);
					c.swapInArray(A, i, qIndex);
				}
				qIndex--;
				L++;
			} else if (c.lt(A[i], p)) {
				if (i == pIndex + 1) {
					c.swapInArray(A, i, pIndex);
				} else {
					c.swapInArray(A, pIndex, pIndex + 1);
					c.swapInArray(A, i, pIndex);
				}
				pIndex++;
				i++;
				S++;
			} else {
				i++;
			}
		}
	}

	std::pair<int, int> result;
	result.first = pIndex;
	result.second = qIndex;
	return result;
}

template<typename T>
void QuickSort::quickSortRec(T* A, int p, int q) {
	if (p < q) {
		int pivot = partition(A, p, q);
		quickSortRec(A, p, pivot - 1);
		quickSortRec(A, pivot + 1, q);
	}
}

template<typename T>
void QuickSort::quickSelectSortRec(T* A, int p, int q) {
	if (p < q) {
		Select s;
		int pivot = s.selectIndexRec(A, p, q, (q - p) / 2 + 1);
		c.swapInArray(A, pivot, q);
		pivot = partition(A, p, q);
		quickSelectSortRec(A, p, pivot - 1);
		quickSelectSortRec(A, pivot + 1, q);
	}
}

template<typename T>
void QuickSort::DPQuickSortRec(T* A, int p, int q) {
	if (p < q) {
		std::pair pivots = DPPartition(A, p, q);
		DPQuickSortRec(A, p, pivots.first - 1);
		DPQuickSortRec(A, pivots.first + 1, pivots.second - 1);
		DPQuickSortRec(A, pivots.second + 1, q);
	}
}

template<typename T>
void QuickSort::DPQuickSelectSortRec(T* A, int p, int q) {
	if (p < q) {
		Select s;
		c.swapInArray(A, p, s.selectIndexRec(A, p, q, (q - p) / 3 + 1));
		c.swapInArray(A, s.selectIndexRec(A, p + 1, q, 2 * (q - p) / 3), q);
		std::pair pivots = DPPartition(A, p, q);
		DPQuickSortRec(A, p, pivots.first - 1);
		DPQuickSortRec(A, pivots.first + 1, pivots.second - 1);
		DPQuickSortRec(A, pivots.second + 1, q);
	}
}

template<typename T>
void QuickSort::quickSort(T* A, int n) {
	c = Count();
	quickSortRec(A, 0, n - 1);
}

template<typename T>
void QuickSort::quickSelectSort(T* A, int n) {
	c = Count();
	quickSelectSortRec(A, 0, n - 1);
}

template<typename T>
void QuickSort::DPQuickSort(T* A, int n) {
	c = Count();
	DPQuickSortRec(A, 0, n - 1);
}

template<typename T>
void QuickSort::DPQuickSelectSort(T* A, int n) {
	c = Count();
	DPQuickSelectSortRec(A, 0, n - 1);
}

#endif