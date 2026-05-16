#include "../CountryData.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>
#include <climits>
using namespace filesystem;

int main() {
	create_directories("zad2/data");
	cout << "Created output directory" << endl;

	vector<string> small_paths = {
		"wi29.tsp",
		"dj38.tsp",
		"qa194.tsp"
	};

	vector<string> all_paths = {
		"wi29.tsp",
		"dj38.tsp",
		"qa194.tsp",
		"uy734.tsp",
		"zi929.tsp",
		"mu1979.tsp",
		"ca4663.tsp",
		"tz6117.tsp",
		"eg7146.tsp",
		"ei8246.tsp"
	};

	struct TabuParams { int tabuLen; int maxIter; };
	vector<TabuParams> grid = {
		{10, 500},
		{10, 2000},
		{50, 500},
		{50, 2000},
		{100, 500},
		{100, 2000},
	};

	int bestTabuLen = 50;
	int bestMaxIter = 1000;
	double bestAvgAll = 1e18;

	ofstream params("zad2/data/parameters.txt");
	params << "=== Tabu Search - testowanie parametrow ===" << endl;
	params << "Liczba prob na konfiguracje: 5" << endl << endl;

	for (const auto &file : small_paths) {
		cout << " [param search] file: " << file << endl;
		CountryData cd("data/" + file);
		cd.print();

		params << "Plik: " << file << " (n=" << cd.n << ")" << endl;
		params << "tabuLen\tmaxIter\tavg\tbest" << endl;

		for (const auto &p : grid) {
			double totalPath = 0;
			int    localBest = INT_MAX;
			for (int i = 0; i < 5; i++) {
				vector<int> path = cd.randomPath();
				auto res = cd.tabuSearch(path, p.tabuLen, p.maxIter);
				totalPath += res.first;
				if (res.first < localBest) localBest = res.first;
			}
			double avg = totalPath / 5.0;
			params << p.tabuLen << "\t" << p.maxIter
			       << "\t" << avg << "\t" << localBest << endl;

			if (avg < bestAvgAll) {
				bestAvgAll  = avg;
				bestTabuLen = p.tabuLen;
				bestMaxIter = p.maxIter;
			}
		}
		params << endl;
	}

	params << "Najlepsze parametry: tabuLen=" << bestTabuLen
	       << "  maxIter=" << bestMaxIter << endl;
	params.close();

	cout << "Najlepsze parametry: tabuLen=" << bestTabuLen
	     << "  maxIter=" << bestMaxIter << endl;

	ofstream summary("zad2/data/summary.txt");
	summary << "=== Tabu Search - wyniki ===" << endl;
	summary << "Parametry bazowe: tabuLen=" << bestTabuLen
	        << "  maxIter=" << bestMaxIter << " (skalowane dla duzych grafow)" << endl << endl;

	for (const auto &file : all_paths) {
		cout << " file: " << file << endl;
		CountryData cd("data/" + file);
		cd.print();

		ofstream os("zad2/data/" + cd.name + ".txt");

		pair<int, vector<pair<double,double>>> best;
		best.first = INT_MAX;
		long long avgPath = 0;

		for (int i = 0; i < 100; i++) {
			if (i % 10 == 0)
				cout << "    " << i << "/100"
				     << " (tabuLen=" << bestTabuLen
				     << " maxIter=" << bestMaxIter << ")" << endl;
			vector<int> path = cd.randomPath();
			auto res = cd.tabuSearch(path, bestTabuLen, bestMaxIter);
			if (res.first < best.first) best = res;
			avgPath += res.first;
		}

		summary << file << endl;
		summary << "tabuLen=" << bestTabuLen << "  maxIter=" << bestMaxIter << endl;
		summary << "best: " << best.first << endl;
		summary << "avg:  " << (double)avgPath / 100.0 << endl << endl;

		for (const auto &pt : best.second)
			os << pt.first << " " << pt.second << endl;
	}

	return 0;
}