#include "Graph.hpp"
#include <queue>
#include <algorithm>

bool Graph::BFS(int s, int t, vector<int>& path) {
	path.clear();
	parent.assign(n, -1);
	visited.assign(n, 0);

	q.clear(); q.reserve(n);
	int ql = 0;

	visited[s] = 1;
	q.push_back(s);

	while (ql < (int) q.size()) {
		int u = q[ql++];

		for (const auto &e : E[u]) {
			int v = e.to, c = e.capacity, f = e.flow;
			if (!visited[v] && c-f > 0) {
				visited[v] = 1;
				parent[v] = u;

				if (v == t) goto FOUND;
				q.push_back(v);
			}
		}
	}
	return false;

FOUND:
	int cur = t;
	while (cur != -1) {
		path.push_back(cur);
		cur = parent[cur];
	}

	reverse(path.begin(), path.end());

	return true;
}

int Graph::findEdge(int u, int v) {
	for (int i = 0; i < (int) E[u].size(); i++) {
		if (E[u][i].to == v) return i;
	}
	return -1;
}

int Graph::minCF(const vector<int> &p) {
	int minCf = INT_MAX;
	for (int i = 0; i+1 < (int) p.size(); i++) {
		int e = findEdge(p[i], p[i+1]);
		int c = E[p[i]][e].capacity - E[p[i]][e].flow;
		if (c < minCf) minCf = c;
	}
	return minCf;
}

void Graph::EdmondsKarp(int s, int t) {
	augmentingPaths = 0;

	vector<int> p;
	while (BFS(s, t, p)) {
		int cf = minCF(p);

		for (int i = 0; i+1 < (int) p.size(); i++) {
			int u = p[i];
			int v = p[i+1];

			int eF = findEdge(u, v);
			int eB = findEdge(v, u);
			E[u][eF].flow += cf;
			E[v][eB].flow -= cf;
		}

		augmentingPaths++;
	}
}