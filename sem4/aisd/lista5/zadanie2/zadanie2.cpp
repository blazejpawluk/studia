#ifndef ZAD2
#define ZAD2

#include "graph.cpp"

void signalRec(Tree T, int v) {
	int n = T.children[v].size();
	T.x[v] = n;
	for (int u : T.children[v]) {
		signalRec(T, u);
		T.x[v] = max(T.x[v], T.x[u]+1);
	}
}

vector<vector<int>> signal(Tree T) {
	vector<vector<int>> result(T.n);

	signalRec(T, T.root);
	for (int i = 0; i < T.n; i++) {
		// cout << i << " " << T.x[i] << endl;
		vector<pair<int, int>> temp;
		for (int k : T.children[i]) temp.push_back(pair(k, T.x[k]));
		sort(temp.begin(), temp.end(), [](const pair<int, int>& a, const pair<int, int>& b){
			return a.second > b.second;
		});
		// cout <<"\t";
		// for (pair<int, int> x : temp) cout << "(" << x.first << "," << x.second << ") ";
		// cout << endl;

		for (pair<int, int> p : temp) result[i].push_back(p.first);
	}

	return result;
}

#endif