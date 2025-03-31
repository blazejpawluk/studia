#include <iostream>
using namespace std;

int n;
int comps;
int swaps;

template<typename T>
bool isSmallerOrEqual(T x, T y) {
	comps++;
	return x <= y;
}

template<typename T>
void setValue(T* A, int index, T value) {
	swaps++;
	A[index] = value;
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
bool isSorted(T* A, int n) {
	for (int i = 1; i < n; i++) {
		if (A[i] < A[i - 1]) {
			return false;
		}
	}
	return true;
}

template<typename T> 
void merge(T* A, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	T L[n1], R[n2];
	for (int i = 0; i < n1; i++) {
		L[i] = A[l + i];
	}
	for (int i = 0; i < n2; i++) {
		R[i] = A[m + 1 + i];
	}

	int i = 0, j = 0;
	int k = l;

	while (i < n1 && j < n2) {
		if (isSmallerOrEqual(L[i],R[j])) {
			setValue(A, k, L[i]);
			i++;
		} else {
			setValue(A, k, R[j]);
			j++;
		}
		k++;
	}

	while (i < n1) {
		setValue(A, k, L[i]);
		i++;
		k++;
	}

	while (j < n2) {
		setValue(A, k, R[j]);
		j++;
		k++;
	}
}

template<typename T>
void mergeSortRec(T* A, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSortRec(A, l, m);
		mergeSortRec(A, m + 1, r);
		merge(A, l, m, r);
	}
}

template<typename T>
void mergeSort(T* A, int n) {
	mergeSortRec(A, 0, n - 1);
}

int main() {
	cout << "length: ";
	cin >> n;

	int A[n], startingArray[n];
	cout << "array (" << n << " integers, for better display max. 99): ";
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		startingArray[i] = A[i];
	}

	if(n < 40) {
		cout << "starting array: ";
		printTab(A, n);
	}

	cout << "sorting..." << endl;
	mergeSort(A, n);

	if(n < 40) {
		cout << "starting array: ";
		printTab(startingArray, n);
		
		cout << "sorted array: ";
		printTab(A, n);
	}

	cout << "array is " << (isSorted(A, n) ? "" : "not ") << "sorted" << endl;

	cout << "comparisons: " << comps << endl;
	cout << "swaps: " << swaps << endl;

	return 0;
}