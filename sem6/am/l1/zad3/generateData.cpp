#include "../CountryData.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>
using namespace filesystem;

int main() {
	create_directories("zad3/data");
	cout << "Created output directory" << endl;

	vector<string> paths = {
		"wi29.tsp",
		"dj38.tsp",
		"qa194.tsp",
		"uy734.tsp",
		"zi929.tsp",
		"mu1979.tsp",
		"ca4663.tsp",
		"tz6117.tsp",
		"eg7146.tsp",
		"ei8246.tsp",
	};

	ofstream summary("zad3/data/summary.txt");
	
	// for (const auto &entry : directory_iterator("data")) {
	for (const auto &file : paths) {
		// string file = entry.path().filename().string();

		cout << " file: " << file << endl;
		
		cout << "  - loading data" << endl;
		CountryData cd("data/" + file);
		cout << "  - data loaded" << endl;
		cd.print();

		cout << "  - creating output file" << endl;
		ofstream os("zad3/data/" + cd.name + ".txt");
		cout << "  - output file created" << endl;

		cout << "  - generating data" << endl;

		pair<int, vector<pair<double,double>>> best;
		best.first = INT_MAX;

		int avgPath = 0;
		int avgSteps = 0;
		auto mst = cd.minimalSpanningTree();

		int iters = (int) ceil(sqrt((double) cd.n));
		for (int i = 0; i < iters; i++) {
			// if (i % 100 == 0) cout << "    " << i << "/" << iters << endl;
			cout << "    " << i << "/" << iters << endl;

			int steps = 0;
			pair<int, vector<pair<double,double>>> temp = cd.localSearchMST(mst.second, steps);
			
			if (temp.first < best.first) best = temp;
			avgPath += temp.first;
			avgSteps += steps;
		}

		summary << file << endl;
		summary << " >  mst cost: " << mst.first << endl;
		summary << " >  avg path: " << (double)avgPath / iters << endl;
		summary << " > avg steps: " << (double)avgSteps / iters << endl << endl;

		for (int i = 0; i < cd.n; i++) {
			os << best.second[i].first << " " << best.second[i].second << endl;
		}
	}

	return 0;
}