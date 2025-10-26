#include <bits/stdc++.h>
#include "graph.cpp"
using namespace std;

#define NIL 0
enum Color {
	WHITE = 0,
	GRAY = 1,
	BLACK = 2
};

void DFS(Graph &G, bool printTree) {
	// translacja na listę sąsiedztwa
	vector<vector<int>> adj(G.n + 1);
	for (auto e : G.E) {
		adj[e.first].push_back(e.second);
		if (!G.directed) adj[e.second].push_back(e.first);
	}

	// sortowanie list, aby zachować porządek
	for (int i = 1; i <= G.n; i++) sort(adj[i].begin(), adj[i].end());

	// implementacja algorytmu z "Introduction to algorithms" Cormena
	vector<int> color(G.n + 1, WHITE);
	vector<int> pi(G.n + 1, NIL);
	vector<int> d(G.n + 1, INT_MAX);
	vector<int> f(G.n + 1, 0);
	int time = 0;
	
	vector<int> visitOrder;
	
	function<void(int)> DFSVisit = [&](int u) {
		time++;
		d[u] = time;
		color[u] = GRAY;

		visitOrder.push_back(u);

		for (int v : adj[u]) {
			if (color[v] == WHITE) {
				pi[v] = u;
				DFSVisit(v);
			}
		}
		color[u] = BLACK;
		time++;
		f[u] = time;
	};

	for (int u = 1; u <= G.n; u++) {
		if (color[u] == WHITE) {
			pi[u] = NIL;
			DFSVisit(u);
		}
	}

	cout << "Kolejnosc odwiedzania:\n";
	if (!visitOrder.empty()) {
		for (int i = 0; i < visitOrder.size(); i++) cout << (i ? " ":"") << visitOrder[i];
		cout << endl;
	}

	if (printTree) {
		cout << "Drzewo BFS:\n";

		bool any = false;
		for (int v = 1; v <= G.n; v++) {
			int p = pi[v];
			if (p != NIL) {
				cout << p << " " << v << endl;
				any = true;
			}
		}

		if (!any) cout << "brak krawedzi\n";
	}
}

int main(int argc, char* argv[]) {
	try {
		Graph G(argc, argv);
		
		bool printTree = false;
		int expArgs = 4 + 2 * G.m;

		string treeFlag = "T";
		if (expArgs < argc && !treeFlag.compare(argv[expArgs])) printTree = true;

		DFS(G, printTree);
		
		return 0;
	} catch(const string err) {
		cerr << err;
		return -1;
	} 
}