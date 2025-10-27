#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
	bool directed;
	int n;
	int m;
	vector<pair<int, int>> E;

	Graph(bool directed, int n, int m, vector<pair<int, int>> E) {
		this->directed = directed;
		this->n = n;
		this->m = m;
		this->E = E;
	}

	Graph(int argc, char* argv[]) {
		if (argc < 3) {
			throw "Zbyt malo argumentow.\n";
		}

		if (argv[1][0] == 'D') directed = true;
		else if (argv[1][0] == 'U') directed = false;
		else throw "Nie mozna stwierdzic czy graf jest skierowany czy nieskierowany.\n";

		try {
			n = stoi(argv[2]);
			if (n <= 0) throw;
		} catch (...) {
			throw "Niepoprawna liczba wierzcholkow grafu.\n";
		}

		try {
			m = stoi(argv[3]);
			if (m < 0) throw;
		} catch (...) {
			throw "Niepoprawna liczba krawedzi grafu.\n";
		}

		for (int i = 0; i < m; i++) {
			try {
				int u = stoi(argv[4 + 2*i]), v = stoi(argv[5 + 2*i]);
				if (u <= 0 || v <= 0 || u > n || v > n) throw;
				E.push_back({u, v});
			} catch (...) {
				throw "Blad przy wczytywaniu krawedzi.\n";
			}
		}
	}
};

/*
GRAFY TESTOWE DO ZADANIA 1
6 9 1 2 1 3 2 3 2 4 2 5 3 5 3 6 4 5 5 6
8 12 1 2 1 4 2 3 2 6 3 4 4 8 5 1 5 8 6 5 6 7 7 3 8 7
9 17 1 2 1 3 1 5 2 4 2 5 3 5 3 6 4 5 4 8 5 6 6 7 6 9 7 4 7 5 7 8 9 7 9 8

D 12 14 1 2 1 3 1 4 2 3 4 5 4 12 5 6 6 7 7 8 9 7 9 8 10 11 10 12 11 12
U 12 14 1 2 1 3 1 4 2 3 4 5 4 12 5 6 6 7 7 8 9 7 9 8 10 11 10 12 11 12

GRAFY TESTOWE DO ZADANIA 2
cykl: D 10 12 1 2 1 6 2 3 3 4 3 8 4 5 5 1 6 7 7 8 8 9 9 10 10 5
acykliczny: D 10 12 1 2 1 5 1 6 2 3 3 4 3 8 4 5 6 7 7 8 8 9 9 10 10 5

GRAFY TESTOWE DO ZADANIA 3
1 składowa: D 11 14 1 2 1 4 1 9 2 3 2 11 3 4 5 6 5 10 6 7 6 8 7 10 8 9 9 6 11 5
>1 składowa: D 11 12 1 2 1 4 2 3 3 4 5 6 5 10 6 7 6 8 7 10 8 9 9 6 11 5

GRAFY TESTOWE DO ZADANIA 4
dwudzielne: 
D 11 10 1 6 6 2 2 7 7 3 3 8 8 4 4 9 9 5 5 10 11 1
U 10 9 1 6 6 2 2 7 7 3 3 8 8 4 4 9 9 5 5 10
niedwudzielne:
D 10 11 1 6 6 2 2 7 2 3 7 3 3 8 8 4 4 9 9 5 5 10 10 9
U 10 11 1 6 6 2 2 7 2 3 7 3 3 8 8 4 4 9 9 5 5 10 10 9
*/