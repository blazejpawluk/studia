#pragma once
#include <bits/stdc++.h>
#include "BinHeap.hpp"
using namespace std;

class Graph {
public:
	int n; // liczba wierzchołków
	long long m; // liczba krawedzi
	vector<vector<pair<int,long long>>> adj; // lista sąsiedztwa u: (v, cost)
	long long minCost, maxCost;

	Graph(int n, vector<pair<pair<int,int>,long long>> E); // lista krawędzi ((u,v), cost)
	Graph(int n, vector<vector<pair<int,long long>>> adj);

	void DijkstraFull(int s);
	long long DijkstraTwo(int s, int t);

	void DialFull(int s);
	long long DialTwo(int s, int t);

	void RadixHeapFull(int s);
	long long RadixHeapTwo(int s, int t);
};