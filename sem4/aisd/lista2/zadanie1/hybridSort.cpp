#include <iostream>
using namespace std;


int n;
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
void insertSort(T* A, int l, int r) {
	for (int j = l; j <= r; j++) {
		T key = A[j];
		int i = j - 1;
		while (i >= 0 && isGreater(A[i], key)) {
			swapInArray(A, i+1, i);
			i--;
		}

		if (n < 40) {
			cout << "array: ";
			printTab(A, n);
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
int myPartition(T* A, int l, int r) {
	T pivot = A[l];
	int index = l;

	for (int i = l + 1; i <= r; i++) {
		if (isLower(A[i], pivot)) {
			if(i == index + 1) {
				swapInArray(A, i, index);
			} else {
				swapInArray(A, index, index + 1);
				swapInArray(A, index, i);
			}
			index++;
		}
	}

	return index;
}

template<typename T>
void quickSortRec(T* A, int l, int r) {
	if (r - l + 1 > 10) {
		if (n < 40) {
			cout << "pivot: " << A[l];
		}

		// int pivot = hoarePartition(A, l, r);
		int pivot = myPartition(A, l, r);

		if (n < 40) {
			cout << ", array (after partition): ";
			printTab(A + l, r - l + 1);
		}

		// quickSortRec(A, l, pivot);
		quickSortRec(A, l, pivot - 1);
		quickSortRec(A, pivot + 1, r);
	} else {
		insertSort(A, l, r);
	}
}

template<typename T>
void hybridSort(T* A, int n) {
	if (n < 10) {
		insertSort(A, 0, n - 1);
	} else {
		quickSortRec(A, 0, n - 1);
	}
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

	cout << "sorting: " << endl;
	hybridSort(A, n);

	if(n < 40) {
		cout << "starting array: ";
		printTab(startingArray, n);
		
		cout << "  sorted array: ";
		printTab(A, n);
	}

	cout << "comparisons: " << comps << endl;
	cout << "swaps: " << swaps << endl;

	return 0;
}