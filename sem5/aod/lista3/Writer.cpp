#include "Writer.hpp"

void writeP2p(string inFile, string outFile, string algorithm, int n, int m, int minCost, int maxCost, vector<pair<pair<int,int>,int>> results) {
	ofstream ofs(outFile);
	if(!ofs) {
        cerr << "Nie można otworzyć pliku: " << outFile << "\n";
        return;
    }

	ofs << "c uzywany algorytm: " << algorithm << "\n";
	ofs << "p res sp ss " << algorithm << "\n";
	ofs << "c plik wejsciowy: " << inFile << "\n";
	ofs << "c plik wyjsciowy: " << outFile << "\n";
	ofs << "p " << inFile << " " << outFile << "\n";
	ofs << "c liczba wierzcholkow: " << n << "\n";
	ofs << "c liczba krawedzi: " << m << "\n";
	ofs << "c minimalny koszt krawedzi: " << minCost << "\n";
	ofs << "c maksymalny koszt krawedzi: " << maxCost << "\n";
	ofs << "g " << n << " " << m << " " << minCost << " " << maxCost << "\n";

	ofs << "c dlugosci najkrotszych sciezek (u v koszt)\n";
	for(pair<pair<int,int>,int> p : results) {
		ofs << "d " << p.first.first << " " << p.first.second << " " << p.second << "\n";
	}
}