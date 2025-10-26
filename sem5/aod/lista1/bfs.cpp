#include <bits/stdc++.h>
#include "graph.cpp"
using namespace std;

#define NIL 0
enum Color {
	WHITE = 0,
	GRAY = 1,
	BLACK = 2
};

void BFS(Graph &G, bool printTree) {
	// translacja na listę sąsiedztwa
	vector<vector<int>> adj(G.n + 1);
	for (auto e : G.E) {
		adj[e.first].push_back(e.second);
		if (!G.directed) adj[e.second].push_back(e.first);
	}

	// sortowanie list, aby zachować porządek
	for (int i = 1; i <= G.n; i++) sort(adj[i].begin(), adj[i].end());

	// implementacja algorytmu z "Intorduction to algorithms" Cormena
	vector<int> color(G.n + 1, WHITE);
	vector<int> d(G.n + 1, INT_MAX);
	vector<int> pi(G.n + 1, NIL);
	
	vector<int> visitOrder;
	
	queue<int> Q;
	for (int s = 1; s <= G.n; s++) {
		if (color[s] == WHITE) {
			color[s] = GRAY;
			d[s] = 0;
			pi[s] = NIL;

			Q.push(s);
			
			while (!Q.empty()) {
				int u = Q.front();
				Q.pop();
				visitOrder.push_back(u);

				for (int v : adj[u]) {
					if (color[v] == WHITE) {
						color[v] = GRAY;
						d[v] = d[u] + 1;
						pi[v] = u;

						Q.push(v);
					}
				}

				color[u] = BLACK;
			}
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

		BFS(G, printTree);
		
		return 0;
	} catch(const string err) {
		cerr << err;
		return -1;
	} 
}