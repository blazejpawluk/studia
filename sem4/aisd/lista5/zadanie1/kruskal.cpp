#ifndef KRUSKAL
#define KRUSKAL

#include "graph.cpp"

vector<Edge> kruskal(Graph G) {
	int n = G.V.size();

	unordered_set<int> Z[n];
	for (int i = 0; i < n; i++) Z[i].insert(i+1);

	priority_queue<Edge> Q;
	for (Edge e : G.E) Q.push(e);

	vector<Edge> T;
	for (int i = 1; i < n; i++) {
		Edge e;
		do {
			e = Q.top();
			Q.pop();
		}
		while (Z[e.V.first] == Z[e.V.second]);

		T.push_back(e);

		unordered_set<int> temp = Z[e.V.first];
		temp.insert(Z[e.V.second].begin(), Z[e.V.second].end());
		Z[e.V.first] = temp;
		Z[e.V.second] = temp;
	}

	return T;
}

#endif