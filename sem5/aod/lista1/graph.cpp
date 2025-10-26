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

GRAFY TESTOWE DO ZADANIA 2
cykl: D 15 16 1 2 2 3 3 4 4 5 5 1 6 7 7 8 8 9 9 6 2 6 5 10 10 11 11 12 12 13 13 14 14 15
acykliczny: D 15 20 1 2 1 3 1 4 2 5 2 6 3 6 3 7 4 7 4 8 5 9 6 9 7 10 8 10 9 11 9 12 10 12 11 13 12 13 13 14 13 15

GRAFY TESTOWE DO ZADANIA 3
1 składowa: D 15 15 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 10 10 11 11 12 12 13 13 14 14 15 15 1
>1 składowa: D 15 16 1 2 2 3 3 4 4 5 5 1 6 7 7 8 8 9 9 10 10 6 11 12 12 13 13 14 14 15 15 11 5 6

GRAFY TESTOWE DO ZADANIA 4
dwudzielne:
D 15 20 1 8 1 9 2 8 2 10 3 9 3 11 4 10 4 12 5 11 5 13 6 12 6 14 7 13 7 15 8 1 9 2 10 3 11 4 12 5 13 6
U 15 18 1 8 1 9 2 8 2 10 3 9 3 11 4 10 4 12 5 11 5 13 6 12 6 14 7 13 7 15 1 10 2 9 3 12 4 11
niedwudzielne:
D 15 18 1 2 2 3 3 1 4 5 5 6 6 4 7 8 8 9 9 10 10 11 11 12 12 13 13 14 14 15 15 7 2 4 3 7 5 9
U 15 15 1 2 2 3 3 1 3 4 4 5 5 6 6 7 7 8 8 9 9 10 10 11 11 12 12 13 13 14 14 15
*/