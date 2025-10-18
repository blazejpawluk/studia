#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// sprawdza czy prefix o długości k z P jest sufiksem P[0..q-1]+a (Pk=|Pqa)
bool isPrefixSuffix(string P, int k, int q, char a) {
	int strlen = q + 1;
	if (k == 0) return true;
	if (k > strlen) return false;

	for (int j = 0; j < k; j++) {
		int pos = strlen - k + j;
		char c;

		if (pos < q) c = P[pos];
		else c = a;

		if (P[j] != c) return false;
	}

	return true;
}

// Cormen 34.4, sigma = 256
vector<vector<int>> computeTransitionFunction(string P) {
	int m = P.size();
	vector<vector<int>> TF(m+1, vector<int>(256, 0));

	for (int q = 0; q <= m; q++) {
		for (int a = 0; a < 256; a++) {
			int k = min(m, q+1);
			while (k > 0 && !isPrefixSuffix(P, k, q, (char)a)) k--;
			TF[q][a] = k;
		}
	}

	return TF;
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

	// skonczony automat (wektor wektorów int)
	auto TF = computeTransitionFunction(pattern);
	
	// Cormen 34.4 - FINITE-AUTOMATION-MATCHER
	int n = text.size();
	int m = pattern.size();

	int q = 0;
	for (int i = 0; i < n; i++) {
		q = TF[q][text[i]];
		if (q == m) cout << i - m + 1 << endl;
	}

	return 0;
}