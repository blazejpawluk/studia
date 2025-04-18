#include <iostream>
#include <fstream>
#include <random>
#include "lib/Algorithms.h"

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::ofstream fileRS("results/randomSelectTest.txt");
	std::ofstream fileS("results/selectTest.txt");

	RandomSelect rs;
	Select s;

	int m = 50;
	for (int n = 100; n <= 10000; n += 100) {
		std::cout << n << std::endl;
		std::uniform_int_distribution<> dis(0, 2 * n - 1);

		int k[5] = {1, n / 4, n / 2, 3 * n / 4, n};

		for (int ki = 0; ki < 5; ki++) {
			for (int i = 0; i < m; i++) {
				int aRS[n], aS[n];
				for (int j = 0; j < n; j++) {
					aRS[j] = dis(gen);
					aS[j] = aRS[j];
				}
	
				rs.randomSelect(aRS, n, k[ki]);
				fileRS << n << " " << k[ki] << " " << rs.c.getComps() << " " << rs.c.getSwaps() << std::endl;
	
				s.select(aS, n, k[ki]);
				fileS << n << " " << k[ki] << " " << s.c.getComps() << " " << s.c.getSwaps() << std::endl;
			}
		}
	}

	fileRS.close();
	fileS.close();

	return 0;
}