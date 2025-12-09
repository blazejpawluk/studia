#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../lib/Graph.hpp"
#include "../lib/Parser.hpp"
#include "../lib/alg/dijkstra.hpp"
#include "../lib/alg/dial.hpp"
#include "../lib/alg/radixheap.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::ofstream paths("outputs/raw/paths.txt", std::ios::app);

void executeTest(std::string family) {
	try {
		std::cout << family << std::endl;

		int maxC = -1;
		Graph *maxG = nullptr;

		std::ofstream ofs("outputs/raw/" + family + ".txt");
		for (auto &entry : std::filesystem::directory_iterator("inputs/" + family)) {
			std::string filename = entry.path().filename().string();
			std::cout << "\t" << filename << std::endl;

			Graph* G = parseGraph("inputs/" + family + "/" + filename);
			if (G->maxCost > maxC) {maxC = G->maxCost; maxG = G;}
			std::cout << "\t\tgraph created" << std::endl;

			ofs << filename.substr(0, filename.size()-5) << " ";
			
			std::cout << "\t\tss - low index" << std::endl;

			auto start = std::chrono::high_resolution_clock::now();
			dijkstra(G, 1);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> duration = end - start;
			ofs << duration.count() << " ";
			
			start = std::chrono::high_resolution_clock::now();
			dial(G, 1);
			end = std::chrono::high_resolution_clock::now();
			duration = end - start;
			ofs << duration.count() << " ";
			
			start = std::chrono::high_resolution_clock::now();
			radixheap(G, 1);
			end = std::chrono::high_resolution_clock::now();
			duration = end - start;
			ofs << duration.count() << " ";
			
			std::cout << "\t\tss - random average" << std::endl;
			
			std::uniform_int_distribution<> dis(1, G->n);
			std::vector<double> total(3, 0);
			for (int i = 0; i < 5; i++) {
				int v = dis(gen);
				
				start = std::chrono::high_resolution_clock::now();
				dijkstra(G, v);
				end = std::chrono::high_resolution_clock::now();
				duration = end - start;
				total[0] += duration.count();
				
				start = std::chrono::high_resolution_clock::now();
				dial(G, v);
				end = std::chrono::high_resolution_clock::now();
				duration = end - start;
				total[1] += duration.count();
				
				start = std::chrono::high_resolution_clock::now();
				radixheap(G, v);
				end = std::chrono::high_resolution_clock::now();
				duration = end - start;
				total[2] += duration.count();
			}
			
			ofs << total[0] / 5.0 << " ";
			ofs << total[1] / 5.0 << " ";
			ofs << total[2] / 5.0 << " ";
			ofs << std::endl;
		}
		
		std::cout << "\t\tp2p - low-high index" << std::endl;
		
		paths << family << " " << 1 << " " << maxG->n << " " << dijkstraPair(maxG, 1, maxG->n) << std::endl;
		paths << family << " " << 1 << " " << maxG->n << " " << dialPair(maxG, 1, maxG->n) << std::endl;
		paths << family << " " << 1 << " " << maxG->n << " " << radixheapPair(maxG, 1, maxG->n) << std::endl;

		std::cout << "\t\tp2p - random" << std::endl;
		
		std::uniform_int_distribution<> dis(1, maxG->n);
		for (int i = 0; i < 4; i++) {
			int v = dis(gen), u;
			do {u = dis(gen);} while (v == u);
			
			paths << family << " " << v << " " << u << " " << dijkstraPair(maxG, v, u) << std::endl;
			paths << family << " " << v << " " << u << " " << dialPair(maxG, v, u) << std::endl;
			paths << family << " " << v << " " << u << " " << radixheapPair(maxG, v, u) << std::endl;

		}
		
		std::cout << "\tdone" << std::endl;
	} catch (const std::exception &e) {std::cerr << e.what() << std::endl;}
}

int main() {
	executeTest("Random4-n");
	executeTest("Random4-C");

	executeTest("Long-n");
	executeTest("Square-n");

	executeTest("USA-road-t");

	return 0;
}