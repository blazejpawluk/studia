#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;

int comps;

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
	
	if (eq(A[s], x)) {
		return s;
	}
	if (gt(A[s], x)) {
		return binSearchRec(A, l, s - 1, x);
	}
	return binSearchRec(A, s + 1, r, x);
}

int main() {
	random_device rd;
	mt19937 gen(rd());

	ofstream file("binSearchTest.txt");
	file << "label n m comparisons time compsConst timeConst" << endl;

	for (int n = 1000; n <= 100000; n += 1000) {
		cout << "n=" << n << endl;
		
		double logn = log2(n);
		
		uniform_int_distribution<> dis(0, 2 * n - 1);
		uniform_int_distribution<> disRan(0, 2 * n - 1);
		uniform_int_distribution<> disBeg(0, n / 3);
		uniform_int_distribution<> disMid(n / 3, 2 * n / 3);
		uniform_int_distribution<> disEnd(2 * n / 3, n - 1);
		uniform_int_distribution<> disNot(0, 2 * n - 1);
		uniform_int_distribution<> disInA(0, n - 1);

		for (int m = 0; m < 1000; m++) {
			int A[n];
			for (int i = 0; i < n; i++) {
				A[i] = dis(gen);
			}
			sort(A, A + n);
			
			int ran = disRan(gen);
			comps = 0;
			auto startTime = high_resolution_clock::now();
			binSearchRec(A, 0, n - 1, ran);
			auto endTime = high_resolution_clock::now();
			auto elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			file << "ran " << n << " " << m << " " << comps << " " << elapsed << " " << (comps / logn) << " " << (elapsed / logn) << endl;
			
			int beg = A[disBeg(gen)];
			comps = 0;
			startTime = high_resolution_clock::now();
			binSearchRec(A, 0, n - 1, beg);
			endTime = high_resolution_clock::now();
			elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			file << "beg " << n << " " << m << " " << comps << " " << elapsed << " " << (comps / logn) << " " << (elapsed / logn) << endl;
			
			int mid = A[disMid(gen)];
			comps = 0;
			startTime = high_resolution_clock::now();
			binSearchRec(A, 0, n - 1, mid);
			endTime = high_resolution_clock::now();
			elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			file << "mid " << n << " " << m << " " << comps << " " << elapsed << " " << (comps / logn) << " " << (elapsed / logn) << endl;
			
			int end = A[disEnd(gen)];
			comps = 0;
			startTime = high_resolution_clock::now();
			binSearchRec(A, 0, n - 1, end);
			endTime = high_resolution_clock::now();
			elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			file << "end " << n << " " << m << " " << comps << " " << elapsed << " " << (comps / logn) << " " << (elapsed / logn) << endl;
			
			int notA = disNot(gen);
			while(binSearchRec(A, 0, n - 1, notA) != -1) {
				notA = disNot(gen);
			}
			comps = 0;
			startTime = high_resolution_clock::now();
			binSearchRec(A, 0, n - 1, notA);
			endTime = high_resolution_clock::now();
			elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			file << "not " << n << " " << m << " " << comps << " " << elapsed << " " << (comps / logn) << " " << (elapsed / logn) << endl;
			
			int inA = A[disInA(gen)];
			comps = 0;
			startTime = high_resolution_clock::now();
			binSearchRec(A, 0, n - 1, inA);
			endTime = high_resolution_clock::now();
			elapsed = duration_cast<nanoseconds>(endTime - startTime).count();
			file << "inA " << n << " " << m << " " << comps << " " << elapsed << " " << (comps / logn) << " " << (elapsed / logn) << endl;
		}
	}

	file.close();

	return 0;
}