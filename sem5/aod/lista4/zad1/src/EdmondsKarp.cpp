#include "Graph.hpp"
#include <algorithm>
#include <cstring>

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

int Graph::EdmondsKarp(int s, int t) {
	augmentingPaths = 0;
	int maxFlow = 0;

	constexpr int INF = 1e9;
	while (BFS(s, t)) {
		cout << augmentingPaths << endl;
		int cf = INF;

		for (int v = t; v != s; v = parentNode[v]) {
			int u = parentNode[v];
			int ei = parentEdge[v];
			cf = min(cf, adj[u][ei].cap);
		}

		for (int v = t; v != s; v = parentNode[v]) {
			int u = parentNode[v];
			int ei = parentEdge[v];

			Edge &e = adj[u][ei];
			Edge &rev = adj[e.to][e.rev];
			
			e.cap -= cf;
			rev.cap += cf;
		}

		maxFlow += cf;
		augmentingPaths++;
	}

	return maxFlow;
}