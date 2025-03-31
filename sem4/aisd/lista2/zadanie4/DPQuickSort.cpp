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
pair<int, int> partition(T* A, int l, int r) {
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
void quickSortRec(T* A, int l, int r) {
	if (l < r) {
		pair<int, int> pivots = partition(A, l, r);
		
		if (n < 40) {
			cout << "p: " << A[pivots.first] << ", q: " << A[pivots.second] << ", array (after partition): ";
			printTab(A + l, r - l + 1);
		}

		quickSortRec(A, l, pivots.first - 1);
		quickSortRec(A, pivots.first + 1, pivots.second - 1);
		quickSortRec(A, pivots.second + 1, r);
	}
}

template<typename T>
void quickSort(T* A, int n) {
	quickSortRec(A, 0, n - 1);
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
	quickSort(A, n);

	if(n < 40) {
		cout << "starting array: ";
		printTab(startingArray, n);
		
		cout << "  sorted array: ";
		printTab(A, n);
	}
	
	cout << "array is " << (isSorted(A, n) ? "" : "not ") << "sorted" << endl;

	cout << "comparisons: " << comps << endl;
	cout << "swaps: " << swaps << endl;

	return 0;
}