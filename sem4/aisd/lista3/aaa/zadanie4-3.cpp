#include <iostream>
#include <random>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include "lib/Algorithms.h"

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::ofstream file("results/binSearchConstTest.txt");
	file << "label n comps time\n";

	BinSearch b;

	for (int n = 1000; n <= 100000; n += 1000) {
		std::cout << n << std::endl;

		double logn = std::log2(n);

		std::uniform_int_distribution<> dis(0, 2 * n - 1);
		std::uniform_int_distribution<> disRan(0, 2 * n - 1);
		std::uniform_int_distribution<> disBeg(0, n / 3);
		std::uniform_int_distribution<> disMid(n / 3, 2 * n / 3);
		std::uniform_int_distribution<> disEnd(2 * n / 3, n - 1);
		std::uniform_int_distribution<> disNot(0, 2 * n - 1);
		std::uniform_int_distribution<> disInA(0, n - 1);

		for (int m = 0; m < 100; m++) {
			int A[n];
			for (int i = 0; i < n; i++) {
				A[i] = dis(gen);
			}
			std::sort(A, A + n);

			int ran = disRan(gen);
			auto startTime = std::chrono::high_resolution_clock::now();
			b.binSearch(A, n, ran);
			auto endTime = std::chrono::high_resolution_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			file << "ran " << n << " " << b.c.getComps() / logn << " " << elapsed / logn << std::endl;

			int beg = A[disBeg(gen)];
			startTime = std::chrono::high_resolution_clock::now();
			b.binSearch(A, n, beg);
			endTime = std::chrono::high_resolution_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			file << "beg " << n << " " << b.c.getComps() / logn << " " << elapsed / logn << std::endl;
			
			int mid = A[disMid(gen)];
			startTime = std::chrono::high_resolution_clock::now();
			b.binSearch(A, n, mid);
			endTime = std::chrono::high_resolution_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			file << "mid " << n << " " << b.c.getComps() / logn << " " << elapsed / logn << std::endl;
			
			int end = A[disEnd(gen)];
			startTime = std::chrono::high_resolution_clock::now();
			b.binSearch(A, n, end);
			endTime = std::chrono::high_resolution_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			file << "end " << n << " " << b.c.getComps() / logn << " " << elapsed / logn << std::endl;
			
			int notA = disNot(gen);
			while(b.binSearch(A, n, notA) != -1) {
				notA = disNot(gen);
			}
			startTime = std::chrono::high_resolution_clock::now();
			b.binSearch(A, n, notA);
			endTime = std::chrono::high_resolution_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			file << "not " << n << " " << b.c.getComps() / logn << " " << elapsed / logn << std::endl;
			
			int inA = A[disInA(gen)];
			startTime = std::chrono::high_resolution_clock::now();
			b.binSearch(A, n, inA);
			endTime = std::chrono::high_resolution_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			file << "inA " << n << " " << b.c.getComps() / logn << " " << elapsed / logn << std::endl;
		}
	}

	file.close();

	return 0;
}