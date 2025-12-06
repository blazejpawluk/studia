#include <limits>
#include "../../lib/Graph.hpp"
#include "../../lib/alg/dial.hpp"

const long long INF = std::numeric_limits<long long>::max() / 4;

std::vector<long long> dial(Graph *G, int s) {
	std::vector<long long> dist(G->n + 1, INF);
	dist[s] = 0;

	std::vector<int> bucketTop(G->maxCost + 1, -1);
	std::vector<int> nextInBucket(G->n + 1, -1);
	std::vector<int> prevInBucket(G->n + 1, -1);
	std::vector<int> bucketOf(G->n + 1, -1);
	
	int elements = 0;

	auto removeFromBucket = [&](int v) {
		int b = bucketOf[v];
		if (b == -1) return;

		int prev = prevInBucket[v], next = nextInBucket[v];

		if (prev != -1) nextInBucket[prev] = next;
		else bucketTop[b] = next;
		
		if (next != -1) prevInBucket[next] = prev;

		nextInBucket[v] = -1;
		prevInBucket[v] = -1;
		bucketOf[v] = -1;

		elements--;
	};

	auto putInBucket = [&](int v, long long d) {
		int b = d % (G->maxCost + 1);
		if (bucketOf[v] != -1) removeFromBucket(v);

		int previousTop = bucketTop[b];
		nextInBucket[v] = previousTop;
		prevInBucket[v] = -1;

		if (previousTop != -1) prevInBucket[previousTop] = v;
		bucketTop[b] = v;
		bucketOf[v] = b;

		elements++;
	};

	putInBucket(s, 0LL);
	int i = 0;

	while (elements > 0) {
		while (bucketTop[i] == -1) i = (i + 1) % (G->maxCost + 1);

		int v = bucketTop[i];
		removeFromBucket(v);

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
	std::vector<long long> dist(G->n + 1, INF);
	dist[s] = 0;

	std::vector<int> bucketTop(G->maxCost + 1, -1);
	std::vector<int> nextInBucket(G->n + 1, -1);
	std::vector<int> prevInBucket(G->n + 1, -1);
	std::vector<int> bucketOf(G->n + 1, -1);
	
	int elements = 0;

	auto removeFromBucket = [&](int v) {
		int b = bucketOf[v];
		if (b == -1) return;

		int prev = prevInBucket[v], next = nextInBucket[v];

		if (prev != -1) nextInBucket[prev] = next;
		else bucketTop[b] = next;
		
		if (next != -1) prevInBucket[next] = prev;

		nextInBucket[v] = -1;
		prevInBucket[v] = -1;
		bucketOf[v] = -1;

		elements--;
	};

	auto putInBucket = [&](int v, long long d) {
		int b = d % (G->maxCost + 1);
		if (bucketOf[v] != -1) removeFromBucket(v);

		int previousTop = bucketTop[b];
		nextInBucket[v] = previousTop;
		prevInBucket[v] = -1;

		if (previousTop != -1) prevInBucket[previousTop] = v;
		bucketTop[b] = v;
		bucketOf[v] = b;

		elements++;
	};

	putInBucket(s, 0LL);
	int i = 0;

	while (elements > 0) {
		while (bucketTop[i] == -1) i = (i + 1) % (G->maxCost + 1);

		int v = bucketTop[i];
		removeFromBucket(v);

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