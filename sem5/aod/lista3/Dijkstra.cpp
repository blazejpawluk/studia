#include "lib/Graph.hpp"
#include "lib/Parser.hpp"
#include "lib/Writer.hpp"

int main(int argc, char* argv[]) {
	vector<string> input = parseCommand(argc, argv, "dijkstra");

	Graph G = parseGraphInput(input[1]);
	if(input[2] == "ss") {
		vector<int> sources = parseSSInput(input[3]);

		double total = 0.0;
		int n = sources.size();
		for(int s : sources) {
			auto start = chrono::high_resolution_clock::now();
			G.DijkstraFull(s);
			auto end = chrono::high_resolution_clock::now();
			chrono::duration<double, std::milli> duration = end - start;
			total += duration.count();
		}
		writeSS(input[3], input[4], "dijkstra", G.n, G.m, G.minCost, G.maxCost, total/n);
	} else if(input[2] == "p2p") {
		vector<pair<int,int>> pairs = parseP2PInput(input[3]);

		vector<pair<pair<int,int>,long long>> results;
		for(pair<int,int> p : pairs) results.push_back({{p.first, p.second}, G.DijkstraTwo(p.first, p.second)});
		writeP2p(input[3], input[4], "dijkstra", G.n, G.m, G.minCost, G.maxCost, results);
	}
}