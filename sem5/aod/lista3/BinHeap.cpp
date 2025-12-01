#include "BinHeap.hpp"

BinHeap::BinHeap(int n) {
	heap.push_back(Node(0,-1));
	pos = vector<int>(n+1, -1);
}

void BinHeap::insert(int v, int k) {
	heap.push_back(Node(v,k));
	pos[v] = heap.size()-1;
	heapifyUp(pos[v]);
}

void BinHeap::decreaseKey(int v, int k) {
	int i = pos[v];
	if(k < heap[i].k) {
		heap[i].k = k;
		heapifyUp(i);
	}
}

Node BinHeap::pop() {
	Node x = heap[1];
	pos[x.v] = -1;
	heap[1] = heap[heap.size()-1];
	heap.pop_back();
	heapify(1);
	return x;
}

void BinHeap::swap(int i, int j) {
	Node vi = heap[i], vj = heap[j];
	heap[i] = vj; heap[j] = vi;
	
	int temp = pos[vi.v];
	pos[vi.v] = pos[vj.v]; 
	pos[vj.v] = temp;
}

void BinHeap::heapifyUp(int i) {
	int p = i/2;
	if(p > 0 && heap[i].k < heap[p].k) {
		swap(i,p);
		heapifyUp(p);
	}
}

void BinHeap::heapify(int i) {
	int l = 2*i, r = 2*i+1;
	int lowest = heap[i].k;

	if(l < heap.size() && heap[l].k < lowest) lowest = heap[l].k;
	if(r < heap.size() && heap[r].k < lowest) lowest = heap[r].k;

	if(lowest == heap[l].k) {
		swap(i,l);
		heapify(l);
	}
	if(lowest == heap[r].k) {
		swap(i,r);
		heapify(r);
	}
}

bool BinHeap::empty() {
	return !heap.size();
}

void BinHeap::print() {
	cout << " ";
	for(Node x : heap) cout << x.v << " ";
	cout << endl;
	for(Node x : heap) cout << x.k << " ";
	cout << endl;
	for(int p : pos) cout << p << " ";
	cout << endl << endl;
}

bool BinHeap::contains(int v) {
	return pos[v] != -1;
}