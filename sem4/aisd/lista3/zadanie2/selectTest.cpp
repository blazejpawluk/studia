#include <iostream>
#include <random>
#include <fstream>
using namespace std;

random_device rd;
mt19937 gen(rd());

int n;
int comps;
int swaps;

template<typename T>
bool le(T a, T b) {
	comps++;
	return a <= b;
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
T randomSelectRec(T* A, int p, int q, int i) {
	if (p == q) {
		return A[q];
	}

	uniform_int_distribution<> dis(p, q);
	swapInArray(A, dis(gen), q);
	int r = partition(A, p, q);
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
	swapInArray(A, index, q);
	int r = partition(A, p, q);
	int k = r - p + 1;

	if (i == k) {
		return A[r];
	}
	if (i < k) {
		return selectRec(A, p, r - 1, i);
	}
	return selectRec(A, r + 1, q, i - k);
}

int main() {
	ofstream fileRS("randomSelectTest.txt");
	ofstream fileS("selectTest.txt");

	for (int n = 100; n <= 50000; n += 100) {
		cout << "n = " << n << endl;

		int k[5] = {1, n / 4, n / 2, 3 * n / 4, n};
		uniform_int_distribution<> dis(0, 2 * n - 1);

		for (int m = 0; m < 50; m++) {
			int A[n];
			for (int i = 0; i < n; i++) {
				A[i] = dis(gen);
			}

			for (int i = 0; i < 5; i++) {
				int B[n];
				for (int j = 0; j < n; j++) {
					B[j] = A[j];
				}
				
				comps = 0;
				swaps = 0;
				randomSelectRec(B, 0, n - 1, k[i]);
				fileRS << n << " " << m << " " << k[i] << " " << comps << " " << swaps << endl;
				
				for (int j = 0; j < n; j++) {
					B[j] = A[j];
				}
				
				comps = 0;
				swaps = 0;
				selectRec(B, 0, n - 1, k[i]);
				fileS << n << " " << m << " " << k[i] << " " << comps << " " << swaps << endl;
			}
		}
	}

	fileRS.close();
	fileS.close();

	cout << "Test results saved in: randomSelectTest.txt, selectTest.txt" << endl;

	return 0;
}