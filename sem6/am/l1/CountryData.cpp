#include "CountryData.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <functional>

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

void CountryData::buildDistMatrix() {
	D.assign(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++) {
			double dx = P[i].first  - P[j].first;
			double dy = P[i].second - P[j].second;
			D[i][j] = D[j][i] = (int)round(sqrt(dx*dx + dy*dy));
		}
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

	buildDistMatrix();
}

void CountryData::print() {
	cout << "name: " << name << endl;
	cout << "country: " << country << endl;
	cout << "dimension: " << n << endl;
}

// lista 0
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

pair<double, vector<pair<double,double>>> CountryData::tspFromMSTCoordinates() {
    auto mst = minimalSpanningTree();
    vector<vector<int>> adj(n);

    for (auto &e : mst.second) {
        int u = -1, v = -1;

        for (int i = 0; i < n; i++) {
            if (P[i] == e.first) u = i;
            if (P[i] == e.second) v = i;
        }

        if (u != -1 && v != -1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    vector<int> pathIndices;
    vector<char> visited(n, false);
	
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        pathIndices.push_back(u);
        for (int v : adj[u]) if (!visited[v]) dfs(v);
    };
    dfs(0);

    double total = 0.0;
    vector<pair<double,double>> pathCoords;
    for (int i = 0; i < n; i++) {
        int u = pathIndices[i];
        int v = pathIndices[(i+1)%n];
        double dx = P[u].first - P[v].first;
        double dy = P[u].second - P[v].second;
        total += sqrt(dx*dx + dy*dy);
        pathCoords.push_back(P[u]);
    }
    pathCoords.push_back(P[pathIndices[0]]);

    return {total, pathCoords};
}

// lista 1
pair<int, vector<pair<double,double>>> CountryData::localSearch(vector<int> &in, int &steps) {
	bool improved = true;
	while (improved) {
		improved = false;
		
		pair<int,int> bestInv;
		int bestDelta = 0;
		
		for (int i = 0 ; i < n; i++) {
			int a = in[i], b = in[(i+1) % n];
			for (int j = i+2; j < n; j++) {
				if (i == 0 && j == n-1) continue;
				int c = in[j], d = in[(j+1) % n];
				int delta = D[a][c] + D[b][d] - D[a][b] - D[c][d];
				if (delta < bestDelta) {
					bestDelta = delta;
					bestInv = {i,j};
				}
			}
		}

		if (bestDelta < 0) {
			steps++;
			invert(in, bestInv.first+1, bestInv.second);
			improved = true;
		}
	}
	
	pair<int, vector<pair<double,double>>> result;
	result.first = pathLength(in);
	result.second = vector<pair<double,double>>(n);
	for (int i = 0; i < n; i++) result.second[i] = P[in[i]];
	return result;
}

pair<int, vector<pair<double,double>>> CountryData::localSearch2(vector<int> &in, int &steps) {
	bool improved = true;
	while (improved) {
		improved = false;
		
		pair<int,int> bestInv;
		int bestDelta = 0;

		auto neighbors = randomNeighbors();
		for (auto [u,v] : neighbors) {
			int a = in[u], b = in[(u+1) % n];
			int c = in[v], d = in[(v+1) % n];
			int delta = D[a][c] + D[b][d] - D[a][b] - D[c][d];
			if (delta < bestDelta) {
				bestDelta = delta;
				bestInv = {u,v};
			}
		}

		if (bestDelta < 0) {
			steps++;
			invert(in, bestInv.first+1, bestInv.second);
			improved = true;
		}
	}
	
	pair<int, vector<pair<double,double>>> result;
	result.first = pathLength(in);
	result.second = vector<pair<double,double>>(n);
	for (int i = 0; i < n; i++) result.second[i] = P[in[i]];
	return result;
}

pair<int, vector<pair<double,double>>> CountryData::localSearchMST(vector<pair<pair<double,double>, pair<double,double>>> &mst, int &steps) {
	vector<vector<int>> adj(n);
    for (auto &e : mst) {
        int u = -1, v = -1;

        for (int i = 0; i < n; i++) {
            if (P[i] == e.first) u = i;
            if (P[i] == e.second) v = i;
        }

        if (u != -1 && v != -1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    vector<int> path;
    vector<char> visited(n, false);
	
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        path.push_back(u);
        for (int v : adj[u]) if (!visited[v]) dfs(v);
    };

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, n-1);
    dfs(dist(gen));
	return localSearch(path, steps);
}

int CountryData::pathLength(vector<int> &p) {
	int total = 0;
	for (int i = 0; i < n; i++) {
		total += D[p[i]][p[(i+1) % n]];
	}
	return total;
}

void CountryData::invert(vector<int> &p, int u, int v) {
	reverse(p.begin() + u, p.begin() + v + 1);
}

set<pair<int,int>> CountryData::randomNeighbors() {
	set<pair<int,int>> result;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, n-1);

	while (result.size() < n) {
		int a = dist(gen), b = dist(gen);
		if (a != b) result.insert({a,b});
	}

	return result;
}