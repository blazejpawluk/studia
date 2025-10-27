#include <bits/stdc++.h>
#include "graph.cpp"
using namespace std;

void bipartite(Graph &G) {
	bool selfLoop = false;

	// translacja na listę sąsiedztwa
	vector<vector<int>> adj(G.n + 1);
	for (auto e : G.E) {
		adj[e.first].push_back(e.second);
		if (!G.directed) adj[e.second].push_back(e.first);
		if (e.first == e.second) selfLoop = true;
	}

	// sortowanie list, aby zachować porządek
	for (int i = 1; i <= G.n; i++) {
		sort(adj[i].begin(), adj[i].end());
		adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
	}

	if (selfLoop) {
		cout << "Graf nie jest dwudzielny.\n";
		return;
	}

	// zmodyfikowany BFS
	// -1 - brak koloru; 0,1 - kolory, oznaczajace czy naleza do V0 czy V1
	vector<int> color(G.n+1, -1);
	vector<bool> visited(G.n+1, false);
	bool valid = true;

	queue<int> Q;
	for (int s = 1; s <= G.n; s++) {
		if (color[s] == -1) {
			color[s] = 0;
			Q.push(s);
			while (!Q.empty() && valid) {
				int u = Q.front();
				Q.pop();

				vector<int> changed;
				for (int v : adj[u]) {
					if (color[v] == -1) {
						changed.push_back(v);
						visited[v] = true;

						color[v] = 1 - color[u];
						Q.push(v);
					} else if (color[v] == color[u]) {
						if (!visited[u]) {
							color[u] = 1 - color[u];
							visited[u] = true;
							for (int w : changed) color[w] = 1 - color[w];
							changed.clear();
						} else {
							// 2 sprawdzone wierzcholki, ktore maja krawedz sa w tym samym zbiorze - graf nie jest dwudzielny
							valid = false;
							break;
						}
					}
				}
			}
		}

		// czyszczenie kolejki jesli wczesniej przerwiemy 
		while (!Q.empty()) Q.pop();
	}

	if (!valid) cout << "Graf nie jest dwudzielny.\n";
	else {
		cout << "Graf jest dwudzielny.\n";

		if (G.n <= 200) {
			vector<int> V0, V1;
			for (int v = 1; v <= G.n; v++) {
				if (color[v] == 1) V1.push_back(v);
				else V0.push_back(v);
				// jesli nie ma koloru to przydzielamy go do V0
			}
	
			cout << "V0:\n";
			for (int i = 0; i < V0.size(); i++) cout << (i ? " ":"") << V0[i];
	
			cout << "\nV1:\n";
			for (int i = 0; i < V1.size(); i++) cout << (i ? " ":"") << V1[i];

			cout << endl;
		}
	}
}

// int main(int argc, char* argv[]) {
// 	try {
// 		Graph G(argc, argv);

// 		bipartite(G);

// 		return 0;
// 	} catch(const string err) {
// 		cerr << err;
// 		return -1;
// 	}
// }