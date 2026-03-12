#include "../CountryData.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>
using namespace filesystem;

int main() {
	create_directories("zad3/data");
	cout << "Created output directory" << endl;
	
	for (const auto &entry : directory_iterator("data")) {
		string file = entry.path().filename().string();

		cout << " file: " << file << endl;
		
		cout << "  - loading data" << endl;
		CountryData cd("data/" + file);
		cout << "  - data loaded" << endl;
		cd.print();

		cout << "  - creating output file" << endl;
		ofstream os("zad3/data/" + cd.name + ".txt");
		cout << "  - output file created" << endl;

		cout << "  - calculating MST" << endl;
		pair<double, vector<pair<pair<double,double>, pair<double,double>>>> mst = cd.minimalSpanningTree();
		cout << "  - calculated" << endl;

		cout << " > wage: " << mst.first << endl;

		for (pair<pair<double,double>, pair<double,double>> edge : mst.second)
			os << edge.first.first << " " << edge.first.second << " " << edge.second.first << " " << edge.second.second << endl;
	}

	return 0;
}