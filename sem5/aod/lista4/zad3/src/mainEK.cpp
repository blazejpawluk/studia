#include <iostream>
#include <string>
#include <chrono>
#include "Graph.hpp"
using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {
	// number of arguments
	if (argc < 3) {
		cerr << "ERROR: wrong number of arguments. Usage: ./main --size k [--printFlow] [--glkp filename].\n";
		return 1;
	} else if (argc > 6) {
		cerr << "ERROR: wrong number of arguments. Usage: ./main --size k [--printFlow] [--glkp filename].\n";
		return 2;
	}

	// check "--size" flag
	if (string(argv[1]) != "--size") {
		cerr << "ERROR: unknown flag : '" << argv[1] << "'. Usage: ./main --size k [--printFlow] [--glkp filename].\n";
		return 3;
	}

	// read value of "--size" flag
	int k;
	try {
		k = stoi(argv[2]);
		if (k < 1 || k > 16) 
			throw range_error("invalid range");
	} catch (invalid_argument &e) {
		cerr << "ERROR: invalid argument for '--size' - expected integer in range [1,16].\n";
		return 4;
	} catch (range_error &e) {
		cerr << "ERROR: invalid value of integer in '--size' - expected integer in range [1,16].\n";
		return 5;
	}

	// read "--printFlow" and "--glkp" flag
	bool pF, glkp;
	string filename;
	if (argc == 3) {pF = false; glkp = false;}
	else if (string(argv[3]) == "--printFlow") {
		if (argc == 4) {
			pF =  true;
			glkp = false;
		} else if (argc == 5 && string(argv[4]) == "--glkp") {
			cerr << "ERROR: no argument for '--glkp' flag: '" << "'. Usage: ./main --size k [--printFlow] [--glkp filename].\n";
			return 6;
		} else if (string(argv[4]) == "--glkp") {
			pF = true;
			glkp = true;
			filename = string(argv[5]);
		} else {
			cerr << "ERROR: unknown flag: '" << argv[4] << "'. Usage: ./main --size k [--printFlow] [--glkp filename].\n";
			return 7;
		}
	}
	else if (string(argv[3]) == "--glkp") {
		if (argc == 4) {
			cerr << "ERROR: no argument for '--glkp' flag: '" << "'. Usage: ./main --size k [--printFlow] [--glkp filename].\n";
			return 8;
		} if (argc == 5) {
			pF = false;
			glkp = true;
			filename = string(argv[4]);
		} else if (string(argv[5]) == "--printFlow") {
			pF =  true;
			glkp = true;
			filename = string(argv[4]);
		} else {
			cerr << "ERROR: unknown flag: '" << argv[5] << "'. Usage: ./main --size k [--printFlow] [--glkp filename].\n";
			return 9;
		}
	}
	else {
		cerr << "ERROR: unknown flag: '" << argv[3] << "'. Usage: ./main --size k [--printFlow] [--glkp filename].\n";
		return 10;
	}

	// input summary
	cout << "========= INPUT =========\n";
	cout << "Performing algorithm for:\n";
	cout << "          k: " << k << endl;
	cout << "  printFlow: " << (pF ? "yes" : "no") << endl;
	cout << "       glkp: " << (glkp ? "yes" : "no") << endl;
	if (glkp) cout << "   filename: " << filename << endl;
	cout << "=========================\n";
	
	auto t0 = high_resolution_clock::now();

	// generate graph
	// cout << "Generating graph...\n";
	HyperCube hc(k);
	// cout << "Graph created.\n\n";
	// hc.print();

	// execute algorithm
	// cout << "Performing algorithm...\n";
	hc.EdmondsKarp(0, (1 << k) - 1);
	int f = hc.flowVal(0);
	// cout << "Algorithm finsihed.\n\n";

	auto t1 = high_resolution_clock::now();
	auto elapsed = duration_cast<milliseconds>(t1-t0).count();

	// write results
	cout << "\n======== OUTPUT =========\n";
	cout << "       max flow: " << f << endl;
	if (pF) {
		cout << "--------------------------\n";
		hc.printFlow();
	}
	if (glkp) {
		cout << "--------------------------\n";
		hc.generateCode(filename);
	}
	cout << "======= OUTPUT P2 =======\n";
	cerr << " execution time: " << elapsed << endl;
	cerr << "augmentic paths: " << hc.getAugmentingPaths() << endl;

	return 0;
}