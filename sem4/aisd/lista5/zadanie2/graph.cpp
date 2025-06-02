#ifndef TREE
#define TREE

#include "bits/stdc++.h"
using namespace std;

struct Graph {
	vector<int> V;
	vector<pair<int, int>> E;
};

Graph createGraph(int n) {
	Graph G;
	if (n <= 0) return G;

	for (int i = 0; i < n; i++) G.V.push_back(i);

	if (n == 1) return G;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(0, n-1);

	vector<int> prufer;
	for (int i = 0; i < n - 2; i++) prufer.push_back(distrib(gen));

	vector<int> degree(n, 1);
	for (int x : prufer) degree[x]++;

	set<int> leaves;
	for (int i = 0; i < n; i++) 
		if (degree[i] == 1) leaves.insert(i);

	for (int x : prufer) {
		int leaf = *leaves.begin();
		leaves.erase(leaves.begin());

		G.E.emplace_back(leaf, x);

		degree[leaf]--;
		degree[x]--;

		if (degree[x] == 1) leaves.insert(x);
	}

	auto it = leaves.begin();
	int u = *it;
	it++;
	int v = *it;
	G.E.emplace_back(u, v);

	return G;
}

struct Tree {
	int root;
	int n;
	vector<int>* children;
	int* x;

	Tree(int root, int n) {
		this->root = root;
		this->n = n;
		children = new vector<int>[n];
		x = new int[n];
	}
};

Tree createTree(Tree T, Graph G, int v) {
	int n = G.V.size();

	for (pair<int, int> edge : G.E) {
		if (edge.first == v) {
			bool isParent = false;
			for (int kids : T.children[edge.second]) 
				if (kids == edge.first) isParent = true;
			
			if (!isParent) T.children[v].push_back(edge.second);
		} else if (edge.second == v) {
			bool isParent = false;
			for (int kids : T.children[edge.first]) 
				if (kids == edge.second) isParent = true;
			
			if (!isParent) T.children[v].push_back(edge.first);
		}
	}

	for (int k : T.children[v]) createTree(T, G, k);

	return T;
}

#endif