#include "Graph.hpp"

int main() {
	int n = 7;
	vector<vector<pair<int,int>>> adj(n+1);
	adj[1].push_back({2,4});
	adj[1].push_back({3,1});
	adj[2].push_back({4,3});
	adj[2].push_back({6,10});
	adj[3].push_back({2,2});
	adj[3].push_back({4,4});
	adj[3].push_back({5,7});
	adj[4].push_back({6,16});
	adj[4].push_back({7,20});
	adj[5].push_back({4,1});
	adj[6].push_back({7,1});

	Graph G(n,adj);
	
	G.DijkstraFull(1);
	cout << G.DijkstraTwo(1,7) << endl;
	cout << G.DijkstraTwo(1,4) << endl;
	
	G.DialFull(1);
	cout << G.DialTwo(1,7) << endl;
	cout << G.DialTwo(1,4) << endl;
	
	G.RadixHeapFull(1);
	cout << G.RadixHeapTwo(1,7) << endl;
	cout << G.RadixHeapTwo(1,4) << endl;

	return 0;
}