#ifndef CD_HPP
#define CD_HPP

#include <string>
#include <vector>
using namespace std;

class CountryData {
public:
	string name;
	string country;
	int n;
	vector<pair<double,double>> P;

	CountryData(const string &filename);
	void print();

	vector<int> randomPath();
	pair<double, vector<pair<pair<double,double>, pair<double,double>>>> minimalSpanningTree();
	pair<double, vector<pair<double,double>>> tspFromMSTCoordinates();
private:
	void loadFromFile(const string &filename);
};

#endif