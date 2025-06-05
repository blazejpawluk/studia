#include "heap.cpp"

int main() {
	int rep = 5;
	int N = 500;

	ofstream file500("results/500-results.txt");

	random_device rd;
	mt19937 gen(rd());

	for (int i = 0; i < rep; i++) {
		cout << i << " ";
		file500 << i << " ";

		comps = 0;
		vector<int> H1 = makeHeap(), H2 = makeHeap();
		file500 << comps << " ";

		uniform_int_distribution<> dis(1, 2*N);
		comps = 0;
		for (int j = 0; j < N; j++) {
			Insert(H1, dis(gen));
			Insert(H2, dis(gen));
		}
		file500 << comps << " ";

		comps = 0;
		vector<int> H = Union(H1, H2);
		file500 << comps << " ";

		comps = 0;
		for (int j = 0; j < 2*N; j++) {
			uniform_int_distribution<> disI(1, size(H));
			Delete(H, H[disI(gen)]);
		}
		file500 << comps << endl;
	}
	cout << endl;

	file500.close();

	int nMin = 100;
	int nMax = 10000;
	int step = 100;
	rep = 5;

	ofstream fileN("results/resultsN.txt");

	for (int n = nMin; n <= nMax; n += step) {
		cout << n << (n%1000 == 0 ? "\n" : " ");

		uniform_int_distribution<> dis(1, 2*n);

		for (int i = 0; i < rep; i++) {
			comps = 0;
			vector<int> H1 = makeHeap(), H2 = makeHeap();
			for (int j = 0; j < n; j++) {
				Insert(H1, dis(gen));
				Insert(H2, dis(gen));
			}
			vector<int> H = Union(H1, H2);
			for (int j = 0; j < 2*n; j++) {
				uniform_int_distribution<> disI(1, size(H));
				Delete(H, H[disI(gen)]);
			}
			fileN << n << " " << 1.0*comps/n << endl;
		}
	}

	fileN.close();

	return 0;
}