#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
using namespace std;

class Graph {
public:
	int n;
	
	struct Edge {
		int to;
		int capacity;
		int flow;
		Edge(int t, int c, int f) : to(t), capacity(c), flow(f) {}
	};
	vector<vector<Edge>> E;

	Graph();
	Graph(int N);

	void setN(int N);
	bool addEdge(int i, int j, int c);

	int flowVal (int s);
	int getAugmentingPaths() const;
	
	void EdmondsKarp(int s, int t);

	void print();
	void printFlow();
	void printMatching();

private:
	vector<int> parent;
	vector<int> visited;
	vector<int> q;

	int augmentingPaths = 0;

	bool BFS(int s, int t, vector<int> &path);
	int minCF(const vector<int> &p);
	int findEdge(int u, int v);
};

class HyperCube : public Graph {
public:
	int k;

	HyperCube(int k);
	void generateCode(const string &filename, bool pF);
};

class BiPartite : public Graph {
public: 
	int k, i;
	
	BiPartite(int k, int i);
	void generateCode(const string &filename, bool pM);
};

#endif