#include "Graph.hpp"

Graph::Graph() {}

Graph::Graph(int N) {
	setN(N);
}

void Graph::setN(int N) {
	if (N < 1) throw range_error("number of vertices must be > 0");
	n = N;
	adj.assign(n, {});

	parentNode.assign(n, -1);
	parentEdge.assign(n, -1);
	visited.assign(n, 0);
	q.clear();
	q.reserve(n);
}

void Graph::addEdge(int u, int v, int c) {
	if (u < 0 || u >= n || v < 0 || v >= n) throw range_error("invalid vertex index");
	if (c < 0) throw range_error("invalid capacity");

	int rev_u = adj[v].size();
	int rev_v = adj[u].size();

	adj[u].push_back({v, c, rev_u, c});
	adj[v].push_back({u, 0, rev_v, 0});
}

int Graph::getAugmentingPaths() const {
	return augmentingPaths;
}

void Graph::print() {
	for (int u = 0; u < n; u++) {
		cout << u << ": ";
		for (const auto &e : adj[u]) {
			if (e.orig > 0)
				cout << e.to << "-" << e.orig << " ";
		}
		cout << '\n';
	}
}

void Graph::printFlow() const {
	for (int u = 0; u < n; u++) {
		for (const auto &e : adj[u]) {
			if (e.orig > 0) {
				cout << "(" << u << ", " << e.to << ") = " << (e.orig - e.cap) << '\n';
			}
		}
	}
}