#include <bits/stdc++.h>
#include "../lib/Graph.hpp"
using namespace std;

vector<string> parseCommand(int argc, char* argv[], string algorithm) {
	if(argc != 7) {
		cerr << "Niepoprawna liczba opcji.\n";
		exit(1);
	}

	vector<string> result(5);
	result[0] = algorithm;

	if(string(argv[2]) == "-d") result[1] = argv[3];
	else {
		cerr << "Niepoprawne uzycie. Poprawne: <algorytm> -d <plik-graf> -ss/-p2p <plik-input> -oss/op2p <plik-output>\n";
		exit(1);
	}

	if(string(argv[4]) == "-ss" && string(argv[6]) == "-oss") {
		result[2] = "ss";
		result[3] = argv[5];
		result[4] = argv[7];
	} else if(string(argv[4]) == "-p2p" && string(argv[6]) == "-op2p") {
		result[2] = "p2p";
		result[3] = argv[5];
		result[4] = argv[7];
	} else {
		cerr << "Niepoprawne uzycie. Poprawne: <algorytm> -d <plik-graf> -ss/-p2p <plik-input> -oss/op2p <plik-output>\n";
		exit(1);
	}

	return result;
}

Graph parseGraphInput(string filename) {
	ifstream fin(filename);
	if(!fin) {
		cerr << "Nie moge otworzyc pliku: " << filename << "\n";
		exit(1);
	}

	string line;
	int n = 0;
	vector<pair<pair<int,int>,int>> edges;

	while(getline(fin, line)) {
		int pos = 0;
		while(pos < line.size() && isspace((char)line[pos])) pos++;
		if(pos >= line.size()) continue;
		char first = line[pos];
		if(first == 'c') continue;
		
		istringstream iss(line.substr(pos));
		string tag;
		iss >> tag;
		if(tag == "p") {
			string sp;
			int m;
			iss >> sp >> n >> m;
		} else if(tag == "a") {
			int u, v, cost;
			iss >> u >> v >> cost;
			edges.push_back({{u,v}, cost});
		}
	}

	if(n <= 0) {
		cerr << "Nie znaleziono linii 'p sp n m' z poprawna liczba wierzcholkow.\n";
		exit(1);
	}

	return Graph(n, edges);
}

vector<int> parseSSInput(string filename) {
	ifstream fin(filename);
	if(!fin) {
		cerr << "Nie moge otworzyc pliku: " << filename << "\n";
		exit(1);
	}

	string line;
	int n = 0;
	vector<int> sources;

	while(getline(fin, line)) {
		int pos = 0;
		while(pos < line.size() && isspace((char)line[pos])) pos++;
		if(pos >= line.size()) continue;
		char first = line[pos];
		if(first == 'c') continue;
		
		istringstream iss(line.substr(pos));
		string tag;
		iss >> tag;
		if(tag == "p") {
			string aux, sp, ss;
			iss >> aux >> sp >> ss >> n;
		} else if(tag == "s") {
			int s;
			iss >> s;
			sources.push_back(s);
		}
	}

	if(n <= 0) {
		cerr << "Nie znaleziono linii 'p aux sp ss <n>' z poprawna liczba zrodel.\n";
		exit(1);
	}

	return sources;
}

vector<pair<int,int>> parseP2PInput(string filename) {
	ifstream fin(filename);
	if(!fin) {
		cerr << "Nie moge otworzyc pliku: " << filename << "\n";
		exit(1);
	}

	string line;
	int n = 0;
	vector<pair<int,int>> pairs;

	while(getline(fin, line)) {
		int pos = 0;
		while(pos < line.size() && isspace((char)line[pos])) pos++;
		if(pos >= line.size()) continue;
		char first = line[pos];
		if(first == 'c') continue;
		
		istringstream iss(line.substr(pos));
		string tag;
		iss >> tag;
		if(tag == "p") {
			string aux, sp, p2p;
			iss >> aux >> sp >> p2p >> n;
		} else if(tag == "q") {
			int u,v;
			iss >> u >> v;
			pairs.push_back({u,v});
		}
	}

	if(n <= 0) {
		cerr << "Nie znaleziono linii 'p aux sp ss <n>' z poprawna liczba zrodel.\n";
		exit(1);
	}

	return pairs;
}