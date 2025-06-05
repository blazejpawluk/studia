#ifndef HEAP
#define HEAP

#include <bits/stdc++.h>
using namespace std;

int comps;
bool compare(bool a) {
	comps++;
	return a;
}

int parent(int i) {return i/2;}
int left(int i) {return 2*i;}
int right(int i) {return 2*i+1;}
int size(vector<int> A) {return A.size()-1;}

void heapify(vector<int>& A, int i) {
	int l = left(i), r = right(i);
	
	int smallest = i;
	if (l <= size(A) && compare(A[l] < A[smallest])) smallest = l;
	if (r <= size(A) && compare(A[r] < A[smallest])) smallest = r;

	if (smallest != i) {
		swap(A[i], A[smallest]);
		heapify(A, smallest);
	}
}

vector<int> buildHeap(vector<int> A) {
	for (int i = size(A)/2; i > 0; i--) heapify(A, i);
	return A;
}

int find(vector<int> A, int x) {
	for (int i = 1; i <= size(A); i++) 
		if (compare(A[i] == x)) return i;
	return -1;
}

vector<int> makeHeap() {
	vector<int> H;
	H.push_back(-1);
	return H;
}

void Insert(vector<int>& H, int x) {
	H.push_back(x);
	int i = size(H);
	while (i > 1 && compare(H[parent(i)] > x)) {
		H[i] = H[parent(i)];
		i = parent(i);
	}
	H[i] = x;
}

int Minimum(vector<int> H) {
	return H[1];
}

int ExtractMin(vector<int>& H) {
	int min = H[1];
	H[1] = H[size(H)];
	H.pop_back();
	heapify(H, 1);
	return min;
}

vector<int> Union(vector<int> H1, vector<int> H2) {
	for (int i = 1; i <= size(H2); i++) H1.push_back(H2[i]);
	return buildHeap(H1);
}

void DecreaseKey(vector<int>& H, int x, int k) {
	int i = find(H, x);
	if (compare(H[i] < k)) {
		H[i] = k;
		heapify(H, i);
	} else {
		while (i > 1 && compare(H[parent(i)] > k)) {
			H[i] = H[parent(i)];
			i = parent(i);
		}
		H[i] = k;
	}
}

void Delete(vector<int>& H, int x) {
	int i = find(H, x);
	
	H[i] = H[size(H)];
	H.pop_back();
	
	if (compare(H[i] > H[parent(i)])) heapify(H, i);
	else {
		while (i > 1 && compare(H[parent(i)] > H[i])) {
			swap(H[parent(i)], H[i]);
			i = parent(i);
		}
	}
}

void print(vector<int> H) {
	for (int i = 1; i <= size(H); i++) cout << H[i] << " ";
	cout << endl;
}

bool isSorted(vector<int> H) {
	for (int i = 2; i <= size(H); i++)
		if (H[i-1] > H[i]) return false;
	return true;
}

#endif