#include <iostream>
#include <cmath>
#include <random>
using namespace std;

int comps;
int swaps;

template<typename T>
bool isLower(T x, T y) {
	comps++;
	return x < y;
}

template<typename T>
bool isGreater(T x, T y) {
	comps++;
	return x > y;
}

template<typename T>
void swapInArray(T* A, int i, int j) {
	swaps++;
	swap(A[i], A[j]);
}

template<typename T> 
pair<int, int> DPPartition(T* A, int l, int r) {
	if (A[l] > A[r]) {
		swapInArray(A, l, r);
	}

	T p = A[l], q = A[r];
	int pIndex = l, qIndex = r;
	int S = 0, L = 0;

	int i = l + 1;
	while (i != qIndex) {
		if (S >= L) {
			if (isLower(A[i], p)) {
				if (i == pIndex + 1) {
					swapInArray(A, i, pIndex);
				} else {
					swapInArray(A, pIndex, pIndex + 1);
					swapInArray(A, i, pIndex);
				}
				pIndex++;
				i++;
				S++;
			} else if (isGreater(A[i], q)) {
				if (i == qIndex - 1) {
					swapInArray(A, i, qIndex);
				} else {
					swapInArray(A, qIndex, qIndex - 1);
					swapInArray(A, i, qIndex);
				}
				qIndex--;
				L++;
			} else {
				i++;
			}
		} else {
			if (isGreater(A[i], q)) {
				if (i == qIndex - 1) {
					swapInArray(A, i, qIndex);
				} else {
					swapInArray(A, qIndex, qIndex - 1);
					swapInArray(A, i, qIndex);
				}
				qIndex--;
				L++;
			} else if (isLower(A[i], p)) {
				if (i == pIndex + 1) {
					swapInArray(A, i, pIndex);
				} else {
					swapInArray(A, pIndex, pIndex + 1);
					swapInArray(A, i, pIndex);
				}
				pIndex++;
				i++;
				S++;
			} else {
				i++;
			}
		}
	}

	pair<int, int> result;
	result.first = pIndex;
	result.second = qIndex;
	return result;
}

template<typename T>
void DPQuickSortRec(T* A, int l, int r) {
	if (l < r) {
		pair<int, int> pivots = DPPartition(A, l, r);

		DPQuickSortRec(A, l, pivots.first - 1);
		DPQuickSortRec(A, pivots.first + 1, pivots.second - 1);
		DPQuickSortRec(A, pivots.second + 1, r);
	}
}

template<typename T>
void DPQuickSort(T* A, int n) {
	DPQuickSortRec(A, 0, n - 1);
}

int main() {
	random_device rd;
	mt19937 gen(rd());

	int k = 100;
	double c = 0;

	for (int n = 100; n <= 5000; n += 100) {
		cout << n << endl;
		double nlogn = n * log(n);
		uniform_int_distribution<> dis(0, 2 * n - 1);

		for (int i = 0; i < k; i++) {
			int tab[n];
			for (int j = 0; j < n; j++) {
				tab[i] = dis(gen);
			}

			comps = 0;
			swaps = 0;
			DPQuickSort(tab, n);

			c += 1.0 * comps / 50 / k / nlogn;
		}
	}

	cout << "constant: " << c << endl;
}