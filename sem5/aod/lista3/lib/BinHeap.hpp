#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Node {
	int v;
	int k;
	Node(int v, int k) {this->v = v; this->k = k;}
};

class BinHeap {
private:
	vector<Node> heap;
	vector<int> pos;

	void swap(int i, int j);
	void heapifyUp(int i);
	void heapify(int i);
public:
	BinHeap(int n);
	void insert(int v, int k);
	void decreaseKey(int v, int k);
	Node pop();
	bool empty();
	bool contains(int v);
};