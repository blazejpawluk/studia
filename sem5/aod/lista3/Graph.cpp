#include "Graph.hpp"

// tworzenie grafu z listy krawędzi
Graph::Graph(int n, vector<pair<pair<int,int>,int>> E, bool directed) {
	this->n = n;
	this->adj.resize(n+1);

	for(pair<pair<int,int>,int> e : E) {
		int v = e.first.first, u = e.first.second, cost = e.second;

		if(v < 1 || v > n || u < 1 || u > n || cost < 0) throw "invalid data";

		this->adj[v].push_back({u, cost});
		if(!directed) this->adj[u].push_back({v, cost}); 
	}
}

// tworzenie grafu z listy sąsiedztwa
Graph::Graph(int n, vector<vector<pair<int,int>>> adj) {
	this->n = n;

	if(adj.size() != n+1) throw "invalid adj size";
	for(vector<pair<int,int>> list : adj) {
		for(pair<int,int> e : list) {
			int u = e.first, cost = e.second;
			if(u < 1 || u > n || cost < 0) throw "invalid data";
		}
	}
	this->adj = adj;
}

void Graph::print() {
	for(int i = 1; i <= n; i++) {
		for(pair<int, int> u : adj[i]) {
			cout << i << "-" << u.first << ", cost: " << u.second << endl;
		}
	}
}