#include <queue>
#include "../../lib/Graph.hpp"
#include "../../lib/alg/dijkstra.hpp"

std::vector<long long> dijkstra(Graph *G, int s) {
	std::vector<long long> dist(G->n + 1, LONG_LONG_MAX);
	dist[s] = 0;

	std::priority_queue<
		std::pair<long long, int>,
		std::vector<std::pair<long long, int>>,
		std::greater<std::pair<long long, int>>
	> pq;
	pq.push({s, 0});

	while (!pq.empty()) {
		auto top = pq.top(); pq.pop();
		int v = top.second;
		long long d = top.first;
		
		if (d > dist[v]) continue;

		for (auto &e : G->adj[v]) {
			int u = e.first;
			long long cost = e.second;

			if (d + cost < dist[u]) {
				dist[u] = d + cost;
				pq.push({dist[u], u});
			}
		}
	}

	return dist;
}

long long dijkstraPair(Graph *G, int s, int t) {
	std::vector<long long> dist(G->n + 1, LONG_LONG_MAX);
	dist[s] = 0;

	std::priority_queue<
		std::pair<long long, int>,
		std::vector<std::pair<long long, int>>,
		std::greater<std::pair<long long, int>>
	> pq;
	pq.push({s, 0});

	while (!pq.empty()) {
		auto top = pq.top(); pq.pop();
		int v = top.second;
		long long d = top.first;

		if (v == t) return dist[v];
		
		if (d > dist[v]) continue;

		for (auto &e : G->adj[v]) {
			int u = e.first;
			long long cost = e.second;

			if (d + cost < dist[u]) {
				dist[u] = d + cost;
				pq.push({dist[u], u});
			}
		}
	}

	return dist[t];
}