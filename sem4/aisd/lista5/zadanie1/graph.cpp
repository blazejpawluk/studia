#ifndef GRAPH
#define GRAPH

#include <bits/stdc++.h>
using namespace std;

struct Edge {
	pair<int, int> V;
	double w;
	
	Edge() {}
	Edge(int v, int u, double w) {
		V.first = v;
		V.second = u;
		this->w = w;
	} 

	bool operator<(const Edge& other) const {
		return this->w > other.w;
	}
};

struct Graph {
	vector<int> V;
	vector<Edge> E;
};

Graph generateFullGraph(int n) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0, 1.0);

	Graph G;
	for (int i = 0; i < n; i++) {
		G.V.push_back(i+1);
		for (int j = 0; j < i; j++) {
			G.E.push_back(Edge(j+1, i+1, dis(gen)));
		}
	}

	return G;
}

#endif