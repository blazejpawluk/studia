#include <iostream>
#include <string>
#include <chrono>
#include "Graph.hpp"
using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {
	// number of arguments
	if (argc < 5) {
		cerr << "ERROR: wrong number of arguments. Usage: ./main --size k --degree i [--printFlow] [--glkp filename].\n";
		return 1;
	} else if (argc > 8) {
		cerr << "ERROR: wrong number of arguments. Usage: ./main --size k --degree i [--printFlow] [--glkp filename].\n";
		return 2;
	}

	// check "--size" flag
	if (string(argv[1]) != "--size") {
		cerr << "ERROR: unknown flag : '" << argv[1] << "'. Usage: ./main --size k --degree i [--printFlow] [--glkp filename].\n";
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

	// check "--degree" flag
	if (string(argv[3]) != "--degree") {
		cerr << "ERROR: unknown flag : '" << argv[1] << "'. Usage: ./main --size k --degree i [--printFlow] [--glkp filename].\n";
		return 6;
	}

	// read value of "--size" flag
	int i;
	try {
		i = stoi(argv[4]);
		if (i < 1 || i > k) 
			throw range_error("invalid range");
	} catch (invalid_argument &e) {
		cerr << "ERROR: invalid argument for '--degree' - expected integer in range [1,k].\n";
		return 7;
	} catch (range_error &e) {
		cerr << "ERROR: invalid value of integer in '--degree' - expected integer in range [1,k].\n";
		return 8;
	}

	// read "--printMatching" and "--glkp" flag
	bool pM, glkp;
	string filename;
	if (argc == 5) {pM = false; glkp = false;}
	else if (string(argv[5]) == "--printMatching") {
		if (argc == 6) {
			pM =  true;
			glkp = false;
		} else if (argc == 7 && string(argv[6]) == "--glkp") {
			cerr << "ERROR: no argument for '--glkp' flag: '" << "'. Usage: ./main --size k [--printMatching] [--glkp filename].\n";
			return 9;
		} else if (string(argv[6]) == "--glkp") {
			pM = true;
			glkp = true;
			filename = string(argv[7]);
		} else {
			cerr << "ERROR: unknown flag: '" << argv[6] << "'. Usage: ./main --size k [--printMatching] [--glkp filename].\n";
			return 10;
		}
	}
	else if (string(argv[5]) == "--glkp") {
		if (argc == 6) {
			cerr << "ERROR: no argument for '--glkp' flag: '" << "'. Usage: ./main --size k [--printMatching] [--glkp filename].\n";
			return 11;
		} if (argc == 7) {
			pM = false;
			glkp = true;
			filename = string(argv[6]);
		} else if (string(argv[7]) == "--printMatching") {
			pM =  true;
			glkp = true;
			filename = string(argv[6]);
		} else {
			cerr << "ERROR: unknown flag: '" << argv[6] << "'. Usage: ./main --size k [--printMatching] [--glkp filename].\n";
			return 12;
		}
	}
	else {
		cerr << "ERROR: unknown flag: '" << argv[5] << "'. Usage: ./main --size k [--printMatching] [--glkp filename].\n";
		return 13;
	}

	// input summary
	cout << "========= INPUT =========\n";
	cout << "Performing algorithm for:\n";
	cout << "              k: " << k << endl;
	cout << "              i: " << i << endl;
	cout << "  printMatching: " << (pM ? "yes" : "no") << endl;
	cout << "=========================\n";
	
	auto t0 = high_resolution_clock::now();
	
	// generate graph
	// cout << "Generating graph...\n";
	BiPartite bp(k, i);
	// cout << "Graph created.\n\n";
	// bp.print();
	
	// execute algorithm
	// cout << "Performing algorithm...\n";
	bp.EdmondsKarp(0, bp.n-1);
	int mm = bp.flowVal(0);
	// cout << "Algorithm finsihed.\n\n";
	
	auto t1 = high_resolution_clock::now();
	auto elapsed = duration_cast<milliseconds>(t1-t0).count();
	
	// write results
	cout << "\n======== OUTPUT =========\n";
	cout << "   max matching: " << mm << endl;
	if (pM) {
		cout << "--------------------------\n";
		bp.printMatching();
	}
	if (glkp) {
		cout << "--------------------------\n";
		bp.generateCode(filename);
	}
	cout << "======= OUTPUT P2 =======\n";
	cerr << " execution time: " << elapsed << endl;

	return 0;
}