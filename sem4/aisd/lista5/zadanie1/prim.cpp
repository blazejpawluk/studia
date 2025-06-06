#ifndef PRIM
#define PRIM

#include "graph.cpp"

Graph Prim(Graph G) {
	int n = G.V.size();

	vector<vector<pair<int, double>>> neighbour(n+1);
	for (Edge e : G.E) {
		neighbour[e.V.first].push_back({e.V.second, e.w});
		neighbour[e.V.second].push_back({e.V.first, e.w});
	}

	vector<bool> inMST(n+1, false);
	vector<double> key(n+1, numeric_limits<double>::infinity());
	vector<int> parent(n+1, -1);

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> Q;

	key[1] = 0.0;
	Q.push({key[1], 1});

	while (!Q.empty()) {
		pair<double, int> top = Q.top();
		Q.pop();

		if (inMST[top.second]) continue;
		inMST[top.second] = true;

		for (pair<int, double> n : neighbour[top.second]) {
			if (!inMST[n.first] && n.second < key[n.first]) {
				key[n.first] = n.second;
				parent[n.first] = top.second;
				Q.push({key[n.first], n.first});
			}
		}
	}

	Graph result;
	result.V = G.V;
	for (int v = 2; v <= n; v++) 
		if (parent[v] != -1) result.E.push_back(Edge(parent[v], v, key[v]));

	return result;
}

#endif