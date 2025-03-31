#include <iostream>
#include <random>
#include <fstream>
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
int hoarePartition(T* A, int l, int r) {
	T pivot = A[l];
	int i = l - 1;
	int j = r + 1;
	while (true) {
		do {i++;} while (isLower(A[i], pivot));
		do {j--;} while (isGreater(A[j], pivot));

		if(i >= j) return j;
		swapInArray(A, i, j);
	}
}

template<typename T>
void quickSortRec(T* A, int l, int r) {
	if (l < r) {
		int pivot = hoarePartition(A, l, r);

		quickSortRec(A, l, pivot);
		quickSortRec(A, pivot + 1, r);
	}
}

template<typename T>
void quickSort(T* A, int n) {
	quickSortRec(A, 0, n - 1);
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

	ofstream fileQ("quickSortTest.txt");
	ofstream fileDPQ("DPQuickSortTest.txt");

	// liczba testow
	for (int k = 1; k <= 100; k *= 10) {
		cout << "k: " << k << endl;

		for (int n = 1000; n <= 50000; n += 1000) {
			cout << "\tn: " << n << endl;
			uniform_int_distribution<> dis(0, 2 * n - 1);

			for (int i = 0; i < k; i++) {
				// generowanie tablicy
				int tabQ[n], tabDPQ[n];
				for (int j = 0; j < n; j++) {
					tabQ[j] = dis(gen);
					tabDPQ[j] = tabQ[j];
				}

				comps = 0;
				swaps = 0;
				quickSort(tabQ, n);
				fileQ << n << " " << k << " " << comps << " " << swaps << endl;

				comps = 0;
				swaps = 0;
				DPQuickSort(tabDPQ, n);
				fileDPQ << n << " " << k << " " << comps << " " << swaps << endl;
			}
		}
	}

	fileQ.close();
	fileDPQ.close();

	cout << "tests saved to files: quickSortTest.txt, DPQuickSortTest.txt" << endl;

	return 0;
}