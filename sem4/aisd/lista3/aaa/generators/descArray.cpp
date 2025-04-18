#include <iostream>
#include <string>
#include <random>
#include <algorithm>

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << 0;
		return 0;
	}

	int n = std::stoi(argv[1]);
	std::cout << n << std::endl;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> disA(0, 2 * n - 1);
	int A[n];
	for (int i = 0; i < n; i++) {
		A[i] = disA(gen); 
	}

	std::sort(A, A + n, std::greater<int>());

	for (int i = 0; i < n; i++) {
		std::cout << A[i] << (i != n - 1 ? " " : "");
	}

	return 0;
}