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

	std::uniform_int_distribution<> dis(0, 2 * n - 1);
	int A[n];
	for (int i = 0; i < n; i++) {
		A[i] = dis(gen); 
	}

	std::sort(A, A + n);

	for (int i = 0; i < n; i++) {
		std::cout << A[i] << (i != n - 1 ? " " : "\n");
	}

	std::cout << dis(gen);

	return 0;
}