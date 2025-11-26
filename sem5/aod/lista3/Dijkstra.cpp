#include "Graph.hpp"

void Graph::DijkstraFull(int s) {
	vector<int> dist(n+1, INT_MAX);
	vector<bool> visited(n+1, false);

	dist[s] = 0;
	visited[s] = true;

	BinHeap heap(n);
	heap.insert(s,0);

	while(!heap.empty()) {
		Node x = heap.pop();
		int v = x.v, k = x.k;

		for(pair<int,int> e : adj[v]) {
			int u = e.first, cost = e.second;

			if(visited[u]) {
				if(dist[u] > k+cost) {
					dist[u] = k+cost;
					if(heap.contains(u)) heap.decreaseKey(u, k+cost);
				}
			} else {
				dist[u] = k+cost;
				visited[u] = true;
				heap.insert(u, k+cost);
			}
		}
	}
}

int Graph::DijkstraTwo(int s, int t) {
	vector<int> dist(n+1, INT_MAX);
	vector<bool> visited(n+1, false);

	dist[s] = 0;
	visited[s] = true;

	BinHeap heap(n);
	heap.insert(s,0);

	while(!heap.empty()) {
		Node x = heap.pop();
		int v = x.v, k = x.k;

		if(v == t) return k;

		for(pair<int,int> e : adj[v]) {
			int u = e.first, cost = e.second;

			if(visited[u]) {
				if(dist[u] > k+cost) {
					dist[u] = k+cost;
					if(heap.contains(u)) heap.decreaseKey(u, k+cost);
				}
			} else {
				dist[u] = k+cost;
				visited[u] = true;
				heap.insert(u, k+cost);
			}
		}
	}

	return -1;
}