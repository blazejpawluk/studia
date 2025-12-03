#pragma once
#include <bits/stdc++.h>
#include "BinHeap.hpp"
using namespace std;

class Graph {
private:
	int n; // liczba wierzchołków
	vector<vector<pair<int,int>>> adj; // lista sąsiedztwa (wierzchołek, do którego prowadzona jest krawędź i jego koszt)
	int minCost, maxCost;
public:
	Graph(int n, vector<pair<pair<int,int>,int>> E, bool directed);
	Graph(int n, vector<vector<pair<int,int>>> adj);

	void DijkstraFull(int s);
	int DijkstraTwo(int s, int t);

	void DialFull(int s);
	int DialTwo(int s, int t);

	void RadixHeapFull(int s);
	int RadixHeapTwo(int s, int t);
};