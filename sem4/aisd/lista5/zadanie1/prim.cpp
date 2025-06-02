#ifndef PRIM
#define PRIM

#include "graph.cpp"

vector<Edge> prim(Graph G) {
	int n = G.V.size();
	
	priority_queue<Edge> Q;
	bool vs[n];
	vector<Edge> T;
	
	int v = 1;
	vs[0] = true;
	for (int i = 1; i < n; i++) vs[i] = false;

	for (int i = 1; i < n; i++) {
		for (Edge e : G.E) {
			int u = -1;
			if (e.V.first == v)	u = e.V.second;
			else if (e.V.second == v) u = e.V.first;

			if (u != -1 && !vs[u]) Q.push(e);
		}

		Edge e;
		int u = -1;
		do {
			e = Q.top();
			Q.pop();
			if (e.V.first == v) u = e.V.second;
			else if (e.V.second == v) u = e.V.first;
		}
		while (u == -1 || (u != -1 && vs[u]));

		T.push_back(e);
		vs[u] = true;
		v = u; 
	}

	return T;
}

#endif