#include "prim.cpp"

int main() {
	int n = 10;
	int total = 1000;
	int working = 0;
	for (int i = 0; i < total; i++) {
		Graph G = generateFullGraph(n);
		Graph K = Prim(G);

		bool isIn[n+1] = {};
		for (Edge e : K.E) {
			isIn[e.V.first] = true;
			isIn[e.V.second] = true;
		}

		bool ok = true;
		for (int j = 1; j <= n; j++) if (!isIn[j]) ok = false;
		if (ok) working++;
	}

	cout << working << "/" << total << endl;
}