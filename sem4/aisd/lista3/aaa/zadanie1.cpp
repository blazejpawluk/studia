#include <iostream>
#include <algorithm>
#include "lib/Array.h"
#include "lib/Algorithms.h"

Array a;

int main() {
	int n;
	std::cout << "Array length: ";
	std::cin >> n;

	int k;
	std::cout << "Order statistic: ";
	std:: cin >> k;

	int rArray[n], sArray[n], startArray[n];
	std::cout << "Array, " << n << " integers from range [0, " << 2 * n - 1 << "]: ";
	for (int i = 0; i < n; i++) {
		std::cin >> startArray[i];
		rArray[i] = startArray[i];
		sArray[i] = startArray[i];
	}

	std::cout << "==================================================\n";
	std::cout << "----- RANDOM SELECT -----\n";

	if (n < 30) {	
		std::cout << "Starting array: ";
		a.print(startArray, n);
		std::cout << "Looking for " << k << " order statistic...\n";
	}
		
	RandomSelect rs;	
	int rsX = rs.randomSelect(rArray, n, k);

	if (n < 30) {
		std::cout << k << " order statistic: " << rsX << std::endl;
		std::cout << "Starting array: ";
		a.print(startArray, n);
		std::cout << "  Ending array: ";
		a.print(rArray, n);
		std::cout << "  Sorted array: ";
		std::sort(rArray, rArray + n);
		a.print(rArray, n);
		std::cout << "Found value is " << (rsX == rArray[k - 1] ? "" : "not ") << "correct.\n";
	}

	std::cout << "Comparisons: " << rs.c.getComps() << std::endl;
	std::cout << "      Swaps: " << rs.c.getSwaps() << std::endl;

	std::cout << "==================================================\n";
	std::cout << "----- SELECT -----\n";

	if (n < 30) {
		std::cout << "Starting array: ";
		a.print(startArray, n);
		std::cout << "Looking for " << k << " order statistic...\n"; 
	}

	Select s;
	int sX = s.select(sArray, n, k);

	if (n < 30) {
		std::cout << k << " order statistic: " << sX << std::endl;
		std::cout << "Starting array: ";
		a.print(startArray, n);
		std::cout << "  Ending array: ";
		a.print(sArray, n);
		std::cout << "  Sorted array: ";
		std::sort(sArray, sArray + n);
		a.print(sArray, n);
		std::cout << "Found value is " << (sX == sArray[k - 1] ? "" : "not ") << "correct.\n";
	}

	std::cout << "Comparisons: " << s.c.getComps() << std::endl;
	std::cout << "      Swaps: " << s.c.getSwaps() << std::endl;

	return 0;
}