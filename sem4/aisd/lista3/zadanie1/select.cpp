#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

int n;
int comps;
int swaps;

template<typename T>
void printArray(T* A, int l, int r) {
	cout << "[";
	for (int i = l; i < r; i++) {
		cout << (A[i] < 10 ? "0" : "") << A[i] << ", ";
	}
	cout << A[r] << "]" << endl;
}

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
int partition(T* A, int l, int r) {
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

	if (n <= 30) {
		cout << "> looking for " << i << " order statistic in: ";
		printArray(A, p, q);
	}
	
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

	if (n <= 30) {
		cout << "> after sorting 5-element subarrays: ";
		printArray(A, p, q);
	}

	T x = selectRec(B, 0, N - 1, N / 2);
	int index = find(A, p, q, x);

	swapInArray(A, index, q);
	int r = partition(A, p, q);
	int k = r - p + 1;

	if (n <= 30) {
		cout << "> after partition: ";
		printArray(A, p, q);
	}

	if (i == k) {
		return A[r];
	}
	if (i < k) {
		return selectRec(A, p, r - 1, i);
	}
	return selectRec(A, r + 1, q, i - k);
}

template<typename T>
T select(T* A, int n, int i) {
	return selectRec(A, 0, n - 1, i);
}

int main() {
	cout << "Array length: ";
	cin >> n;

	int k;
	cout << "Order statistic: ";
	cin >> k;

	int A[n], start[n];
	cout << "Array, " << n << " integers from range [0, " << 2 * n - 1 << "]: ";
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		start[i] = A[i];
	}

	cout << "==================================================" << endl;
	if (n <= 30) {
		cout << "Starting array: ";
		printArray(start, 0, n - 1);
	}

	cout << "==================================================" << endl;
	cout << "Looking for " << k << " order statistic..." << endl;
	
	int x = select(A, n, k);
	
	cout << "==================================================" << endl;
	if (n <= 30) {
		cout << "Starting array: ";
		printArray(start, 0, n - 1);

		cout << "Ending array: ";
		printArray(A, 0, n - 1);

		cout << k << " order statistic: " << x << endl;

		cout << "Sorted array: ";
		sort(A, A + n);
		printArray(A, 0, n - 1);

		cout << "Found value is " << (x == A[k - 1] ? "" : "not ") << "correct." << endl;
	}

	cout << "==================================================" << endl;
	cout << "Comparisons: " << comps << endl;
	cout << "Swaps: " << swaps << endl;

	return 0;
}