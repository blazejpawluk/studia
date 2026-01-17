#include <iostream>
#include <string>
#include <chrono>
#include "Graph.hpp"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {
	// number of arguments
	if (argc < 3) {
		cerr << "ERROR: wrong number of arguments. Usage: ./main --size k [--printFlow].\n";
		return 1;
	} else if (argc > 4) {
		cerr << "ERROR: wrong number of arguments. Usage: ./main --size k [--printFlow].\n";
		return 2;
	}
	
	// check "--size" flag
	if (string(argv[1]) != "--size") {
		cerr << "ERROR: unknown flag : '" << argv[1] << "'. Usage: ./main --size k [--printFlow].\n";
		return 3;
	}
	
	// read value of "--size" flag
	int k;
	try {
		k = stoi(argv[2]);
		if (k < 1 || k > 16) throw range_error("invalid range");
	} catch (invalid_argument &e) {
		cerr << "ERROR: invalid argument for '--size' - expected integer in range [1,16].\n";
		return 4;
	} catch (range_error &e) {
		cerr << "ERROR: invalid value of integer in '--size' - expected integer in range [1,16].\n";
		return 5;
	}
	
	// read "--printFlow" flag
	bool pF;
	if (argc == 3) pF = false;
	else if (argc == 4 && string(argv[3]) == "--printFlow") pF = true; 
	else {
		cerr << "ERROR: unknown flag: '" << argv[3] << "'. Usage: ./main --size k [--printFlow].\n";
		return 6;
	} 
	
	// input summary
	cout << "========= INPUT =========\n";
	cout << "Performing algorithm for:\n";
	cout << " k: " << k << '\n';
	cout << " printFlow: " << (pF ? "yes" : "no") << '\n';
	cout << "=========================\n"; 
	
	auto t0 = high_resolution_clock::now(); 
	
	// generate graph
	// cout << "Generating graph...\n";
	HyperCube hc(k);
	// cout << "Graph created.\n\n";
	hc.print();
	
	// execute algorithm
	// cout << "Performing algorithm...";
	int f = hc.EdmondsKarp(0, (1 << k) - 1);
	// cout << "Algorithm finsihed.\n\n";
	
	auto t1 = high_resolution_clock::now();
	auto elapsed = duration_cast<milliseconds>(t1-t0).count();
	
	// write results
	cout << "\n========= OUTPUT =========\n";
	cout << "max flow: " << f << '\n';
	if (pF) {
		cout << "--------------------------\n";
		hc.printFlow();
	}
	
	cout << "======== OUTPUT P2 ========\n";
	cerr << " execution time: " << elapsed << '\n';
	cerr << "augmentic paths: " << hc.getAugmentingPaths() << endl;
	
	return 0;
}