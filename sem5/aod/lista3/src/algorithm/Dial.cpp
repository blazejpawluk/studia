#include "../../lib/Graph.hpp"

void addToBucket(int v);

void Graph::DialFull(int s) {
	int c = this->maxCost;
	
	vector<long long> dist(n+1, INT_MAX);
	dist[s] = 0;
	
	vector<int> bucketTop(c+1, -1);
	vector<int> nextNode(n+1, -1);
	vector<int> prevNode(n+1, -1);
	
	
}

bool emptyBuckets(vector<vector<int>> bucket) {
	for(vector<int> b : bucket) if(!b.empty()) return false;
	return true;
}

long long Graph::DialTwo(int s, int t) {
	int c = this->maxCost;
	
	vector<int> dist(n+1, INT_MAX);
	dist[s] = 0;
	
	vector<vector<int>> bucket(c+1);
	bucket[0].push_back(s);
	
	int current = 0;
	while(!emptyBuckets(bucket)) {
		while(bucket[current].empty()) current = (current+1) % (c+1);

		for(int v : bucket[current]) {
			if(v == t) return dist[v];

			for(pair<int,int> x : adj[v]) {
				int u = x.first, cost = x.second;
				if(dist[u] > dist[v]+cost) {
					int index = dist[u] % (c+1);
					for(int i = 0; i < bucket[index].size(); i++) {
						if(bucket[index][i] == u) {
							bucket[index].erase(bucket[index].begin() + i);
							break;
						} 
					}

					dist[u] = dist[v]+cost;
					bucket[dist[u] % (c+1)].push_back(u);
				}
			}
		}
		bucket[current].clear();
	}

	return -1;
}