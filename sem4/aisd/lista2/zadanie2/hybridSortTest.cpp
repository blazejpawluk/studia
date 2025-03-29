#include <iostream>
#include <random>
#include <limits.h>
using namespace std;

int comps;
int swaps;
int treshold;

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
void insertSort(T* A, int l, int r) {
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
	if (r - l + 1 > treshold) {
		int pivot = hoarePartition(A, l, r);
		quickSortRec(A, l, pivot);
		quickSortRec(A, pivot + 1, r);
	} else {
		insertSort(A, l, r);
	}
}

template<typename T>
void hybridSort(T* A, int n) {
	if (n < treshold) {
		insertSort(A, 0, n - 1);
	} else {
		quickSortRec(A, 0, n - 1);
	}
}

int main() {
	cout << "hybrid sort test" << endl;

	random_device rd;
	mt19937 gen(rd());
	
	int n = 50000;
	int k = 100;
	uniform_int_distribution<> dis(0, 2 * n - 1);

	double avgC[11], avgS[11];

	for (int t = 5; t <= 15; t++) {
		cout << "treshold: " << t << endl;
		treshold = t;

		for (int i = 0; i < k; i++) {
			int A[n];
			for(int j = 0; j < n; j++) {
				A[j] = dis(gen);
			}

			comps = 0;
			swaps = 0;
			hybridSort(A, n);
			avgC[t - 5] += comps / k;
			avgS[t - 5] += swaps / k;
		}
	}

	int minC = 0, minS = 0;
	for (int i = 0; i < 11; i++) {
		if (avgC[minC] > avgC[i]) {
			minC = i;
		}
		if (avgS[minS] > avgS[i]) {
			minS = i;
		}
		cout << "treshold: " << i + 5 << ", avg comps: " << avgC[i] << ", avg swaps: " << avgS[i] << endl;
	}

	cout << "min comps: " << minC + 5 << endl;
	cout << "min swaps: " << minS + 5 << endl;

	return 0;
}