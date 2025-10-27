#include <bits/stdc++.h>
#include "graph.cpp"
using namespace std;

void SCC(Graph &G) {
	// translacja na listę sąsiedztwa
	vector<vector<int>> adj(G.n + 1);
	vector<vector<int>> revadj(G.n + 1);
	for (auto e : G.E) {
		adj[e.first].push_back(e.second);
		if (!G.directed) {
			adj[e.second].push_back(e.first);
			revadj[e.first].push_back(e.second);
		} else revadj[e.second].push_back(e.first);
	}

	// sortowanie list, aby zachować porządek
	for (int i = 1; i <= G.n; i++) {
		sort(adj[i].begin(), adj[i].end());
		sort(revadj[i].begin(), revadj[i].end());
	}

	// implementacja algorytmu Korasaju
	vector<bool> visited(G.n+1, false);
	vector<int> L;

	// wersja rekurencyjna nie dziala dla n rzedu 10^5
	// function<void(int)> Visit = [&](int u) {
	// 	if (!visited[u]) {
	// 		visited[u] = true;
	// 		for (int v : adj[u]) Visit(v);
	// 		L.push_back(u);
	// 	}
	// };

	// for (int u = 1; u <= G.n; u++) Visit(u);
	// reverse(L.begin(), L.end());

	// vector<vector<int>> assignment(G.n+1);
	// vector<bool> assigned(G.n+1, false);

	// function<void(int, int)> Assign = [&](int u, int root) {
	// 	if(!assigned[u]) {
	// 		assigned[u] = true;
	// 		assignment[root].push_back(u);
	// 		for (int v : adj[u]) Assign(v, root);
	// 	}
	// };

	// for (int u : L) Assign(u, u);

	// wersja iteracyjna 
	// Visit iteracyjnie
	for (int s = 1; s <= G.n; s++) {
		if (!visited[s]) {
			vector<pair<int, int>> st;
			st.push_back({s, 0});
			while (!st.empty()) {
				int u = st.back().first;
				int &it = st.back().second;
				if (!visited[u]) visited[u] = true;
				if (it < adj[u].size()) {
					int v = adj[u][it++];
					if (!visited[v]) st.push_back({v, 0});
				} else {
					L.push_back(u);
					st.pop_back();
				}
			}
		}
	}

	reverse(L.begin(), L.end());

	vector<vector<int>> assignment(G.n+1);
	vector<bool> assigned(G.n+1, false);
	
	// Assign iteracyjnie
	for (int r : L) {
		if (!assigned[r]) {
			vector<int> st;
			st.push_back(r);
			while (!st.empty()) {
				int u = st.back();
				st.pop_back();
				if (!assigned[u]) {
					assigned[u] = true;
					assignment[r].push_back(u);
					for (int v : revadj[u]) {
						if (!assigned[v]) st.push_back(v);
					}
				}
			}
		}
	}

	vector<vector<int>> result;
	for(vector<int> a : assignment) {
		if (!a.empty()) result.push_back(a);
	}

	cout << "Liczba silnie spojnych skladowych: " << result.size() << endl;

	cout << "Liczba wierzcholkow w silnie spojnych skladowych:\n";
	for (int i = 0; i < result.size(); i++) cout << (i ? " ":"") << result[i].size();
	cout << endl;

	if (G.n <= 200) {
		cout << "Listy wierzcholkow skladowych:\n";
		for (vector<int> v : result) {
			for (int i = 0; i < v.size(); i++) cout << (i ? " ":"") << v[i];
			cout << endl;
		}
	}
}

// int main(int argc, char* argv[]) {
// 	try {
// 		Graph G(argc, argv);

// 		SCC(G);

// 		return 0;
// 	} catch(const string err) {
// 		cerr << err;
// 		return -1;
// 	}
// }