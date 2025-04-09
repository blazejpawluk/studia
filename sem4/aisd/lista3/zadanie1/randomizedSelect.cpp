#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

random_device rd;
mt19937 gen(rd());

int n;
int comps;
int swaps;

template<typename T>
void printArray(T* A, int l, int r) {
	cout << "[";
	for (int i = l; i < r; i++) {
		cout << A[i] << ", ";
	}
	cout << A[r] << "]" << endl;
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
int randPartition(T* A, int l, int r) {
	uniform_int_distribution<> dis(l, r);
	swapInArray(A, dis(gen), r);
	return partition(A, l, r);
}

template<typename T>
T randomSelectRec(T* A, int p, int q, int i) {
	if (p == q) {
		return A[q];
	}

	if (n <= 30) {
		cout << "> looking for " << i << " order statistic in: ";
		printArray(A, p, q);
	}

	int r = randPartition(A, p, q);
	int k = r - p + 1;

	if (i == k) {
		return A[r];
	}
	if (i < k) {
		return randomSelectRec(A, p, r - 1, i);
	}
	return randomSelectRec(A, r + 1, q, i - k);
}

template<typename T>
T randomSelect(T* A, int n, int i) {
	return randomSelectRec(A, 0, n - 1, i);
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
	
	int x = randomSelect(A, n, k);
	
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