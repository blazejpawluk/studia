#include "CountryData.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <algorithm>

CountryData::CountryData(const string &filename) {
	loadFromFile(filename);
}

string trim(string s) {
	s.erase(
		remove_if(s.begin(), s.end(), 
			[](unsigned char c) {return isspace(c);}
	), s.end());
	return s;
}

void CountryData::loadFromFile(const string &filename) {
	name.clear();
	country.clear();
	n = 0;
	P.clear();
	
	ifstream in(filename);
	string line;
	bool nodes = false;
	bool firstComment = true;
	while (getline(in, line)) {
		int separatorIndex = line.find(':');
		string key, value;
		if (separatorIndex != string::npos) {
			key = line.substr(0, separatorIndex);
			value = line.substr(separatorIndex+1);
		} else {
			key = line;
			value = "";
		}

		if (trim(key) == "NAME") {
			name = value;
		} else if (trim(key) == "COMMENT" && firstComment) {
			firstComment = false;
			istringstream iss(value);
			string token;
			while (iss >> token) country = token;
		} else if (trim(key) == "DIMENSION") {
			n = stoi(value);
			P = vector<pair<double,double>>(n, {0,0});
		} else if (value == "") {
			istringstream iss(key);
			int id; double x, y;
			if (iss >> id >> x >> y) {
				P[id-1] = {x,y};
			}
		}
	}
}

void CountryData::print() {
	cout << "name: " << name << endl;
	cout << "country: " << country << endl;
	cout << "dimension: " << n << endl;
}

vector<int> CountryData::randomPath() {
	vector<int> path(n);
	for (int i = 0; i < n; i++) path[i] = i;
	
	random_device rd;
	mt19937 gen(rd());
	shuffle(path.begin(), path.end(), gen);

	return path;
}

// algorytm prima
pair<double, vector<pair<pair<double,double>, pair<double,double>>>> CountryData::minimalSpanningTree() {
	if (n <= 0) return {0.0, {}};
	vector<double> minDist(n, numeric_limits<double>::infinity());
	vector<int> parent(n, -1);
	vector<char> used(n, false);
	minDist[0] = 0.0;
	for (int i = 0; i < n; i++) {
		int v = -1;
		for (int j = 0; j < n; j++) {
			if (!used[j] && (v == -1 || minDist[j] < minDist[v])) v = j;
		}
		if (v == -1) break;
		used[v] = true;
		for (int to = 0; to < n; to++) {
			if (used[to]) continue;
			double dx = P[v].first - P[to].first;
			double dy = P[v].second - P[to].second;
			double d = sqrt(dx*dx + dy*dy);
			if (d < minDist[to]) {
				minDist[to] = d;
				parent[to] = v;
			}
		}
	}
	double total = 0.0;
	vector<pair<pair<double,double>, pair<double,double>>> edges;
	for (int i = 1; i < n; i++) {
		if (parent[i] != -1) {
			edges.emplace_back(P[parent[i]], P[i]);
			double dx = P[parent[i]].first - P[i].first;
			double dy = P[parent[i]].second - P[i].second;
			total += sqrt(dx*dx + dy*dy);
		}
	}
	return {total, edges};
}