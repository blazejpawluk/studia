#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Graph {
public:
	int n;
	
	struct Edge {
		int to;
		int capacity;
		int flow;
		int rev;
		Edge(int t, int c, int f, int r) : to(t), capacity(c), flow(f), rev(r) {}
	};
	vector<vector<Edge>> E;

	Graph();
	Graph(int N);

	void setN(int N);
	void addEdge(int i, int j, int c);

	int flowVal (int s);
	int getAugmentingPaths() const;
	void resetFlow();
	
	void EdmondsKarp(int s, int t);
	int Dinic(int s, int t);

	void print();
	void printFlow();

private:
	vector<int> parent;
	vector<int> visited;
	vector<int> q;

	int augmentingPaths = 0;

	bool BFS(int s, int t, vector<int> &path);
	int minCF(const vector<int> &p);
	int findEdge(int u, int v);

	vector<int> level;
	vector<int>ptr;

	bool BFSlevel(int s, int t);
	int DFSblocking(int u, int t, int pushed);
};

class HyperCube : public Graph {
public:
	int k;

	HyperCube(int k);
};

#endif