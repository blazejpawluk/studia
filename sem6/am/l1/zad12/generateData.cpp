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

		cout << "  - generating data" << endl;
		vector<int> results;
		results.reserve(1000);
		vector<int> bestPath;
		int bestSum = 1000000000;
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
			double d = sqrt(dx*dx + dy*dy);
			sum += round(d);

			results.push_back(sum);
			if (sum < bestSum) {
				bestSum = sum;
				bestPath = path;
			}
		}
		cout << "  - data generated" << endl;

		double avgMin10 = 0.0;
		for (int g = 0; g < 100; g++) {
			int groupMin = 1000000000;
			for (int k = g*10; k < g*10 + 10; k++) groupMin = min(groupMin, results[k]);
			avgMin10 += groupMin;
		}
		avgMin10 /= 100.0;

		double avgMin50 = 0.0;
		for (int g = 0; g < 20; g++) {
			int groupMin = 1000000000;
			for (int k = g*50; k < g*50 + 50; k++) groupMin = min(groupMin, results[k]);
			avgMin50 += groupMin;
		}
		avgMin50 /= 20.0;

		cout << "  - average of minima for each 10 draws: " << avgMin10 << endl;
		cout << "  - average of minima for each 50 draws: " << avgMin50 << endl;
		cout << "  - minimal value for 1000 draws: " << bestSum << endl;

		for (int i = 0; i < (int)bestPath.size(); i++) {
			os << cd.P[bestPath[i]].first << " " << cd.P[bestPath[i]].second << endl;
		}
	}

	return 0;
}