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
std::ofstream paths("outputs/raw/paths.txt");

void executeTest(std::string family) {
	try {
		std::cout << family << std::endl;

		int maxC = -1;
		Graph *maxG;

		std::ofstream ofs("outputs/raw/" + family + ".txt");
		for (auto &entry : std::filesystem::directory_iterator("inputs/" + family)) {
			std::string filename = entry.path().filename().string();
			std::cout << "\t" << filename << std::endl;

			Graph* G = parseGraph("inputs/" + family + "/" + filename);
			if (G->maxCost > maxC) {maxC = G->maxCost; maxG = G;}
			std::cout << "\t\tgraph created" << std::endl;

			ofs << filename.substr(0, filename.size()-5) << " ";
			
			std::cout << "\t\tss - low index" << std::endl;

			try {
				auto start = std::chrono::high_resolution_clock::now();
				dijkstra(G, 1);
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> duration = end - start;
				ofs << duration.count() << " ";
			} catch (const std::exception &e) {std::cerr << "dijkstra: " << e.what() << std::endl;}
			catch (...) {std::cerr << "dijkstra: unknown" << std::endl;}
			std::cout << "dijkstra\n";
			
			try {
				auto start = std::chrono::high_resolution_clock::now();
				dial(G, 1);
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> duration = end - start;
				ofs << duration.count() << " ";
			} catch (const std::exception &e) {std::cerr << "dial: " << e.what() << std::endl;}
			catch (...) {std::cerr << "dial: unknown" << std::endl;}
			std::cout << "dial\n";
			
			try {
				auto start = std::chrono::high_resolution_clock::now();
				radixheap(G, 1);
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> duration = end - start;
				ofs << duration.count() << " ";
			} catch (const std::exception &e) {std::cerr << "radixheap: " << e.what() << std::endl;}
			catch (...) {std::cerr << "radixheap: unknown" << std::endl;}
			std::cout << "radixheap\n";
			
			std::cout << "\t\tss - random average" << std::endl;
			
			std::uniform_int_distribution<> dis(1, G->n);
			std::vector<double> total(3, 0);
			for (int i = 0; i < 5; i++) {
				int v = dis(gen);
				
				try {
					auto start = std::chrono::high_resolution_clock::now();
					dijkstra(G, v);
					auto end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double, std::milli> duration = end - start;
					ofs << duration.count() << " ";
				} catch (const std::exception &e) {std::cerr << "dijkstra: " << e.what() << std::endl;}
				catch (...) {std::cerr << "dijkstra: unknown" << std::endl;}
				
				try {
					auto start = std::chrono::high_resolution_clock::now();
					dial(G, v);
					auto end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double, std::milli> duration = end - start;
					ofs << duration.count() << " ";
				} catch (const std::exception &e) {std::cerr << "dial: " << e.what() << std::endl;}
				catch (...) {std::cerr << "dial: unknown" << std::endl;}
				
				try {
					auto start = std::chrono::high_resolution_clock::now();
					radixheap(G, v);
					auto end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double, std::milli> duration = end - start;
					ofs << duration.count() << " ";
				} catch (const std::exception &e) {std::cerr << "radixheap: " << e.what() << std::endl;}
				catch (...) {std::cerr << "radixheap: unknown" << std::endl;}
			}
			
			ofs << total[0] / 5.0 << " ";
			ofs << total[1] / 5.0 << " ";
			ofs << total[2] / 5.0 << " ";
			ofs << std::endl;
		}
		
		paths << family << " ";
		
		std::cout << "\t\tp2p - low-high index" << std::endl;
		
		try {paths << dijkstraPair(maxG, 1, maxG->n) << " ";}
		catch (const std::exception &e) {std::cerr << "dijkstra: " << e.what() << std::endl;}
		catch (...) {std::cerr << "dijkstra: unknown" << std::endl;}
		
		try {paths << dialPair(maxG, 1, maxG->n) << " ";}
		catch (const std::exception &e) {std::cerr << "dial: " << e.what() << std::endl;}
		catch (...) {std::cerr << "dial: unknown" << std::endl;}
		
		try {paths << radixheapPair(maxG, 1, maxG->n) << " ";}
		catch (const std::exception &e) {std::cerr << "radixheap: " << e.what() << std::endl;}
		catch (...) {std::cerr << "radixheap: unknown" << std::endl;}
		
		std::cout << "\t\tp2p - random" << std::endl;
		
		std::uniform_int_distribution<> dis(1, maxG->n);
		for (int i = 0; i < 4; i++) {
			int v = dis(gen), u;
			do {u = dis(gen);} while (v == u);
			
			try {paths << dijkstraPair(maxG, v, u) << " ";}
			catch (const std::exception &e) {std::cerr << "dijkstra: " << e.what() << std::endl;}
			catch (...) {std::cerr << "dijkstra: unknown" << std::endl;}
			
			try {paths << dialPair(maxG, v, u) << " ";}
			catch (const std::exception &e) {std::cerr << "dial: " << e.what() << std::endl;}
			catch (...) {std::cerr << "dial: unknown" << std::endl;}
			
			try {paths << radixheapPair(maxG, v, u) << " ";}
			catch (const std::exception &e) {std::cerr << "radixheap: " << e.what() << std::endl;}
			catch (...) {std::cerr << "radixheap: unknown" << std::endl;}
		}
		paths << std::endl;
		
		std::cout << "\t\tdone" << std::endl;
	} catch (const std::exception &e) {std::cerr << "global: " << e.what() << std::endl;}
	catch (...) {std::cerr << "global unknown" << std::endl;}
}

int main() {
	executeTest("Random4-n");
	executeTest("Random4-C");

	executeTest("Long-n");
	executeTest("Square-n");

	executeTest("Long-C");
	executeTest("Square-C");

	executeTest("USA-road-t");

	return 0;
}