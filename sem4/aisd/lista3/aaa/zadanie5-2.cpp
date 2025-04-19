#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include "lib/Algorithms.h"

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::ofstream fileQS("results/quickSortTest.txt");
	std::ofstream fileQSS("results/quickSelectSortTest.txt");
	std::ofstream fileDPQS("results/DPQuickSortTest.txt");
	std::ofstream fileDPQSS("results/DPQuickSelectSortTest.txt");

	QuickSort q;

	for (int n = 100; n <= 10000; n += 100) {
		std::cout << n << std::endl;

		std::uniform_int_distribution<> dis(0, 2 * n - 1);

		for (int m = 0; m < 50; m++) {
			int A[n], qs[n], qss[n], dpqs[n], dpqss[n];
			for (int i = 0; i < n; i++) {
				A[i] = dis(gen);
				qs[i] = A[i];
				qss[i] = A[i];
				dpqs[i] = A[i];
				dpqss[i] = A[i];
			}

			auto startTime = std::chrono::high_resolution_clock::now();
			q.quickSort(qs, n);
			auto endTime = std::chrono::high_resolution_clock::now();
			auto elapsed  = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			fileQS << n << " " << q.c.getComps() << " " << elapsed << std::endl;

			startTime = std::chrono::high_resolution_clock::now();
			q.quickSelectSort(qss, n);
			endTime = std::chrono::high_resolution_clock::now();
			elapsed  = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			fileQSS << n << " " << q.c.getComps() << " " << elapsed << std::endl;

			startTime = std::chrono::high_resolution_clock::now();
			q.DPQuickSort(dpqs, n);
			endTime = std::chrono::high_resolution_clock::now();
			elapsed  = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			fileDPQS << n << " " << q.c.getComps() << " " << elapsed << std::endl;

			startTime = std::chrono::high_resolution_clock::now();
			q.DPQuickSelectSort(dpqss, n);
			endTime = std::chrono::high_resolution_clock::now();
			elapsed  = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
			fileDPQSS << n << " " << q.c.getComps() << " " << elapsed << std::endl;
		}
	}

	fileQS.close();
	fileQSS.close();
	fileDPQS.close();
	fileDPQSS.close();

	return 0;
}