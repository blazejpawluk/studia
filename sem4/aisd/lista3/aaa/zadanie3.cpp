#include <iostream>
#include <fstream>
#include <random>
#include "lib/Algorithms.h"

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::ofstream file("results/selectTresholdTest.txt");

	Select s;

	int t[4] = {3, 5, 7, 9};
	int m = 50;

	for (int i = 0; i < 4; i++) {
		s.setTreshold(t[i]);

		for (int n = 100; n <= 50000; n += 100) {
			std::cout << t[i] << " " << n << std::endl;
			std::uniform_int_distribution<> disA(0, 2 * n - 1);
			std::uniform_int_distribution<> disK(1, n);

			for (int j = 0; j < m; j++) {
				int A[n];
				for (int a = 0; a < n; a++) {
					A[a] = disA(gen);
				}

				int k = disK(gen);

				s.select(A, n, k);
				file << n << " " << t[i] << " " << s.c.getComps() << " " << s.c.getSwaps() << std::endl;
			}
		}
	}

	file.close();

	return 0;
}