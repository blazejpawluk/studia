#include "../lib/Writer.hpp"

void writeSS(string inFile, string outFile, string algorithm, int n, int m, int minCost, int maxCost, double avg) {
	ofstream ofs(outFile);
	if(!ofs) {
        cerr << "Nie można otworzyć pliku: " << outFile << "\n";
        return;
    }

	ofs << "c uzywany algorytm: " << algorithm << "\n";
	ofs << "p res sp ss " << algorithm << "\n";
	ofs << "c plik wejsciowy: " << inFile << "\n";
	ofs << "c plik wyjsciowy: " << outFile << "\n";
	ofs << "f " << inFile << " " << outFile << "\n";
	ofs << "c liczba wierzcholkow: " << n << "\n";
	ofs << "c liczba krawedzi: " << m << "\n";
	ofs << "c minimalny koszt krawedzi: " << minCost << "\n";
	ofs << "c maksymalny koszt krawedzi: " << maxCost << "\n";
	ofs << "g " << n << " " << m << " " << minCost << " " << maxCost << "\n";
	ofs << "c sredni czas znalezienia sciezki miedzy zrodlem a wszystkimi wierzcholkami: " << avg << " ms\n";
	ofs << "t " << avg << "\n";
}

void writeP2p(string inFile, string outFile, string algorithm, int n, int m, int minCost, int maxCost, vector<pair<pair<int,int>,long long>> results) {
	ofstream ofs(outFile);
	if(!ofs) {
        cerr << "Nie można otworzyć pliku: " << outFile << "\n";
        return;
    }

	ofs << "c uzywany algorytm: " << algorithm << "\n";
	ofs << "p res sp p2p " << algorithm << "\n";
	ofs << "c plik wejsciowy: " << inFile << "\n";
	ofs << "c plik wyjsciowy: " << outFile << "\n";
	ofs << "f " << inFile << " " << outFile << "\n";
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