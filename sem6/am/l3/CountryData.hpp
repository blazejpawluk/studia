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

	// lista 2
	pair<int, vector<pair<double,double>>> simulatedAnnealing(vector<int> &in, double T, double alpha, int epochLen, int stopEpochs);
	pair<int, vector<pair<double,double>>> tabuSearch(vector<int> &in, int tabuLen, int maxIter);

	// lista 3
	pair<int, vector<pair<double,double>>> geneticSearch(
		int popSize = 100,
		int islands = 5,
		int generations = 50,
		int migrationIntervalRate = 3, 
		int migrationSizeBest = 3,
		int migrationSizeRandom = 2,
		int k = 5,
		double crossSizeMin = 0.4,
		double crossSizeMax = 0.7,
		double mutationProbability = 0.3,
		double mutationSizeMin = 0.1,
		double mutationSizeMax = 0.2,
		int adolescenceLength = 10,
		bool f = true
	);
private:
	void loadFromFile(const string &filename);
	
	vector<vector<int>> D;
	void buildDistMatrix();

	// lista 1
	int pathLength(vector<int> &p);
	void invert(vector<int> &p, int u, int v);
	set<pair<int,int>> randomNeighbors();

	// lista 3
	void adolescence(vector<int> &in, int length);
	vector<pair<vector<int>, int>> selectElements(const vector<pair<vector<int>, int>>& v, int k, int l);
	vector<int> ox(const vector<int>& p1, const vector<int>& p2, int n);
	vector<int> pmx(const vector<int>& p1, const vector<int>& p2, int n);
};

#endif