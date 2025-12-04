#include "Graph.hpp"
#include "Parser.hpp"
#include "Writer.hpp"

int main(int argc, char* argv[]) {
	vector<string> input = parseCommand(argc, argv);

	string algorithm = input[0];
	Graph G = parseGraphInput(input[1]);
	if(input[2] == "ss") {
		vector<int> sources = parseSSInput(input[3]);

		double total = 0.0;
		int n = sources.size();
		if(algorithm == "dijkstra") {
			for(int s : sources) {
				auto start = chrono::high_resolution_clock::now();
				G.DijkstraFull(s);
				auto end = chrono::high_resolution_clock::now();
				chrono::duration<double, std::milli> duration = end - start;
				total += duration.count();
			}
			writeSS(input[3], input[4], algorithm, G.n, G.m, G.minCost, G.maxCost, total/n);
		} else if(algorithm == "dial") {
			for(int s : sources) {
				auto start = chrono::high_resolution_clock::now();
				G.DijkstraFull(s);
				auto end = chrono::high_resolution_clock::now();
				chrono::duration<double, std::milli> duration = end - start;
				total += duration.count();
			}
			writeSS(input[3], input[4], algorithm, G.n, G.m, G.minCost, G.maxCost, total/n);
		} else if(algorithm == "radixheap") {
			for(int s : sources) {
				auto start = chrono::high_resolution_clock::now();
				G.DijkstraFull(s);
				auto end = chrono::high_resolution_clock::now();
				chrono::duration<double, std::milli> duration = end - start;
				total += duration.count();
			}
			writeSS(input[3], input[4], algorithm, G.n, G.m, G.minCost, G.maxCost, total/n);
		}
	} else if(input[2] == "p2p") {
		vector<pair<int,int>> pairs = parseP2PInput(input[3]);

		if(algorithm == "dijkstra") {
			vector<pair<pair<int,int>,int>> results;
			for(pair<int,int> p : pairs) results.push_back({{p.first, p.second}, G.DijkstraTwo(p.first, p.second)});
			writeP2p(input[3], input[4], algorithm, G.n, G.m, G.minCost, G.maxCost, results);
		} else if(algorithm == "dial") {
			vector<pair<pair<int,int>,int>> results;
			for(pair<int,int> p : pairs) results.push_back({{p.first, p.second}, G.DialTwo(p.first, p.second)});
			writeP2p(input[3], input[4], algorithm, G.n, G.m, G.minCost, G.maxCost, results);
		} else if(algorithm == "radixheap") {
			vector<pair<pair<int,int>,int>> results;
			for(pair<int,int> p : pairs) results.push_back({{p.first, p.second}, G.RadixHeapTwo(p.first, p.second)});
			writeP2p(input[3], input[4], algorithm, G.n, G.m, G.minCost, G.maxCost, results);
		}
	}
}