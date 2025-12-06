#include "../../lib/Parser.hpp"

std::vector<std::string> parseCommand(int argc, char* argv[]) {
	if (argc != 6) throw "Za malo argumentow";

	std::vector<std::string> result(4);

	// tryb (ss/p2p)
	if (std::string(argv[3]) == "-ss") result[0] = "ss";
	else if (std::string(argv[3]) == "-p2p")  result[0] = "p2p";
	else throw "Nieznany tryb";

	// plik z grafem
	if (std::string(argv[1]) == "-d") result[1] = std::string(argv[2]);
	else throw "Niepoprawna flaga pliku z grafem";

	// plik ze zrodlem
	result[2] = std::string(argv[4]);

	// plik wynikowy
	if (result[0] == "ss" && std::string(argv[5]) == "-oss") result[3] = std::string(argv[3]);
	else if (result[0] == "p2p" && std::string(argv[5]) == "-op2p") result[3] = std::string(argv[3]);
	else throw "Niepoprawna flaga pliku wyjsciowego";

	return result;
}

Graph *parseGraph(std::string filename) {
	std::ifstream ifs(filename);
	if (!ifs) throw "Nie mozna znalezc pliku z grafem.";

	std::string line;
	int n;
	Graph *G = nullptr;

	while(std::getline(ifs, line)) {
		int pos = 0;

		// pomijanie bialych znakow
		while (pos < line.size() && std::isspace((char)line[pos])) pos++;

		// wykrywanie pustej linii
		if (pos >= line.size()) continue;
		
		// wykrywanie komentarzy
		char first = line[pos];
		if (first == 'c') continue;

		// sprawdzanie tresci
		std::istringstream iss(line.substr(pos));
		std::string tag;
		iss >> tag;
		if (tag == "p") {
			std::string sp; int m;
			iss >> sp >> n >> m;
			G = new Graph(n, true);
		} else if (tag == "a") {
			int u, v; long long cost;
			iss >> u >> v >> cost;
			if (G) G->addEdge(u, v, cost);
		}

		if (n <= 0) throw "Niepoprawny plik z grafem";
	}

	return G;
}

std::vector<int> parseSSFile(std::string filename) {
	std::ifstream ifs(filename);
	if (!ifs) throw "Nie mozna znalezc pliku ze zrodlami";

	std::string line;
	int n;
	std::vector<int> sources;

	while(std::getline(ifs, line)) {
		int pos = 0;

		// pomijanie bialych znakow
		while (pos < line.size() && std::isspace((char)line[pos])) pos++;

		// wykrywanie pustej linii
		if (pos >= line.size()) continue;
		
		// wykrywanie komentarzy
		char first = line[pos];
		if (first == 'c') continue;

		// sprawdzanie tresci
		std::istringstream iss(line.substr(pos));
		std::string tag;
		iss >> tag;
		if (tag == "p") {
			std::string aux, sp, ss;
			iss >> aux >> sp >> ss >> n;
		} else if (tag == "s") {
			int s;
			iss >> s;
			sources.push_back(s);
		}

		if (n <= 0) throw "Niepoprawny plik ze zrodlami";
	}

	return sources;
}

std::vector<std::pair<int,int>> parseP2PFle(std::string filename) {
	std::ifstream ifs(filename);
	if (!ifs) throw "Nie mozna znalezc pliku z parami";

	std::string line;
	int n;
	std::vector<std::pair<int,int>> pairs;

	while(std::getline(ifs, line)) {
		int pos = 0;

		// pomijanie bialych znakow
		while (pos < line.size() && std::isspace((char)line[pos])) pos++;

		// wykrywanie pustej linii
		if (pos >= line.size()) continue;
		
		// wykrywanie komentarzy
		char first = line[pos];
		if (first == 'c') continue;

		// sprawdzanie tresci
		std::istringstream iss(line.substr(pos));
		std::string tag;
		iss >> tag;
		if (tag == "p") {
			std::string aux, sp, p2p;
			iss >> aux >> sp >> p2p >> n;
		} else if (tag == "q") {
			int u, v;
			iss >> u >> v;
			pairs.push_back({u, v});
		}

		if (n <= 0) throw "Niepoprawny plik z parami";
	}

	return pairs;
}