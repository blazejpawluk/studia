#include "signal.cpp"

int main() {
	int nMin = 1000;
	int nMax = 5000;
	int step = 500;
	int rep = 50;

	ofstream file("results/results.txt");

	random_device rd;
	mt19937 gen(rd());

	for (int n = nMin; n <= nMax; n += step) {
		cout << n << endl;

		uniform_int_distribution<> dis(1, n);
		
		for (int i = 0; i < rep; i++) {
			int root = dis(gen);
			Tree T = createTree(n, root);
			signalRec(T, root);
			file << n << " " << T.X[root] << endl;
		}
	}

	file.close();

	return 0;
}