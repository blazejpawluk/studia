#include "Graph.hpp"

// tworzenie grafu z listy krawędzi
Graph::Graph(int n, vector<pair<pair<int,int>,int>> E, bool directed) {
	this->n = n;
	this->adj.resize(n+1);
	this->minCost = INT_MAX;
	this->maxCost = -1;

	for(pair<pair<int,int>,int> e : E) {
		int v = e.first.first, u = e.first.second, cost = e.second;

		if(v < 1 || v > n || u < 1 || u > n || cost < 0) throw "invalid data";

		this->adj[v].push_back({u, cost});
		if(!directed) this->adj[u].push_back({v, cost});
		
		if(this->minCost > cost) this->minCost = cost;
		if(this->maxCost < cost) this->maxCost = cost;
	}
}

// tworzenie grafu z listy sąsiedztwa
Graph::Graph(int n, vector<vector<pair<int,int>>> adj) {
	this->n = n;
	this->minCost = INT_MAX;
	this->maxCost = -1;

	if(adj.size() != n+1) throw "invalid adj size";
	for(vector<pair<int,int>> list : adj) {
		for(pair<int,int> e : list) {
			int u = e.first, cost = e.second;
			if(u < 1 || u > n || cost < 0) throw "invalid data";
			if(this->minCost > cost) this->minCost = cost;
			if(this->maxCost < cost) this->maxCost = cost;
		}
	}
	this->adj = adj;
}