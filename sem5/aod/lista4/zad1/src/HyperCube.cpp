#include "Graph.hpp"
#include <random>

random_device rd;
mt19937 gen(rd());

int H(int x) {
	int c = 0;
	while (x > 0) {
		c += (x % 2);
		x /= 2;
	}
	return c;
}

HyperCube::HyperCube(int k) {
	if (k < 1 || k > 16) throw range_error("invalid hyper cube dim");

	setN(1 << k);

	for (int x = 0; x < n; x++) {
		int h = H(x);
		int z = k - h;
		uniform_int_distribution<> dis(1, 1 << max(h+1, z));
		
		for (int i = 0; i < k; i++) {
			int bit = 1 << i;
			if ((x & bit) == 0) {
				addEdge(x, x | bit, dis(gen));
			}
		}
	}
}