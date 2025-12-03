#include "Graph.hpp"
#include <cmath>

bool allEmpty(vector<vector<pair<int,int>>> x) {
	for(int i = 0; i < x.size(); i++) {
		if(!x[i].empty()) return false;
	}
	return true;
}

int firstNonEmpty(vector<vector<pair<int,int>>> x) {
	for(int i = 0; i < x.size(); i++) {
		if(!x[i].empty()) return i;
	}
	return -1;
}

void insert(int v, int d, vector<vector<pair<int,int>>> &x, vector<int> a, vector<int> b) {
	// for(int i = 0; i < a.size(); i++) cout << a[i] << " ";
	// cout << endl;
	// for(int i = 0; i < b.size(); i++) cout << b[i] << " ";
	// cout << endl;
	int k = 0;
	while(!(a[k] <= d && b[k] >= d)) k++;
	// cout << d << " " << k << endl;
	x[k].push_back({v,d});
}

void remove(int v, int d, vector<vector<pair<int,int>>> &x, vector<int> a, vector<int> b) {
	int k = 0;
	while(!(a[k] <= d && b[k] >= d)) k++;
	for(int i = 0; i < x[k].size(); i++) {
		if(x[k][i].first == v) {
			x[k].erase(x[k].begin() + i);
			return;
		}
	}
}

void reshape(vector<vector<pair<int,int>>> &x, vector<int> &a, vector<int> &b, vector<int> width, int minD, int maxD, int k) {
	for(int i = 0; i < k; i++) {
		if(minD > maxD) {
			a[i] = maxD;
			b[i] = -1;
		} else {
			a[i] = minD;
			minD += width[i];
			b[i] = min(minD-1, maxD);
		}
	}
	for(pair<int,int> p : x[k]) {
		int v = p.first;
		int d = p.second;
		insert(v,d,x,a,b);
	}
	x[k].clear();
}

void Graph::RadixHeapFull(int s) {
	int K = ceil(log2(n*maxCost));

	vector<int> dist(n+1, INT_MAX);
	dist[s] = 0;

	vector<vector<pair<int,int>>> bucket(K+1);
	bucket[0].push_back({s,0});

	vector<int> width(K+1);
	vector<int> a(K+1);
	vector<int> b(K+1);
	width[0] = 1; a[0] = 0;
	int x = 1;
	for(int i = 1; i <= K; i++) {
		width[i] = x;
		a[i] = x;
		x *= 2;
		b[i] = x-1;
	}

	while(!allEmpty(bucket)) {
		int k = firstNonEmpty(bucket);
		
		if(k < 2) {
			pair<int,int> x = bucket[k][bucket[k].size()-1];
			bucket[k].pop_back();
			int v = x.first, d = x.second;
			
			for(pair<int,int> edge : adj[v]) {
				int u = edge.first, cost = edge.second;
				if(dist[u] > d + cost) {
					if(dist[u] != INT_MAX) remove(u, dist[u], bucket, a, b);
					dist[u] = d + cost;
					insert(u, dist[u], bucket, a, b);
				}
			}
		} else {
			int minD = INT_MAX;
			for(int i = 0; i < bucket[k].size(); i++)
			if(bucket[k][i].second < minD) minD = bucket[k][i].second;
			int maxD = a[k] + width[k+1] - 1;
			reshape(bucket, a, b, width, minD, maxD, k);
		}
	}
}

int Graph::RadixHeapTwo(int s, int t) {
	int K = ceil(log2(n*maxCost));

	vector<int> dist(n+1, INT_MAX);
	dist[s] = 0;

	vector<vector<pair<int,int>>> bucket(K+1);
	bucket[0].push_back({s,0});

	vector<int> width(K+1);
	vector<int> a(K+1);
	vector<int> b(K+1);
	width[0] = 1; a[0] = 0;
	int x = 1;
	for(int i = 1; i <= K; i++) {
		width[i] = x;
		a[i] = x;
		x *= 2;
		b[i] = x-1;
	}

	while(!allEmpty(bucket)) {
		int k = firstNonEmpty(bucket);
		
		if(k < 2) {
			pair<int,int> x = bucket[k][bucket[k].size()-1];
			bucket[k].pop_back();
			int v = x.first, d = x.second;

			if(v == t) return d;
			
			for(pair<int,int> edge : adj[v]) {
				int u = edge.first, cost = edge.second;
				if(dist[u] > d + cost) {
					if(dist[u] != INT_MAX) remove(u, dist[u], bucket, a, b);
					dist[u] = d + cost;
					insert(u, dist[u], bucket, a, b);
				}
			}
		} else {
			int minD = INT_MAX;
			for(int i = 0; i < bucket[k].size(); i++)
			if(bucket[k][i].second < minD) minD = bucket[k][i].second;
			int maxD = a[k] + width[k+1] - 1;
			reshape(bucket, a, b, width, minD, maxD, k);
		}
	}

	return -1;
}