#include "Graph.hpp"

BiPartite::BiPartite(int k, int i) {
	if (k < 1 || k > 16) throw range_error("invalid bipartite graph size");
	if (i < 1 || i > k) throw range_error("invalid bipartite graph degree");

	this->k = k;
	this->i = i;

	int b = 1 << k;
	setN(2*b+2);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, b);

	for (int v = 1; v <= b; v++) {
		addEdge(0, v, 1);
		addEdge(v, 0, 0);

		addEdge(b+v, n-1, 1);
		addEdge(n-1, b+v, 0);

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