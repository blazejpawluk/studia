#include "graph.cpp"
#include "kruskal.cpp"
#include "prim.cpp"
using namespace chrono;

int main() {
	int nMin = 1000;
	int nMax = 5000;
	int step = 500;
	int rep = 50;

	ofstream fileK("results/resultsKruskal.txt");
	ofstream fileP("results/resultsPrim.txt");

	for (int n = nMin; n <= nMax; n += step) {
		cout << n << endl;
		Graph G = generateFullGraph(n);

		for (int i = 0; i < rep; i++) {
			auto start = high_resolution_clock::now();
			Kruskal(G);
			auto finish = high_resolution_clock::now();
			auto elapsed = duration_cast<nanoseconds> (finish - start);
			fileK << n << " " << elapsed.count() << endl;
	
			start = high_resolution_clock::now();
			Prim(G);
			finish = high_resolution_clock::now();
			elapsed = duration_cast<nanoseconds> (finish - start);
			fileP << n << " " << elapsed.count() << endl;
		}
	}

	fileK.close();
	fileP.close();
	return 0;
}