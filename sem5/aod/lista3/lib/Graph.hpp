#pragma once
#include <bits/stdc++.h>
#include "BinHeap.hpp"
using namespace std;

class Graph {
public:
	int n; // liczba wierzchołków
	int m; // liczba krawedzi
	vector<vector<pair<int,int>>> adj; // lista sąsiedztwa u: (v, cost)
	int minCost, maxCost;

	Graph(int n, vector<pair<pair<int,int>,int>> E); // lista krawędzi ((u,v), cost)
	Graph(int n, vector<vector<pair<int,int>>> adj);

	void DijkstraFull(int s);
	int DijkstraTwo(int s, int t);

	void DialFull(int s);
	int DialTwo(int s, int t);

	void RadixHeapFull(int s);
	int RadixHeapTwo(int s, int t);
};