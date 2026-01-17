#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
	struct Edge {
		int to;
		int rev;
		int cap;
		int orig;
	};

	int n;
	vector<vector<Edge>> adj;

	Graph();
	Graph(int N);

	void setN(int N);
	void addEdge(int u, int v, int c);

	int EdmondsKarp(int s, int t);
	int getAugmentingPaths() const;

	void print();
	void printFlow() const;

private:
	vector<int> parentNode;
	vector<int> parentEdge;
	vector<unsigned char> visited;
	vector<int> q;

	int augmentingPaths = 0;

	bool BFS(int s, int t);
};

class HyperCube : public Graph {
public:
	int k;
	HyperCube(int k);
};

#endif