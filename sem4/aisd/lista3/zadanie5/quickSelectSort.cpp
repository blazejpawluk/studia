#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

int n;
int comps;
int swaps;

template<typename T>
bool gt(T a, T b) {
	comps++;
	return a > b;
}

template<typename T>
bool eq(T a, T b) {
	comps++;
	return a == b;
}

template<typename T>
bool le(T a, T b) {
	comps++;
	return a <= b;
}

template<typename T>
void swapInArray(T* A, int a, int b) {
	swaps++;
	swap(A[a], A[b]);
}

template<typename T>
void printTab(T* A, int n) {
	cout << "[";
	if (n > 0) {	
		for (int i = 0; i < n - 1; i++) {
			cout << (A[i] < 10 ? "0" : "") << A[i] << ", ";
		}
		cout << (A[n - 1] < 10 ? "0" : "") << A[n - 1];
	}
	cout << "]" << endl;
}

template<typename T>
void sortFragment(T* A, int l, int r) {
	for (int j = l; j <= r; j++) {
		T key = A[j];
		int i = j - 1;
		while (i >= l && gt(A[i], key)) {
			swapInArray(A, i + 1, i);
			i--;
		}
	}
}

template<typename T>
int find(T* A, int l, int r, T x) {
	for (int i = l ; i <= r; i++) {
		if (eq(A[i], x)) {
			return i;
		}
	}
	return -1;
}

template<typename T>
int myPartition(T* A, int l, int r) {
	T pivot = A[r];
	int i = l - 1;

	for (int j = l; j < r; j++) {
		if (le(A[j], pivot)) {
			i++;
			swapInArray(A, i, j);
		}
	}

	i++;
	swapInArray(A, i, r);
	return i;
}

template<typename T>
T selectRec(T* A, int p, int q, int i) {
	if (p == q) {
		return A[p];
	}

	int size = q - p + 1;

	// if (n <= 30) {
	// 	cout << "> looking for " << i << " order statistic in: ";
	// 	printArray(A, p, q);
	// }
	
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

	// if (n <= 30) {
	// 	cout << "> after sorting 5-element subarrays: ";
	// 	printArray(A, p, q);
	// }

	T x = selectRec(B, 0, N - 1, N / 2);
	int index = find(A, p, q, x);

	swapInArray(A, index, q);
	int r = myPartition(A, p, q);
	int k = r - p + 1;

	// if (n <= 30) {
	// 	cout << "> after myPartition: ";
	// 	printArray(A, p, q);
	// }

	if (i == k) {
		return A[r];
	}
	if (i < k) {
		return selectRec(A, p, r - 1, i);
	}
	return selectRec(A, r + 1, q, i - k);
}

template<typename T>
void quickSortRec(T* A, int l, int r) {
	if (l < r) {
		cout << "Array before partition: ";
		printTab(A + l, r - l + 1);

		T pivot = selectRec(A, l, r, (r - l) / 2 + 1);
		int pivotIndex = find(A, l, r, pivot);
		swapInArray(A, r, pivotIndex);

		pivotIndex = myPartition(A, l, r);

		cout << "Array after partition: ";
		printTab(A + l, r - l + 1);
		cout << "Pivot: " << A[pivotIndex] << endl;

		quickSortRec(A, l, pivotIndex - 1);
		quickSortRec(A, pivotIndex + 1, r);
	}
}

template<typename T>
bool isSorted(T* A, int n) {
	for (int i = 1; i < n; i++) {
		if (A[i] < A[i - 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	cout << "length: ";
	cin >> n;

	int A[n], startingArray[n];
	cout << "array (" << n << " integers, for better display use numbers lower than 99): ";
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		startingArray[i] = A[i];
	}

	
	if(n < 40) {
		cout << endl << "==============================" << endl;
		cout << "starting array: ";
		printTab(A, n);
	}
	
	cout << "==============================" << endl;
	
	cout << "sorting ..." << endl;
	quickSortRec(A, 0, n - 1);
	
	cout << "==============================" << endl;
	
	if(n < 40) {
		cout << "starting array: ";
		printTab(startingArray, n);
		
		cout << "sorted array: ";
		printTab(A, n);
		
		cout << "==============================" << endl;
	}
	
	cout << "array is " << (isSorted(A, n) ? "" : "not ") << "sorted" << endl;
	
	cout << "==============================" << endl;
	
	cout << "comparisons: " << comps << endl;
	cout << "swaps: " << swaps << endl;

	return 0;
}