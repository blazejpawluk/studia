#include "../../lib/Graph.hpp"
#include "../../lib/alg/radixheap.hpp"

std::vector<long long> radixheap(Graph *G, int s) {
	std::vector<long long> dist(G->n + 1, LONG_LONG_MAX);
	dist[s] = 0;
	
	std::vector<std::vector<std::pair<long long, int>>> bucket(65);
	bucket[0].push_back({0, s});

	long long a = 0;
	while (true) {
		int cur = 0;
		while (cur < 65 && bucket[cur].empty()) cur++;
		if (cur == 65) break;

		if (cur == 0) {
			auto x = bucket[cur].back();
			int v = x.second;
			long long d = x.first;
			bucket[cur].pop_back();

			if (d > dist[v]) continue;

			for (auto &e : G->adj[v]) {
				int u = e.first;
				long long cost = e.second;

				if (dist[u] > d + cost) {
					dist[u] = d + cost;

					long long xorDiff = dist[u] ^ a;
					int b = 0;
					while (xorDiff) {
						b++;
						xorDiff >>= 1;
					}
					bucket[b].push_back({dist[u], u});
				}
			}
		} else {
			long long minInBucket = LONG_LONG_MAX;
			for (auto &p : bucket[cur]) {
				int v = p.second;
				long long d = p.first;

				if (d > dist[v]) continue;
				if (minInBucket > d) minInBucket = d;
			}

			if (minInBucket == LONG_LONG_MAX) {
				bucket[cur].clear();
				continue;
			}

			a = minInBucket;
			for (auto &p : bucket[cur]) {
				int v = p.second;
				long long d = p.first;

				if (d > dist[v]) continue;

				long long xorDiff = dist[v] ^ a;
				int b = 0;
				while (xorDiff) {
					b++;
					xorDiff >>= 1;
				}
				bucket[b].push_back({dist[v], v});
			}
		}
	}

	return dist;
}

long long radixheapPair(Graph *G, int s, int t) {
	std::vector<long long> dist(G->n + 1, LONG_LONG_MAX);
	dist[s] = 0;
	
	std::vector<std::vector<std::pair<long long, int>>> bucket(65);
	bucket[0].push_back({0, s});

	long long a = 0;
	while (true) {
		int cur = 0;
		while (cur < 65 && bucket[cur].empty()) cur++;
		if (cur == 65) break;

		if (cur == 0 || cur == 1) {
			auto x = bucket[cur].back();
			int v = x.second;
			long long d = x.first;
			bucket[cur].pop_back();

			if (v == t) return d;

			if (d > dist[v]) continue;

			for (auto &e : G->adj[v]) {
				int u = e.first;
				long long cost = e.second;

				if (dist[u] > d + cost) {
					dist[u] = d + cost;

					long long xorDiff = dist[u] ^ a;
					int b = 0;
					while (xorDiff) {
						b++;
						xorDiff >>= 1;
					}
					bucket[b].push_back({dist[u], u});
				}
			}
		} else {
			long long minInBucket = LONG_LONG_MAX;
			for (auto &p : bucket[cur]) {
				int v = p.second;
				long long d = p.first;

				if (d > dist[v]) continue;
				if (minInBucket > d) minInBucket = d;
			}

			if (minInBucket == LONG_LONG_MAX) {
				bucket[cur].clear();
				continue;
			}

			a = minInBucket;
			for (auto &p : bucket[cur]) {
				int v = p.second;
				long long d = p.first;

				if (d > dist[v]) continue;

				long long xorDiff = dist[v] ^ a;
				int b = 0;
				while (xorDiff) {
					b++;
					xorDiff >>= 1;
				}
				bucket[b].push_back({dist[v], v});
			}
		}
	}

	return -1;
}