#ifndef SIGNAL
#define SIGNAL

#include "graph.cpp"

void signalRec(Tree T, int v) {
	int n = T.N[v].size();
	T.X[v] = n;
	for (int k : T.N[v]) {
		signalRec(T, k);
		T.X[v] = max(T.X[v], T.X[k]+1);
	}
}

Tree signal(Tree T) {
	int n = T.V.size();
	vector<int> N[n+1];

	signalRec(T, T.root);

	for (int i = 1; i <= n; i++) {
		vector<pair<int, int>> temp;
		for (int k : T.N[i]) temp.push_back({T.X[k], k});

		sort(temp.begin(), temp.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
			return a.first > b.first;
		});

		for (pair<int, int> p : temp) N[i].push_back(p.second);
	}

	for (int i = 1; i <= n; i++) {
		T.N[i].erase(T.N[i].begin(), T.N[i].end());
		for (int k : N[i]) T.N[i].push_back(k);
	}

	return T;
}

#endif