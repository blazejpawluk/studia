#include "../../lib/Graph.hpp"

Graph::Graph(int n, bool directed) {
	this->n = n;
	this->directed = directed;
	this->m = 0;
	this->minCost = LONG_LONG_MAX;
	this->maxCost = -1;
	this->adj.resize(n+1);
}

void Graph::addEdge(int u, int v, long long cost) {
	if (u < 1 || u > n || v < 1 || v > n || cost < 0) return;
	adj[u].push_back({v, cost});
	if (!directed) adj[v].push_back({u, cost});

	if (cost > maxCost) maxCost = cost;
	if (cost < minCost) minCost = cost;
}