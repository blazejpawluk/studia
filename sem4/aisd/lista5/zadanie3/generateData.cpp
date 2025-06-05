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
		Node *H1 = MakeHeap(), *H2 = MakeHeap();
		file500 << comps << " ";

		uniform_int_distribution<> dis(1, 2*N);
		comps = 0;
		int h1[N], h2[N], h[2*N];
		for (int j = 0; j < N; j++) {
			h1[i] = dis(gen);
			h2[i] = dis(gen);

			h[i] = h1[i];
			h[N+i] = h2[i];

			H1 = Insert(H1, h1[i]);
			H1 = Insert(H2, h2[i]);
		}
		file500 << comps << " ";

		comps = 0;
		Node* H = Union(H1, H2);
		file500 << comps << " ";

		comps = 0;
		for (int j = 0; j < 2*N; j++) {
			uniform_int_distribution<> disI(0, 2*N-j-1);
			Delete(H, find(H, h[disI(gen)]));
		}
		file500 << comps << endl;
	}
	cout << endl;

	file500.close();

	int nMin = 100;
	int nMax = 10000;
	int step = 100;
	rep = 50;

	ofstream fileN("results/resultsN.txt");

	for (int n = nMin; n <= nMax; n += step) {
		cout << n << (n%1000 == 0 ? "\n" : " ");

		uniform_int_distribution<> dis(1, 2*n);

		for (int i = 0; i < rep; i++) {
			comps = 0;
			Node *H1 = MakeHeap(), *H2 = MakeHeap();
			int h1[n], h2[n], h[2*n];
			for (int j = 0; j < n; j++) {
				h1[i] = dis(gen);
				h2[i] = dis(gen);

				h[i] = h1[i];
				h[n+i] = h2[i];

				H1 = Insert(H1, h1[i]);
				H1 = Insert(H2, h2[i]);
			}
			Node* H = Union(H1, H2);
			for (int j = 0; j < 2*n; j++) {
				uniform_int_distribution<> disI(0, 2*n-j-1);
				Delete(H, find(H, h[disI(gen)]));
			}
			fileN << n << " " << 1.0*comps/n << endl;
		}
	}

	fileN.close();

	return 0;
}