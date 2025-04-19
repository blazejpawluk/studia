#ifndef QUICK_SORT
#define QUICK_SORT

#include "Algorithms.h"
#include "Array.h"
#include <iostream>

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
	if (c.gt(A[l], A[r])) {
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

Array a3;

template<typename T>
void QuickSort::quickSortRec(T* A, int p, int q) {
	if (p < q) {
		if (n < 30) {
			std::cout << "> quick sort on: ";
			a3.printFragment(A, p, q);
		}

		int pivot = partition(A, p, q);

		if (n < 30) {
			std::cout << " > after quick sort partition (pivot: " << A[pivot] << "): ";
			a3.printFragment(A, p, q);
		}

		quickSortRec(A, p, pivot - 1);
		quickSortRec(A, pivot + 1, q);
	}
}

template<typename T>
void QuickSort::quickSelectSortRec(T* A, int p, int q) {
	if (p < q) {
		if (n < 30) {
			std::cout << "> quick select sort on: ";
			a3.printFragment(A, p, q);
		}

		Select s;
		T pivot = s.selectRec(A, p, q, (q - p) / 2 + 1);
		for (int i = p; i <= q; i++) {
			if (c.eq(A[i], pivot)) {
				c.swapInArray(A, i, q);
				break;
			}
		}

		int pivotIndex = partition(A, p, q);

		if (n < 30) {
			std::cout << " > after quick select sort partition (pivot: " << A[pivot] << "): ";
			a3.printFragment(A, p, q);
		}

		quickSelectSortRec(A, p, pivotIndex - 1);
		quickSelectSortRec(A, pivotIndex + 1, q);
	}
}

template<typename T>
void QuickSort::DPQuickSortRec(T* A, int p, int q) {
	if (p < q) {
		if (n < 30) {
			std::cout << "> dual-pivot quick sort on: ";
			a3.printFragment(A, p, q);
		}

		std::pair pivots = DPPartition(A, p, q);

		if (n < 30) {
			std::cout << " > after dual-pivot quick sort partition (pivots: " << A[pivots.first] << ", " << A[pivots.second] << "): ";
			a3.printFragment(A, p, q);
		}

		DPQuickSortRec(A, p, pivots.first - 1);
		DPQuickSortRec(A, pivots.first + 1, pivots.second - 1);
		DPQuickSortRec(A, pivots.second + 1, q);
	}
}

template<typename T>
void QuickSort::DPQuickSelectSortRec(T* A, int p, int q) {
	if (p < q) {
		if (n < 30) {
			std::cout << "> dual-pivot quick select sort on: ";
			a3.printFragment(A, p, q);
		}

		Select s;
		T pivotLeft = s.selectRec(A, p, q, (q - p) / 3 + 1);
		T pivotRight = s.selectRec(A, p, q, 2 * (q - p) / 3 + 1);

		for (int i = p; i <= q; i++) {
			if (c.eq(A[i], pivotLeft)) {
				c.swapInArray(A, p, i);
			} else if (c.eq(A[i], pivotRight)) {
				c.swapInArray(A, i, q);
			}
		}

		std::pair pivots = DPPartition(A, p, q);

		if (n < 30) {
			std::cout << " > after dual-pivot quick select sort partition (pivots: " << A[pivots.first] << ", " << A[pivots.second] << "): ";
			a3.printFragment(A, p, q);
		}

		DPQuickSortRec(A, p, pivots.first - 1);
		DPQuickSortRec(A, pivots.first + 1, pivots.second - 1);
		DPQuickSortRec(A, pivots.second + 1, q);
	}
}

template<typename T>
void QuickSort::quickSort(T* A, int n) {
	c = Count();
	this->n = n;
	quickSortRec(A, 0, n - 1);
}

template<typename T>
void QuickSort::quickSelectSort(T* A, int n) {
	c = Count();
	this->n = n;
	quickSelectSortRec(A, 0, n - 1);
}

template<typename T>
void QuickSort::DPQuickSort(T* A, int n) {
	c = Count();
	this->n = n;
	DPQuickSortRec(A, 0, n - 1);
}

template<typename T>
void QuickSort::DPQuickSelectSort(T* A, int n) {
	c = Count();
	this->n = n;
	DPQuickSelectSortRec(A, 0, n - 1);
}

#endif