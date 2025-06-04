#include "graph.cpp"
#include "kruskal.cpp"
#include "prim.cpp"

int main() {
	cout << "FULL GRAPH:\n";
	Graph G = generateFullGraph(10);
	for (Edge e : G.E) cout << e.V.first << "-" << e.V.second << ", wage=" << e.w << endl;
	
	cout << "\nKRUSKAL:\n";
	Graph K = Kruskal(G);
	for (Edge e : K.E) cout << e.V.first << "-" << e.V.second << ", wage=" << e.w << endl;
	
	cout << "\nPRIM:\n";
	Graph P = Prim(G);
	for (Edge e : P.E) cout << e.V.first << "-" << e.V.second << ", wage=" << e.w << endl;
	
	return 0;
}