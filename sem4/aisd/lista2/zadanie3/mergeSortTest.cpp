#include <iostream>
#include <random>
#include <fstream>
using namespace std;

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
		comps++;
		for (int i = 2; i < n; i++) {
			comps++;
			if (currentRun.desc != A[i - 1] > A[i]) {
				currentRun.r = i - 1;
				runs.push_back(currentRun);

				currentRun.l = i;
				if (i + 1 < n) {
					currentRun.desc = A[i] > A[i + 1];
					comps++;
				} else {
					currentRun.desc = false;
				}
			}
		}
		currentRun.r = n - 1;
		runs.push_back(currentRun);

		// ordering descending runs
		for (int i = 0; i < runs.size(); i++) {
			if (runs[i].desc) {
				for (int j = 0; j <= (runs[i].r - runs[i].l) / 2; j++) {
					swapInArray(A, runs[i].l + j, runs[i].r - j);
				}
			}
		}

		// looking for runs closest in size and merging until whole array is sorted
		int sizeDiff = 0;
		bool increaseDiff = false;
		while (runs.size() > 1) {
			sizeDiff += (increaseDiff ? 1 : 0);
			increaseDiff = true;
			for (int i = 1; i < runs.size(); i++) {
				if (abs((runs[i - 1].r - runs[i - 1].l) - (runs[i].r - runs[i].l)) <= sizeDiff) {
					if (n < 40) {
						cout << "merging (" << runs[i - 1].l << ", " << runs[i - 1].r << ") and (" << runs[i].l << ", " << runs[i].r << ")" << endl;
					}

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
	random_device rd;
	mt19937 gen(rd());

	ofstream fileM("mergeSortTest.txt");
	ofstream fileO("ownSortTest.txt");

	// liczba testow
	for (int k = 1; k <= 100; k *= 10) {
		cout << "k: " << k << endl;

		for (int n = 100; n <= 5000; n += 100) {
			cout << "\tn: " << n << endl;
			uniform_int_distribution<> dis(0, 2 * n - 1);

			for (int i = 0; i < k; i++) {
				// generowanie tablicy
				int tabM[n], tabO[n];
				for (int j = 0; j < n; j++) {
					tabM[j] = dis(gen);
					tabO[j] = tabM[j];
				}

				comps = 0;
				swaps = 0;
				mergeSort(tabM, n);
				fileM << n << " " << k << " " << comps << " " << swaps << endl;

				comps = 0;
				swaps = 0;
				ownSort(tabO, n);
				fileO << n << " " << k << " " << comps << " " << swaps << endl;
			}
		}
	}

	fileM.close();
	fileO.close();

	cout << "tests saved to files: mergeSortTest.txt, ownSortTest.txt" << endl;

	return 0;
}