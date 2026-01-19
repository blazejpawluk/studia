#include "Graph.hpp"
#include <random>
random_device rd;
mt19937 gen(rd());

BiPartite::BiPartite(int k, int i) {
	if (k < 1 || k > 16) throw range_error("invalid bipartite graph size");
	if (i < 1 || i > k) throw range_error("invalid bipartite graph degree");

	int b = 1 << k;
	uniform_int_distribution<> dis(1, b);
	setN(2*b+2);

	for (int v = 1; v <= b; v++) {
		addEdge(0, v, 1);
		addEdge(b+v, n-1, 1);

		for (int j = 0; j < i; j++) {
			int u = b + dis(gen);
			bool success = addEdge(v, u, 1);
			while (!success) {
				u = b + dis(gen);
				success = addEdge(v, u, 1);
			}
			addEdge(u, v, 0);
		}
	}
}