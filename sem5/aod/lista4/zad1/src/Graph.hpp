// #ifndef GRAPH
// #define GRAPH

// #include <iostream>
// #include <vector>
// using namespace std;

// class Graph {
// public:
// 	struct Edge {
// 		int to;
// 		int rev;
// 		int cap;
// 		int orig;
// 	};

// 	int n;
// 	vector<vector<Edge>> adj;

// 	Graph();
// 	Graph(int N);

// 	void setN(int N);
// 	void addEdge(int u, int v, int c);

// 	int EdmondsKarp(int s, int t);
// 	int getAugmentingPaths() const;

// 	void print();
// 	void printFlow() const;

// private:
// 	vector<int> parentNode;
// 	vector<int> parentEdge;
// 	vector<unsigned char> visited;
// 	vector<int> q;

// 	int augmentingPaths = 0;

// 	bool BFS(int s, int t);
// };

// class HyperCube : public Graph {
// public:
// 	int k;
// 	HyperCube(int k);
// };

// #endif

#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Graph {
public:
	int n;
	vector<vector<int>> E;

	Graph();
	Graph(int N);
	Graph(int N, vector<vector<int>> edges);

	void setN(int N);
	void addEdge(int i, int j, int c);

	int flowVal (const vector<vector<int>> &f, int s);
	int getAugmentingPaths() const;
	
	vector<vector<int>> EdmondsKarp(int s, int t);

	void print();
	void printFlow(const vector<vector<int>> &f);

private:
	vector<int> parent;
	vector<int> visited;
	vector<int> q;

	int augmentingPaths = 0;

	bool BFS(const vector<vector<int>> &r, int s, int t, vector<int> &path);

	int minCF(const vector<int> &p, const vector<vector<int>> &r);
};

class HyperCube : public Graph {
public:
	int k;

	HyperCube(int k);
};

#endif