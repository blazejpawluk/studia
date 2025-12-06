#pragma once

#include <vector>
#include <limits.h>

struct Graph {
	int n;
	bool directed;
	long long m;
	long long minCost, maxCost;
	std::vector<std::vector<std::pair<int, long long>>> adj;

	Graph(int n, bool directed);
	void addEdge(int u, int v, long long cost);
};