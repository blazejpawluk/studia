#ifndef CD_HPP
#define CD_HPP

#include <string>
#include <vector>
#include <set>
using namespace std;

class CountryData {
public:
	string name;
	string country;
	int n;
	vector<pair<double,double>> P;

	CountryData(const string &filename);
	void print();

	// lista 0
	vector<int> randomPath();
	pair<double, vector<pair<pair<double,double>, pair<double,double>>>> minimalSpanningTree();
	pair<double, vector<pair<double,double>>> tspFromMSTCoordinates();

	// lista 1
	pair<int, vector<pair<double,double>>> localSearch(vector<int> &in, int &steps);
	pair<int, vector<pair<double,double>>> localSearch2(vector<int> &in, int &steps);
	pair<int, vector<pair<double,double>>> localSearchMST(vector<pair<pair<double,double>, pair<double,double>>> &mst, int &steps);
private:
	void loadFromFile(const string &filename);
	
	vector<vector<int>> D;
	void buildDistMatrix();

	// lista 1
	int pathLength(vector<int> &p);
	void invert(vector<int> &p, int u, int v);
	set<pair<int,int>> randomNeighbors();
};

#endif