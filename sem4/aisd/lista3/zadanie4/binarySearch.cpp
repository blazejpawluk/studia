#include <iostream>
using namespace std;

int n;
int comps;

template<typename T>
void printArray(T* A, int l, int r) {
	cout << "[";
	for (int i = l; i < r; i++) {
		cout << (A[i] < 10 ? "0" : "") << A[i] << ", ";
	}
	cout << A[r] << "]" << endl;
}

template<typename T>
bool eq(T a, T b) {
	comps++;
	return a == b;
}

template<typename T>
bool gt(T a, T b) {
	comps++;
	return a > b;
}

template<typename T>
int binSearchRec(T* A, int l, int r, T x) {
	if (l > r) {
		return -1;
	}

	int s = (l + r) / 2;
	if (n <= 30) {
		cout << "> s=" << s << ", A[s]=" << A[s] << endl;
	}
	
	if (eq(A[s], x)) {
		return s;
	}
	if (gt(A[s], x)) {
		return binSearchRec(A, l, s - 1, x);
	}
	return binSearchRec(A, s + 1, r, x);
}

template<typename T>
int binSearch(T* A, int n, T x) {
	return binSearchRec(A, 0, n - 1, x);
}

int main() {
	cout << "Array length: ";
	cin >> n;

	int A[n];
	cout << "Array, " << n << " integers from range [0, " << 2 * n - 1 << "]: ";
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}

	int x;
	cout << "Looking for: ";
	cin >> x;

	cout << "==================================================" << endl;
	if (n <= 30) {
		cout << "Starting array: ";
		printArray(A, 0, n - 1);
	}

	cout << "==================================================" << endl;
	cout << "Looking for " << x << "..." << endl;
	
	int index = binSearch(A, n, x);

	cout << "==================================================" << endl;
	if (n <= 30) {
		cout << "Array: ";
		printArray(A, 0, n - 1);
	}
	cout << "Looking for: " << x << endl;
	if (index == -1) {
		cout << "Value not found in array." << endl;
	} else {
		cout << "Value found on index: " << index << " (A[" << index << "] = " << A[index] << ")" << endl;
	}

	cout << "==================================================" << endl;
	cout << "Comparisons: " << comps << endl;

	return 0;
}