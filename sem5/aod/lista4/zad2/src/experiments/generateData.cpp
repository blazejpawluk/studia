#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include "../Graph.hpp"

using namespace std;
using namespace chrono;


int main() {
	filesystem::create_directories("output");

	ofstream file("output/results.csv");
	file << "k,i,run,time_us,mm\n";

	const int RUNS = 10;

	for (int k = 3; k <= 10; ++k) {
		for (int i = 1; i <= k; ++i) {
			for (int run = 1; run <= RUNS; ++run) {

				auto start = high_resolution_clock::now();

				BiPartite bp(k, i);
				bp.EdmondsKarp(0, bp.n - 1);
				int mm = bp.flowVal(0);

				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start).count();

				file << k << ","
					<< i << ","
					<< run << ","
					<< duration << ","
					<< mm << "\n";
			}
		}
	}

	cout << "Dane zapisane do output/results.csv\n";
	return 0;
}