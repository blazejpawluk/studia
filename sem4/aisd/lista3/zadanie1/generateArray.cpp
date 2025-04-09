#include <iostream>
#include <string>
#include <random>
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

	uniform_int_distribution<> disK(1, n);
	cout << disK(gen) << endl;

	uniform_int_distribution<> disA(0, 2 * n - 1);
	for (int i = 0; i < n; i++) {
		cout << disA(gen) << (i < n - 1 ? " " : ""); 
	}

	return 0;
}