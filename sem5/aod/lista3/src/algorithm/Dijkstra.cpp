#include "../../lib/Graph.hpp"

void Graph::DijkstraFull(int s) {
	vector<long long> dist(n+1, INT_MAX);
	dist.reserve(n+1);
	dist[s] = 0;

	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
	pq.push({0, s});

	while(!pq.empty()) {
		auto x = pq.top(); pq.pop();
		long long d = x.first; int v = x.second;

		if(d > dist[v]) continue;

		for(const auto &e : adj[v]) {
			int u = e.first;  long long cost = e.second;

			if(dist[u] > d+cost) {
				dist[u] = d+cost;
				pq.push({dist[u], u});
			}
		}
	}
}

long long Graph::DijkstraTwo(int s, int t) {
	vector<long long> dist(n+1, INT_MAX);
	dist.reserve(n+1);
	dist[s] = 0;

	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
	pq.push({0, s});

	while(!pq.empty()) {
		auto x = pq.top(); pq.pop();
		long long d = x.first; int v = x.second;

		if(v == t) return d;

		if(d > dist[v]) continue;

		for(const auto &e : adj[v]) {
			int u = e.first;  long long cost = e.second;

			if(dist[u] > d+cost) {
				dist[u] = d+cost;
				pq.push({dist[u], u});
			}
		}
	}

	return -1;
}