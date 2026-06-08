#include "../CountryData.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>
using namespace filesystem;

int main() {
	create_directories("zad1/data");
	cout << "Created output directory" << endl;

	vector<string> paths = {
		"wi29.tsp",
		"dj38.tsp",
		"qa194.tsp",
		"uy734.tsp",
		"zi929.tsp",
		"mu1979.tsp",
		// "ca4663.tsp",
		// "tz6117.tsp",
		// "eg7146.tsp",
		// "ei8246.tsp",
	};

	ofstream summary("zad1/data/summary.txt");
	
	for (const auto &file : paths) {
		cout << " file: " << file << endl;
		
		cout << "  - loading data" << endl;
		CountryData cd("data/" + file);
		cout << "  - data loaded" << endl;
		cd.print();

		cout << "  - creating output file" << endl;
		ofstream os("zad1/data/" + cd.name + ".txt");
		ofstream os2("zad1/data/" + cd.name + "-2.txt");
		cout << "  - output file created" << endl;

		cout << "  - generating data" << endl;

		pair<int, vector<pair<double,double>>> best;
		best.first = INT_MAX;
		pair<int, vector<pair<double,double>>> best2;
		best2.first = INT_MAX;

		int avgPath = 0, avgPath2 = 0;
		int n = 10;
		for (int i = 0; i < n; i++) {
			cout << "    " << i << "/" << n << endl;
			
			pair<int, vector<pair<double,double>>> temp = cd.geneticSearch();
			pair<int, vector<pair<double,double>>> temp2 = cd.geneticSearch();
			
			if (temp.first < best.first) best = temp;
			avgPath += temp.first;
			if (temp2.first < best2.first) best2 = temp;
			avgPath2 += temp2.first;
		}

		summary << file << endl;
		summary << "avg path: " << (double)avgPath / n << endl;
		summary << "avg path2: " << (double)avgPath2 / n << endl;

		for (int i = 0; i < cd.n; i++) {
			os << best.second[i].first << " " << best.second[i].second << endl;
			os2 << best2.second[i].first << " " << best2.second[i].second << endl;
		}
	}

	return 0;
}