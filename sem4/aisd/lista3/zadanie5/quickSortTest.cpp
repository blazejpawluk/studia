#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

random_device rd;
mt19937 gen(rd());

int comps;
int swaps;

template<typename T>
bool lt(T a, T b) {
	comps++;
	return a < b;
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
int myPartition(T* A, int l, int r) {
	T pivot = A[r];
	int i = l - 1;

	for (int j = l; j < r; j++) {
		if (le(A[j], pivot)) {
			i++;
			swap(A[i], A[j]);
		}
	}

	i++;
	swap(A[i], A[r]);
	return i;
}

template<typename T>
void quickSortRec(T* A, int l, int r) {
	if (l < r) {
		int pivot = myPartition(A, l, r);

		quickSortRec(A, l, pivot - 1);
		quickSortRec(A, pivot + 1, r);
	}
}

template<typename T>
void quickSort(T* A, int n) {
	quickSortRec(A, 0, n - 1);
}

template<typename T> 
pair<int, int> DPPartition(T* A, int l, int r) {
	if (A[l] > A[r]) {
		swap(A[l], A[r]);
	}

	T p = A[l], q = A[r];
	int pIndex = l, qIndex = r;
	int S = 0, L = 0;

	int i = l + 1;
	while (i != qIndex) {
		if (S >= L) {
			if (lt(A[i], p)) {
				if (i == pIndex + 1) {
					swap(A[i], A[pIndex]);
				} else {
					swap(A[pIndex], A[pIndex + 1]);
					swap(A[i], A[pIndex]);
				}
				pIndex++;
				i++;
				S++;
			} else if (gt(A[i], q)) {
				if (i == qIndex - 1) {
					swap(A[i], A[qIndex]);
				} else {
					swap(A[qIndex], A[qIndex - 1]);
					swap(A[i], A[qIndex]);
				}
				qIndex--;
				L++;
			} else {
				i++;
			}
		} else {
			if (gt(A[i], q)) {
				if (i == qIndex - 1) {
					swap(A[i], A[qIndex]);
				} else {
					swap(A[qIndex], A[qIndex - 1]);
					swap(A[i], A[qIndex]);
				}
				qIndex--;
				L++;
			} else if (lt(A[i], p)) {
				if (i == pIndex + 1) {
					swap(A[i], A[pIndex]);
				} else {
					swap(A[pIndex], A[pIndex + 1]);
					swap(A[i], A[pIndex]);
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
void DPQuickSortRec(T* A, int l, int r) {
	if (l < r) {
		pair<int, int> pivots = DPPartition(A, l, r);

		DPQuickSortRec(A, l, pivots.first - 1);
		DPQuickSortRec(A, pivots.first + 1, pivots.second - 1);
		DPQuickSortRec(A, pivots.second + 1, r);
	}
}

template<typename T>
void DPQuickSort(T* A, int n) {
	DPQuickSortRec(A, 0, n - 1);
}

template<typename T>
void sortFragment(T* A, int l, int r) {
	for (int j = l; j <= r; j++) {
		T key = A[j];
		int i = j - 1;
		while (i >= l && gt(A[i], key)) {
			swap(A[i + 1], A[i]);
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
T selectRec(T* A, int p, int q, int i) {
	if (p == q) {
		return A[p];
	}

	int size = q - p + 1;
	
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

	T x = selectRec(B, 0, N - 1, N / 2);
	int index = find(A, p, q, x);

	swap(A[index], A[q]);
	int r = myPartition(A, p, q);
	int k = r - p + 1;

	if (i == k) {
		return A[r];
	}
	if (i < k) {
		return selectRec(A, p, r - 1, i);
	}
	return selectRec(A, r + 1, q, i - k);
}

template<typename T>
void quickSelectSortRec(T* A, int l, int r) {
	if (l < r) {
		T pivot = selectRec(A, l, r, (r - l) / 2 + 1);
		int pivotIndex = find(A, l, r, pivot);
		swap(A[r], A[pivotIndex]);

		pivotIndex = myPartition(A, l, r);

		quickSelectSortRec(A, l, pivotIndex - 1);
		quickSelectSortRec(A, pivotIndex + 1, r);
	}
}

template<typename T>
void quickSelectSort(T* A, int n) {
	quickSelectSortRec(A, 0, n - 1);
}

template<typename T>
void DPQuickSelectSortRec(T* A, int l, int r) {
	if (l < r) {
		T leftPivot = selectRec(A, l, r, (r - l) / 3 + 1);
		T rightPivot = selectRec(A, l, r, (2 * (r - l) / 3) + 1);
		
		swap(A[find(A, l, r, leftPivot)], A[l]);
		swap(A[find(A, l, r, rightPivot)], A[r]);
		
		pair<int, int> pivots = DPPartition(A, l, r);

		DPQuickSelectSortRec(A, l, pivots.first - 1);
		DPQuickSelectSortRec(A, pivots.first + 1, pivots.second - 1);
		DPQuickSelectSortRec(A, pivots.second + 1, r);
	}
}

template<typename T>
void DPQuickSelectSort(T* A, int n) {
	DPQuickSelectSortRec(A, 0, n - 1);
}

int main() {
	ofstream fileQS("qsTest.txt");
	ofstream fileDPQS("dpqsTest.txt");
	ofstream fileQSS("qssTest.txt");
	ofstream fileDPQSS("dpqssTest.txt");

	int k = 50;
	for (int n = 100; n <= 10000; n += 100) {
		cout << n << endl;

		for (int m = 0; m < k; m++) {
			uniform_int_distribution<> dis(0, 2 * n - 1);
			int qs[n], dpqs[n], qss[n], dpqss[n];
			for (int i = 0; i < n; i++) {
				qs[i] = dis(gen);
				dpqs[i] = qs[i];
				qss[i] = qs[i];
				dpqss[i] = qs[i];
			}

			comps = 0;
			auto startTime = high_resolution_clock::now();
			quickSort(qs, n);
			auto endTime = high_resolution_clock::now();
			auto elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			fileQS << n << " " << m << " " << comps << " " << elapsed << endl;
			
			comps = 0;
			startTime = high_resolution_clock::now();
			DPQuickSort(dpqs, n);
			endTime = high_resolution_clock::now();
			elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			fileDPQS << n << " " << m << " " << comps << " " << elapsed << endl;

			comps = 0;
			startTime = high_resolution_clock::now();
			quickSelectSort(dpqs, n);
			endTime = high_resolution_clock::now();
			elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			fileQSS << n << " " << m << " " << comps << " " << elapsed << endl;

			comps = 0;
			startTime = high_resolution_clock::now();
			DPQuickSelectSort(dpqs, n);
			endTime = high_resolution_clock::now();
			elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			fileDPQSS << n << " " << m << " " << comps << " " << elapsed << endl;
		}
	}

	fileQS.close();
	fileDPQS.close();
	fileQSS.close();
	fileDPQSS.close();

	return 0;
}