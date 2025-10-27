#include <bits/stdc++.h>
#include "graph.cpp"
using namespace std;

#define NIL 0
enum Color {
	WHITE = 0,
	GRAY = 1,
	BLACK = 2
};

void TopologicalSort(Graph &G) {
	// translacja na listę sąsiedztwa
	vector<vector<int>> adj(G.n + 1);
	for (auto e : G.E) {
		adj[e.first].push_back(e.second);
		if (!G.directed) adj[e.second].push_back(e.first);
	}

	// sortowanie list, aby zachować porządek
	for (int i = 1; i <= G.n; i++) sort(adj[i].begin(), adj[i].end());

	// DFS z wykrywaniem cykli i sortowaniem
	vector<int> color(G.n + 1, WHITE);
	vector<int> pi(G.n + 1, NIL);
	vector<int> d(G.n + 1, INT_MAX);
	vector<int> f(G.n + 1, 0);
	int time = 0;
	
	vector<int> order;
	bool hasCycle = false;
	
	function<void(int)> DFSVisit = [&](int u) {
		time++;
		d[u] = time;
		color[u] = GRAY;

		for (int v : adj[u]) {
			if (color[v] == WHITE) {
				pi[v] = u;
				DFSVisit(v);
			} else if (color[v] == GRAY) hasCycle = true;
			// wykrycie back edge => cykl
		}
		color[u] = BLACK;
		time++;
		f[u] = time;
		order.push_back(u);
	};

	for (int u = 1; u <= G.n; u++) {
		if (color[u] == WHITE) {
			pi[u] = NIL;
			DFSVisit(u);
		}
	}

	if (hasCycle) cout << "Graf zawiera skierowany cykl.\n";
	else {
		cout << "Graf jest acykliczny.\n";
		if (G.n <= 200) {
			reverse(order.begin(), order.end());
			cout << "Porzadek topologiczny:\n";
			for (int i = 0; i < order.size(); i++) cout << (i ? " ":"") << order[i];
			cout << endl;
		} else cout << "(n > 200)\n";
	}
}

// int main(int argc, char* argv[]) {
// 	try {
// 		Graph G(argc, argv);
		
// 		TopologicalSort(G);
		
// 		return 0;
// 	} catch(const string err) {
// 		cerr << err;
// 		return -1;
// 	} 
// }