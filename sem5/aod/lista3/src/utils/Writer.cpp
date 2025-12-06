#include "../../lib/Writer.hpp"

void writeSSOutput(std::string alg, std::vector<std::string> input, Graph *G, double avg) {
	std::ofstream ofs(input[3]);
	if (!ofs) return;

	ofs << "c uzywany algorytm: " << alg << std::endl;
	ofs << "p res sp ss " << alg << std::endl;
	ofs << "c plik z grafem: " << input[1] << std::endl;
	ofs << "c plik wejsciowy: " << input[2] << std::endl;
	ofs << "c plik wyjsciowy: " << input[3] << std::endl;
	ofs << "f " << input[2] << " " << input[3] << std::endl;
	ofs << "c liczba wierzcholkow: " << G->n << std::endl;
	ofs << "c liczba krawedzi: " << G->m << std::endl;
	ofs << "c minimalny koszt krawedzi: " << G->minCost << std::endl;
	ofs << "c maksymalny koszt krawedzi: " << G->maxCost << std::endl;
	ofs << "g " << G->n << " " << G->m << " " << G->minCost << " " << G->maxCost << std::endl;
	ofs << "c sredni czas znalezienia sciezki miedzy zrodlem a wszystkimi wierzcholkami: " << avg << " ms" << std::endl;
	ofs << "t " << avg << std::endl; 
}

void writeP2POutput(std::string alg, std::vector<std::string> input, Graph *G, std::vector<std::pair<std::pair<int, int>, long long>> results) {
	std::ofstream ofs(input[3]);
	if (!ofs) return;

	ofs << "c uzywany algorytm: " << alg << std::endl;
	ofs << "p res sp ss " << alg << std::endl;
	ofs << "c plik z grafem: " << input[1] << std::endl;
	ofs << "c plik wejsciowy: " << input[2] << std::endl;
	ofs << "c plik wyjsciowy: " << input[3] << std::endl;
	ofs << "f " << input[2] << " " << input[3] << std::endl;
	ofs << "c liczba wierzcholkow: " << G->n << std::endl;
	ofs << "c liczba krawedzi: " << G->m << std::endl;
	ofs << "c minimalny koszt krawedzi: " << G->minCost << std::endl;
	ofs << "c maksymalny koszt krawedzi: " << G->maxCost << std::endl;
	ofs << "c dlugosci najkrotszych sciezek (u v cost)" << std::endl;
	for (const auto &r : results) ofs << "d " << r.first.first << " " << r.first.second << " " << r.second << std::endl;
}