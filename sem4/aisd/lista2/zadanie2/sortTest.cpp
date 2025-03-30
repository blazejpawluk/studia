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
void insertSort(T* A, int n) {
	for (int j = 1; j < n; j++) {
		T key = A[j];
		int i = j - 1;
		while (i >= 0 && isGreater(A[i], key)) {
			swapInArray(A, i+1, i);
			i--;
		}
	}
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
void insertHybridSort(T* A, int l, int r) {
	for (int j = l; j <= r; j++) {
		T key = A[j];
		int i = j - 1;
		while (i >= 0 && isGreater(A[i], key)) {
			swapInArray(A, i+1, i);
			i--;
		}
	}
}

template<typename T>
void quickHybridSortRec(T* A, int l, int r) {
	if (r - l + 1 > 10) {
		int pivot = hoarePartition(A, l, r);
		quickHybridSortRec(A, l, pivot);
		quickHybridSortRec(A, pivot + 1, r);
	} else {
		insertHybridSort(A, l, r);
	}
}

template<typename T>
void hybridSort(T* A, int n) {
	if (n < 10) {
		insertHybridSort(A, 0, n - 1);
	} else {
		quickHybridSortRec(A, 0, n - 1);
	}
}

int main() {
	random_device rd;
	mt19937 gen(rd());

	ofstream fileI("insertSortTest.txt");
	ofstream fileQ("quickSortTest.txt");
	ofstream fileH("hybridSortTest.txt");

	// liczba testow
	for (int k = 1; k <= 100; k *= 10) {
		cout << "k: " << k << endl;

		// rozmiary tablicy dla wszystkich algorytmow
		for (int n = 10; n <= 50; n += 10) {
			cout << "\tn: " << n << endl;
			uniform_int_distribution<> dis(0, 2 * n - 1);

			for (int i = 0; i < k; i++) {
				// generowanie tablicy
				int tabI[n], tabQ[n], tabH[n];
				for (int j = 0; j < n; j++) {
					tabI[j] = dis(gen);
					tabQ[j] = tabI[j];
					tabH[j] = tabI[j];
				}

				comps = 0;
				swaps = 0;
				insertSort(tabI, n);
				fileI << n << " " << k << " " << comps << " " << swaps << endl;

				comps = 0;
				swaps = 0;
				quickSort(tabQ, n);
				fileQ << n << " " << k << " " << comps << " " << swaps << endl;

				comps = 0;
				swaps = 0;
				hybridSort(tabH, n);
				fileH << n << " " << k << " " << comps << " " << swaps << endl;
			}
		}

		// rozmiary dla wszystkich algorytmów poza insert sortem
		for (int n = 1000; n <= 50000; n += 1000) {
			cout << "\tn: " << n << endl;
			uniform_int_distribution<> dis(0, 2 * n - 1);

			for (int i = 0; i < k; i++) {
				// generowanie tablicy
				int tabQ[n], tabH[n];
				for (int j = 0; j < n; j++) {
					tabQ[j] = dis(gen);
					tabH[j] = tabQ[j];
				}

				comps = 0;
				swaps = 0;
				quickSort(tabQ, n);
				fileQ << n << " " << k << " " << comps << " " << swaps << endl;

				comps = 0;
				swaps = 0;
				hybridSort(tabH, n);
				fileH << n << " " << k << " " << comps << " " << swaps << endl;
			}
		}
	}

	fileI.close();
	fileQ.close();
	fileH.close();

	cout << "tests saved to files: insertSortTest.txt, quickSortTest.txt, hybridSortTest.txt" << endl;

	return 0;
}