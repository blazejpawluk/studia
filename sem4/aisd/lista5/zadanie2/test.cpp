#include "zadanie2.cpp"

int main() {
	int n = 10;

	Graph G = createGraph(n);
	Tree T = createTree(Tree(0, n), G, 0);


	cout << "\nDRZEWO:\n";
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (int k : T.children[i]) cout << k << " ";
		cout << endl;
	}

	cout << "\nW KOLEJNOSCI:\n";
	vector<vector<int>> result = signal(T);
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (int k : result[i]) cout << k << " ";
		cout << endl;
	}

	return 0;
}