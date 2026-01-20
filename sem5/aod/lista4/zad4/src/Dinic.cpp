#include "Graph.hpp"
#include <queue>

bool Graph::BFSlevel(int s, int t) {
	fill(level.begin(), level.end(), -1);
	queue<int> q;
	level[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (const Edge &e : E[u]) {
			int v = e.to;
			int rem = e.capacity - e.flow;
			if (rem > 0 && level[v] == -1) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return level[t] != -1;
}

int Graph::DFSblocking(int u, int t, int pushed) {
	if (pushed == 0) return 0;
	if (u == t) return pushed;
	for (int &cid = ptr[u]; cid < (int)E[u].size(); cid++) {
		Edge &e = E[u][cid];
		int v = e.to;
		int rem = e.capacity - e.flow;
		if (rem > 0 && level[v] == level[u] + 1) {
			int tr = DFSblocking(v, t, min(pushed, rem));
			if (tr > 0) {
				e.flow += tr;
				E[v][e.rev].flow -= tr;
				return tr;
			}
		}
	}
	return 0;
}

int Graph::Dinic(int s, int t) {
	if (s == t) return 0;
	level.assign(n, -1);
	ptr.assign(n, 0);

	int flow = 0;
	while (BFSlevel(s, t)) {
		fill(ptr.begin(), ptr.end(), 0);

		while (int pushed = DFSblocking(s, t, INT_MAX)) {
			flow += pushed;
		}
	}
	return flow;
}