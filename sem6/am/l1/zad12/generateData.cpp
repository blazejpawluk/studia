#include "../CountryData.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>
using namespace filesystem;

int main() {
	create_directories("zad12/data");
	cout << "Created output directory" << endl;

	for (const auto &entry : directory_iterator("data")) {
		string file = entry.path().filename().string();

		cout << " file: " << file << endl;
		
		cout << "  - loading data" << endl;
		CountryData cd("data/" + file);
		cout << "  - data loaded" << endl;
		cd.print();

		cout << "  - creating output file" << endl;
		ofstream os("zad12/data/" + cd.name + ".txt");
		cout << "  - output file created" << endl;

		os << cd.country << endl;
		
		cout << "  - generating data" << endl;
		for (int i = 0; i < 1000; i++) {
			vector<int> path = cd.randomPath();
			int sum = 0;

			for (int i = 0; i < cd.n - 1; i++) {
				double dx = abs(cd.P[path[i]].first - cd.P[path[i+1]].first);
				double dy = abs(cd.P[path[i]].second - cd.P[path[i+1]].second);
				double d = sqrt(dx + dy);
				sum += round(d);
			}
			double dx = abs(cd.P[path[cd.n-1]].first - cd.P[path[0]].first);
			double dy = abs(cd.P[path[cd.n-1]].second - cd.P[path[0]].second);
			double d = sqrt(dx + dy);
			sum += round(d);

			os << sum << endl;
		}
		cout << "  - data generated" << endl;
	}

	return 0;
}