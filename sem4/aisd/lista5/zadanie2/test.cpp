#include "signal.cpp"

int main() {
	int n = 10;

	Tree T = createTree(n, 1);
	cout << "Tree:\n";
	for (int i = 1; i <= n; i++) {
		cout << i << ": ";
		for (int k : T.N[i]) cout << k << " ";
		cout << endl;
	}

	T = signal(T);
	cout << "\nSorted:\n";
	for (int i = 1; i <= n; i++) {
		cout << i << " - " << T.X[i] << ": ";
		for (int k : T.N[i]) cout << k << " ";
		cout << endl;
	}

	return 0;
}