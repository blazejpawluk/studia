#include <bits/stdc++.h>
#include <chrono>
#include <iomanip>

#include "scc.cpp"

using namespace std;
using namespace chrono;

int main() {
	for (int i = 1; i <= 6; i++) {
		string filename = "testy/3/g3-" + to_string(i) + ".txt";
		ifstream infile(filename);

		string arg;
		infile >> arg;
		bool directed = arg == "D";

		int n, m;
		infile >> n >> m;

		vector<pair<int, int>> E;
		for (int i = 0; i < m; i++) {
			int u, v;
			infile >> u >> v;
			E.push_back({u, v});
		}

		infile.close();

		Graph G(directed, n, m, E);

		cout << filename << ": " << endl;
		auto t1 = high_resolution_clock::now();
		SCC(G);
		auto t2 = high_resolution_clock::now();
		duration<double, milli> elapsed = t2 - t1;
		cout << endl << fixed << setprecision(6) << elapsed.count() << " ms\n\n";
	}

	return 0;
}