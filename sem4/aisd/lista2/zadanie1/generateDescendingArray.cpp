#include <iostream>
#include <string>
#include <random>
#include <algorithm>
using namespace std;

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << 0;
		return 0;
	}

	int n = stoi(argv[1]);
	cout << n << endl;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 2 * n - 1);

	int tab[n];
	for (int i = 0; i < n; i++) {
		tab[i] = dis(gen);
	}
	sort(tab, tab + n, greater<int>());

	for (int i = 0; i < n; i++) {
		cout << tab[i] << (i < n - 1 ? " " : ""); 
	}

	return 0;
}