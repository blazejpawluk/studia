#include <iostream>
using namespace std;

int n;
int comps;
int swaps;

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
void insertSort(T* A, int n) {
	for (int j = 1; j < n; j++) {
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
	insertSort(A, n);
	
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