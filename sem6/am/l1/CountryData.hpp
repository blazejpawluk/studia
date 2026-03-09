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
private:
	void loadFromFile(const string &filename);
};

#endif