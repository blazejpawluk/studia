// #include "Graph.hpp"
// #include <algorithm>
// #include <cstring>

// bool Graph::BFS(int s, int t) {
// 	fill(parentNode.begin(), parentNode.end(), -1);
// 	fill(parentEdge.begin(), parentEdge.end(), -1);
// 	fill(visited.begin(), visited.end(), 0);
	
// 	q.clear();
// 	q.reserve(n);
// 	int ql = 0;
	
// 	q.push_back(s);
// 	visited[s] = 1;
	
// 	while (ql < (int) q.size()) {
// 		int u = q[ql++];
		
// 		const auto &au = adj[u];
// 		for (int i = 0; i < (int) au.size(); i++) {
// 			const Edge &e = au[i];
// 			int v = e.to;
			
// 			if (!visited[v] && e.cap > 0) {
// 				visited[v] = 1;
// 				parentNode[v] = u;
// 				parentEdge[v] = i;
				
// 				if (v == t) return true;
// 				q.push_back(v);
// 			}
// 		}
// 	}
	
// 	return false;
// }

// int Graph::EdmondsKarp(int s, int t) {
// 	augmentingPaths = 0;
// 	int maxFlow = 0;

// 	constexpr int INF = 1e9;
// 	while (BFS(s, t)) {
// 		cout << augmentingPaths << endl;
// 		int cf = INF;

// 		for (int v = t; v != s; v = parentNode[v]) {
// 			int u = parentNode[v];
// 			int ei = parentEdge[v];
// 			cf = min(cf, adj[u][ei].cap);
// 		}

// 		for (int v = t; v != s; v = parentNode[v]) {
// 			int u = parentNode[v];
// 			int ei = parentEdge[v];

// 			Edge &e = adj[u][ei];
// 			Edge &rev = adj[e.to][e.rev];
			
// 			e.cap -= cf;
// 			rev.cap += cf;
// 		}

// 		maxFlow += cf;
// 		augmentingPaths++;
// 	}

// 	return maxFlow;
// }

#include "Graph.hpp"
#include <queue>
#include <algorithm>

bool Graph::BFS(const vector<vector<int>>& r, int s, int t, vector<int>& path) {
	path.clear();
	parent.assign(n, -1);
	visited.assign(n, 0);
	q.clear(); q.reserve(n);
	int ql = 0;

	visited[s] = 1;
	q.push_back(s);

	while (ql < (int) q.size()) {
		int u = q[ql++];

		const vector<int> &ru = r[u];
		for (int v = 0; v < n; v++) {
			if (!visited[v] && ru[v] > 0) {
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

int Graph::minCF(const vector<int> &p, const vector<vector<int>> &r) {
	int minCf = r[p[0]][p[1]];
	for (int i = 1; i+1 < (int) p.size(); i++) {
		int c = r[p[i]][p[i+1]];
		if (c < minCf) minCf = c;
	}
	return minCf;
}

vector<vector<int>> Graph::EdmondsKarp(int s, int t) {
	vector<vector<int>> f(n, vector<int>(n, 0));
	vector<vector<int>> r = E;
	augmentingPaths = 0;

	vector<int> p;
	while (BFS(r, s, t, p)) {
		int cf = minCF(p, r);

		for (int i = 0; i+1 < (int) p.size(); i++) {
			int u = p[i];
			int v = p[i+1];

			f[u][v] += cf;
			f[v][u] -= cf;

			r[u][v] -= cf;
			r[v][u] += cf;
		}

		augmentingPaths++;
	}

	return f;
}