#include "../CountryData.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>
using namespace filesystem;

int main() {
	create_directories("zad4/data");
	cout << "Created output directory" << endl;
	
	for (const auto &entry : directory_iterator("data")) {
		string file = entry.path().filename().string();

		cout << " file: " << file << endl;
		
		cout << "  - loading data" << endl;
		CountryData cd("data/" + file);
		cout << "  - data loaded" << endl;
		cd.print();

		cout << "  - creating output file" << endl;
		ofstream os("zad4/data/" + cd.name + ".txt");
		cout << "  - output file created" << endl;

		cout << "  - calculating TSP" << endl;
		pair<double, vector<pair<double,double>>> tsp = cd.tspFromMSTCoordinates();
		cout << "  - calculated" << endl;

		cout << " > wage: " << tsp.first << endl;

		for (pair<double,double> edge : tsp.second)
			os << edge.first << " " << edge.second << endl;
	}

	return 0;
}