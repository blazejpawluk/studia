#include "../CountryData.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>
#include <climits>
using namespace filesystem;

int main() {
	create_directories("zad1/data");
	cout << "Created output directory" << endl;

	vector<string> small_paths = {
		"wi29.tsp",
		"dj38.tsp",
		"qa194.tsp",
		"uy734.tsp",
		"zi929.tsp"
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

	struct SAParams { double T; double alpha; int stopEpochs; };
	vector<SAParams> grid = {
		{500, 0.95,  50},
		{500, 0.99,  50},
		{2000, 0.95,  50},
		{2000, 0.99,  50},
		{2000, 0.95, 150},
		{2000, 0.99, 150},
		{10000, 0.95, 150},
		{10000, 0.99, 150},
	};

	double bestT = 2000;
	double bestAlpha = 0.99;
	int bestStopEpoch = 50;
	double bestAvgAll = 1e18;

	ofstream params("zad1/data/parameters.txt");
	params << "=== Simulated Annealing - testowanie parametrow ===" << endl;
	params << "Liczba prob na konfiguracje: 5,  epochLen = n" << endl << endl;

	for (const auto &file : small_paths) {
		cout << " [param search] file: " << file << endl;
		CountryData cd("data/" + file);
		cd.print();

		params << "Plik: " << file << " (n=" << cd.n << ")" << endl;
		params << "T\talpha\tstopEpochs\tavg\tbest" << endl;

		for (const auto &p : grid) {
			double totalPath = 0;
			int    localBest = INT_MAX;
			for (int i = 0; i < 5; i++) {
				vector<int> path = cd.randomPath();
				auto res = cd.simulatedAnnealing(path, p.T, p.alpha, cd.n, p.stopEpochs);
				totalPath += res.first;
				if (res.first < localBest) localBest = res.first;
			}
			double avg = totalPath / 5.0;
			params << p.T << "\t" << p.alpha << "\t" << p.stopEpochs
			       << "\t" << avg << "\t" << localBest << endl;

			if (avg < bestAvgAll) {
				bestAvgAll    = avg;
				bestT         = p.T;
				bestAlpha     = p.alpha;
				bestStopEpoch = p.stopEpochs;
			}
		}
		params << endl;
	}

	params << "Najlepsze parametry: T=" << bestT
	       << "  alpha=" << bestAlpha
	       << "  stopEpochs=" << bestStopEpoch << endl;
	params.close();

	cout << "Najlepsze parametry: T=" << bestT
	     << "  alpha=" << bestAlpha
	     << "  stopEpochs=" << bestStopEpoch << endl;

	// --- główna symulacja: 100 prób dla każdego grafu ---
	ofstream summary("zad1/data/summary.txt");
	summary << "=== Simulated Annealing - wyniki ===" << endl;
	summary << "Parametry: T=" << bestT
	        << "  alpha=" << bestAlpha
	        << "  epochLen=n  stopEpochs=" << bestStopEpoch << endl << endl;

	for (const auto &file : all_paths) {
		cout << " file: " << file << endl;
		CountryData cd("data/" + file);
		cd.print();

		ofstream os("zad1/data/" + cd.name + ".txt");

		pair<int, vector<pair<double,double>>> best;
		best.first = INT_MAX;
		long long avgPath = 0;

		for (int i = 0; i < 100; i++) {
			if (i % 10 == 0) cout << "    " << i << "/100" << endl;
			vector<int> path = cd.randomPath();
			auto res = cd.simulatedAnnealing(path, bestT, bestAlpha, cd.n, bestStopEpoch);
			if (res.first < best.first) best = res;
			avgPath += res.first;
		}

		summary << file << endl;
		summary << "best: " << best.first << endl;
		summary << "avg:  " << (double)avgPath / 100.0 << endl << endl;

		for (const auto &pt : best.second)
			os << pt.first << " " << pt.second << endl;
	}

	return 0;
}