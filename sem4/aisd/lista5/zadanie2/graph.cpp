#ifndef TREE
#define TREE

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

struct Tree {
	vector<int> V;
	vector<int>* N;
	int* X;
	int root;

	Tree (int n, int root) {
		this->root = root;
		N = new vector<int>[n+1];
		X = new int[n+1];
	}
};

Tree createTree(int n, int root) {
	Graph G = Prim(generateFullGraph(n));
	Tree T(n, root);
	T.V = G.V;

	for (Edge e : G.E) {
		T.N[e.V.first].push_back(e.V.second);
		T.N[e.V.second].push_back(e.V.first);
	}

	queue<int> Q;
	Q.push(root);
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		for (int k : T.N[v]) {
			auto it = remove(T.N[k].begin(), T.N[k].end(), v);
			T.N[k].erase(it, T.N[k].end());
			Q.push(k);
		}
	}

	return T;
}

#endif