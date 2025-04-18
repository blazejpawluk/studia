#include <iostream>
#include "lib/Array.h"
#include "lib/Algorithms.h"

Array a;

int main() {
	int n;
	std::cout << "Array length: ";
	std::cin >> n;

	int A[n];
	std::cout << "Array, " << n << " integers from range [0, " << 2 * n - 1 << "]: ";
	for (int i = 0; i < n; i++) {
		std::cin >> A[i];
	}

	int v;
	std::cout << "Value to search for: ";
	std::cin >> v;

	std::cout << "==================================================\n";
	std::cout << "----- BINARY SEARCH -----\n";

	std::cout << "Starting array: ";
	a.print(A, n);
	std::cout << "Looking for " << v << "...\n";

	BinSearch bs;
	int x = bs.binSearch(A, n, v);

	if (x == -1) {
		std::cout << "Value " << v << " not found in the array.\n";
	} else {
		std::cout << "Value " << v << " found in array on position " << x << std::endl;
	}

	std::cout << "Comparisons: " << bs.c.getComps() << std::endl;

	return 0;
}