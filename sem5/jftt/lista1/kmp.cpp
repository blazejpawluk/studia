#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Cormen 34.4
vector<int> computePrefixFunction(string P) {
	int m = P.size();
	vector<int> pi(m, 0);
	int k = 0;

	for (int q = 1; q < m; q++) {
		while (k > 0 && P[k] != P[q]) k = pi[k-1];
		if (P[k] == P[q]) k++;
		pi[q] = k;
	}

	return pi;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Niepoprawne wywołanie programu. Poprawne wywołanie: FA <wzorzec> <nazwa pliku>" << endl;
		return 1;
	}

	string pattern = argv[1];
	string filename = argv[2];

	if (!pattern.length()) {
		cout << "Podany wzorzec jest pusty - brak dopasowań" << endl;
		return 1;
	}

	// wczytywanie zawartości pliku
	string text;
	try {
		ifstream in(filename, ios::binary);
		if (!in) throw runtime_error("Nie można otworzyć pliku " + filename);

		in.seekg(0, ios::end);
		text.reserve((size_t)in.tellg());
		in.seekg(0, ios::beg);
		text.assign((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
	} catch (const exception &e) {
		cout << e.what() << endl;
		return 1;
	}

	// Cormen 34.4 - KMP-MATCHER
	int m = pattern.size();
	int n = text.size();
	auto pi = computePrefixFunction(pattern);

	int q = 0;
	for (int i = 0; i < n; i++) {
		while (q > 0 &&	pattern[q] != text[i]) q = pi[q-1];
		if (pattern[q] == text[i]) q++;
		if (q == m) {
			cout << i-m+1 << endl;
			q = pi[q-1];
		}
	}

	return 0;
}