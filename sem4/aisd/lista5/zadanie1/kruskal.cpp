#ifndef KRUSKAL
#define KRUSKAL

#include "graph.cpp"

int findSet(int v, vector<int>& parent) {
	if (parent[v] == v) return v;
	return parent[v] = findSet(parent[v], parent);
}

void unionSets(int a, int b, vector<int>& parent, vector<int>& rank) {
	a = findSet(a, parent);
	b = findSet(b, parent);
	if (a != b) {
		if (rank[a] < rank[b]) swap(a, b);
		parent[b] = a;
		if (rank[a] == rank[b]) rank[a]++;
	}
}

Graph Kruskal(Graph G) {
	int n = G.V.size();

	vector<int> parent(n+1), rank(n+1, 0);
	for (int i = 1; i <= n; i++) parent[i] = i;

	vector<Edge> sortedE = G.E;
	sort(sortedE.begin(), sortedE.end(), [](const Edge& a, const Edge&b) {return a.w < b.w;});

	Graph result;
	result.V = G.V;

	for (Edge e : sortedE) {
		int u = e.V.first;
		int v = e.V.second;
		if (findSet(u, parent) != findSet(v, parent)) {
			unionSets(u, v, parent, rank);
			result.E.push_back(e);

			if (result.E.size() == n-1) break;
		}
	}

	return result;
}

#endif