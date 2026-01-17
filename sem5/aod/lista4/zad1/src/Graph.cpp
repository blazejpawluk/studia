#include "Graph.hpp"

Graph::Graph() {}

Graph::Graph(int N) {
	if (N < 1) throw range_error("number of vertixes should be > 1");

	n = N;
	E = vector<vector<Edge>>(n);
}

void Graph::setN(int N) {
	if (N < 1) throw range_error("number of vertixes should be > 1");

	n = N;
	E = vector<vector<Edge>>(n);
}

void Graph::addEdge(int i, int j, int c) {
	if (i < 0 || i >= n || j < 0 || j >= n) throw range_error("invalid vertix's index");
	if (c < 0) throw range_error("invalid capacity");

	E[i].push_back(Edge(j, c, 0));
	E[j].push_back(Edge(i, 0, 0));
}

int Graph::flowVal(int s) {
	int sum = 0;
	for (const auto &e : E[s]) if (e.capacity > 0) sum += e.flow; 
	return sum;
}

int Graph::getAugmentingPaths() const {
	return augmentingPaths;
}

void Graph::print() {
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (const auto &e : E[i]) if (e.capacity > 0) cout << e.to << "-" << e.capacity << " ";
		cout << '\n';
	}
}

void Graph::printFlow() {
	for (int i = 0; i < n; i++) {
		for (const auto &e : E[i]) if (e.capacity > 0) cout << "(" << i << "," << e.to << ")=" << e.flow << '\n';
	}
}