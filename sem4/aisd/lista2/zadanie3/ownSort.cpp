#include <iostream>
#include <vector>
#include <cmath>
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

struct run {
    int l;
    int r;
    bool desc;
};

template<typename T>
void ownSort(T* A, int n) {
	if (n > 1) {
		vector<run> runs;
	
		// detecting runs
		run currentRun;
		currentRun.l = 0;
		currentRun.desc = A[0] > A[1];
		for (int i = 2; i < n; i++) {
			if (currentRun.desc != A[i - 1] > A[i]) {
				currentRun.r = i - 1;
				runs.push_back(currentRun);

				currentRun.l = i;
				if (i + 1 < n) {
					currentRun.desc = A[i] > A[i + 1];
				} else {
					currentRun.desc = false;
				}
			}
		}
		currentRun.r = n - 1;
		runs.push_back(currentRun);

		// ordering descernding runs
		for (int i = 0; i < runs.size(); i++) {
			if (runs[i].desc) {
				for (int j = 0; j <= (runs[i].r - runs[i].l) / 2; j++) {
					swapInArray(A, runs[i].l + j, runs[i].r - j);
				}
			}
		}

		int sizeDiff = 0;
		bool increaseDiff = false;
		while (runs.size() > 1) {
			sizeDiff += (increaseDiff ? 1 : 0);
			increaseDiff = true;
			for (int i = 1; i < runs.size(); i++) {
				if (abs((runs[i - 1].r - runs[i - 1].l) - (runs[i].r - runs[i].l)) <= sizeDiff) {
					cout << "merging (" << runs[i - 1].l << ", " << runs[i - 1].r << ") and (" << runs[i].l << ", " << runs[i].r << ")" << endl;
					merge(A, runs[i - 1].l, runs[i - 1].r, runs[i].r);
					runs[i - 1].r = runs[i].r;
					runs.erase(runs.begin() + i);
					increaseDiff = false;
					break;
				}
			}
		}
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

	cout << "sorting..." << endl;
	ownSort(A, n);

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