#include <iostream>
#include "lib/Array.h"
#include "lib/Algorithms.h"

Array a;
QuickSort qs;

int main() {
	int n;
	std::cout << "Array length: ";
	std::cin >> n;

	int startArray[n], qsA[n], qssA[n], dpqsA[n], dpqssA[n];
	std::cout << "Array, " << n << " integers from range [0, " << 2 * n - 1 << "]: ";
	for (int i = 0; i < n; i++) {
		std::cin >> startArray[i];
		qsA[i] = startArray[i];
		qssA[i] = startArray[i];
		dpqsA[i] = startArray[i];
		dpqssA[i] = startArray[i];
	}

	std::cout << "==================================================\n";
	std::cout << "----- QUICK SORT -----\n";

	if (n < 30) {
		std::cout << "Starting array: ";
		a.print(qsA, n);
		std::cout << "Sorting array using quick sort...\n";
	}

	qs.quickSort(qsA, n);

	if (n < 30) {
		std::cout << "Starting array: ";
		a.print(startArray, n);
		std::cout << "  Sorted array: ";
		a.print(qsA, n);
		std::cout << "Array is " << (a.isSorted(qsA, n) ? "" : "not ") << "sorted.\n";
	}

	std::cout << "Comparisons: " << qs.c.getComps() << std::endl;
	std::cout << "      Swaps: " << qs.c.getSwaps() << std::endl;

	std::cout << "==================================================\n";
	std::cout << "----- QUICK SELECT SORT -----\n";

	if (n < 30) {
		std::cout << "Starting array: ";
		a.print(qssA, n);
		std::cout << "Sorting array using quick select sort...\n";
	}

	qs.quickSelectSort(qssA, n);

	if (n < 30) {
		std::cout << "Starting array: ";
		a.print(startArray, n);
		std::cout << "  Sorted array: ";
		a.print(qssA, n);
		std::cout << "Array is " << (a.isSorted(qssA, n) ? "" : "not ") << "sorted.\n";
	}

	std::cout << "Comparisons: " << qs.c.getComps() << std::endl;
	std::cout << "      Swaps: " << qs.c.getSwaps() << std::endl;

	std::cout << "==================================================\n";
	std::cout << "----- DUAL-PIVOT QUICK SORT -----\n";

	if (n < 30) {
		std::cout << "Starting array: ";
		a.print(dpqsA, n);
		std::cout << "Sorting array using dual-pivot quick sort...\n";
	}

	qs.DPQuickSort(dpqsA, n);

	if (n < 30) {
		std::cout << "Starting array: ";
		a.print(startArray, n);
		std::cout << "  Sorted array: ";
		a.print(dpqsA, n);
		std::cout << "Array is " << (a.isSorted(dpqsA, n) ? "" : "not ") << "sorted.\n";
	}

	std::cout << "Comparisons: " << qs.c.getComps() << std::endl;
	std::cout << "      Swaps: " << qs.c.getSwaps() << std::endl;

	std::cout << "==================================================\n";
	std::cout << "----- DUAL-PIVOT QUICK SELECT SORT -----\n";

	if (n < 30) {
		std::cout << "Starting array: ";
		a.print(dpqssA, n);
		std::cout << "Sorting array using dual-pivot quick select sort...\n";
	}

	qs.DPQuickSelectSort(dpqssA, n);

	if (n < 30) {
		std::cout << "Starting array: ";
		a.print(startArray, n);
		std::cout << "  Sorted array: ";
		a.print(dpqssA, n);
		std::cout << "Array is " << (a.isSorted(dpqssA, n) ? "" : "not ") << "sorted.\n";
	}

	std::cout << "Comparisons: " << qs.c.getComps() << std::endl;
	std::cout << "      Swaps: " << qs.c.getSwaps() << std::endl;

	return 0;
}