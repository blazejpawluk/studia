#include "../../lib/Graph.hpp"
#include "../../lib/alg/dial.hpp"

std::vector<long long> dial(Graph *G, int s) {
	std::vector<long long> dist(G->n + 1, LONG_LONG_MAX);
	dist[s] = 0;

	int size = 0;
	std::vector<int> bucketTop(G->maxCost + 1, -1);
	std::vector<int> nextInBucket(G->n + 1);
	std::vector<int> prevInBucket(G->n + 1);

	auto putInBucket = [&](int v, long long d) {
		long long bucket = d % (G->maxCost + 1);
		int previousTop = bucketTop[bucket];

		nextInBucket[v] = previousTop;
		prevInBucket[v] = -1;

		if (previousTop != -1) prevInBucket[previousTop] = v;
		bucketTop[bucket] = v;

		size++;
	};

	auto removeFromBucket = [&](int v, long long d) {
		long long bucket = d % (G->maxCost + 1);

		int prev = prevInBucket[v], next = nextInBucket[v];
		if (prev != -1) nextInBucket[prev] = next;
		else bucketTop[bucket] = next;

		if (next != -1) prevInBucket[next] = prev;

		nextInBucket[v] = -1;
		prevInBucket[v] = -1;

		size--;
	};

	putInBucket(s, 0);
	int i = 0;

	while (size > 0) {
		while (bucketTop[i] == -1) i = (i + 1) % (G->maxCost + 1);

		int v = bucketTop[i];
		removeFromBucket(v, dist[v]);

		for (auto &e : G->adj[v]) {
			int u = e.first;
			long long cost = e.second;

			if (dist[u] > dist[v] + cost) {
				dist[u] = dist[v] + cost;
				putInBucket(u, dist[u]);
			}
		}
	}

	return dist;
}

long long dialPair(Graph *G, int s, int t) {
	std::vector<long long> dist(G->n + 1, LONG_LONG_MAX);
	dist[s] = 0;

	int size = 0;
	std::vector<int> bucketTop(G->maxCost + 1, -1);
	std::vector<int> nextInBucket(G->n + 1);
	std::vector<int> prevInBucket(G->n + 1);

	auto putInBucket = [&](int v, long long d) {
		long long bucket = d % (G->maxCost + 1);
		int previousTop = bucketTop[bucket];

		nextInBucket[v] = previousTop;
		prevInBucket[v] = -1;

		if (previousTop != -1) prevInBucket[previousTop] = v;
		bucketTop[bucket] = v;

		size++;
	};

	auto removeFromBucket = [&](int v, long long d) {
		long long bucket = d % (G->maxCost + 1);

		int prev = prevInBucket[v], next = nextInBucket[v];
		if (prev != -1) nextInBucket[prev] = next;
		else bucketTop[bucket] = next;

		if (next != -1) prevInBucket[next] = prev;

		nextInBucket[v] = -1;
		prevInBucket[v] = -1;

		size--;
	};

	putInBucket(s, 0);
	int i = 0;

	while (size > 0) {
		while (bucketTop[i] == -1) i = (i + 1) % (G->maxCost + 1);

		int v = bucketTop[i];
		removeFromBucket(v, dist[v]);

		if (v == t) return dist[v];

		for (auto &e : G->adj[v]) {
			int u = e.first;
			long long cost = e.second;

			if (dist[u] > dist[v] + cost) {
				dist[u] = dist[v] + cost;
				putInBucket(u, dist[u]);
			}
		}
	}

	return dist[t];
}