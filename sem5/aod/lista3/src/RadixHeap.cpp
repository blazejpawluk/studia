#include <vector>
#include <string>
#include <chrono>
#include "../lib/Graph.hpp"
#include "../lib/Parser.hpp"
#include "../lib/Writer.hpp"
#include "../lib/alg/radixheap.hpp"

int main(int argc, char* argv[]) {
	std::vector<std::string> input = parseCommand(argc, argv);

	Graph *G = parseGraph(input[1]);

	if (input[0] == "ss") {
		std::vector<int> sources = parseSSFile(input[2]);

		double total = 0.0;
		for (int s : sources) {
			auto start = std::chrono::high_resolution_clock::now();
			radixheap(G, s);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> duration = end - start;
			total += duration.count();
		}

		writeSSOutput("radixheap", input, G, total/sources.size());
	} else if (input[0] == "p2p") {
		std::vector<std::pair<int,int>> pairs = parseP2PFle(input[2]);
		
		std::vector<std::pair<std::pair<int, int>, long long>> results;		
		for (auto p : pairs) {
			long long d = radixheapPair(G, p.first, p.second);
			results.push_back({{p.first, p.second}, d});
		}

		writeP2POutput("radixheap", input, G, results);
	}

	return 0;
}