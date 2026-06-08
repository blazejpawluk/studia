#include "CountryData.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <functional>
#include <cmath>
#include <deque>
#include <climits>
#include <assert.h>

CountryData::CountryData(const string &filename) {
	loadFromFile(filename);
}

string trim(string s) {
	s.erase(
		remove_if(s.begin(), s.end(), 
			[](unsigned char c) {return isspace(c);}
	), s.end());
	return s;
}

void CountryData::buildDistMatrix() {
	D.assign(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++) {
			double dx = P[i].first  - P[j].first;
			double dy = P[i].second - P[j].second;
			D[i][j] = D[j][i] = (int)round(sqrt(dx*dx + dy*dy));
		}
}

void CountryData::loadFromFile(const string &filename) {
	name.clear();
	country.clear();
	n = 0;
	P.clear();
	
	ifstream in(filename);
	string line;
	bool nodes = false;
	bool firstComment = true;
	while (getline(in, line)) {
		int separatorIndex = line.find(':');
		string key, value;
		if (separatorIndex != string::npos) {
			key = line.substr(0, separatorIndex);
			value = line.substr(separatorIndex+1);
		} else {
			key = line;
			value = "";
		}

		if (trim(key) == "NAME") {
			name = value;
		} else if (trim(key) == "COMMENT" && firstComment) {
			firstComment = false;
			istringstream iss(value);
			string token;
			while (iss >> token) country = token;
		} else if (trim(key) == "DIMENSION") {
			n = stoi(value);
			P = vector<pair<double,double>>(n, {0,0});
		} else if (value == "") {
			istringstream iss(key);
			int id; double x, y;
			if (iss >> id >> x >> y) {
				P[id-1] = {x,y};
			}
		}
	}

	buildDistMatrix();
}

void CountryData::print() {
	cout << "name: " << name << endl;
	cout << "country: " << country << endl;
	cout << "dimension: " << n << endl;
}

// lista 0
vector<int> CountryData::randomPath() {
	vector<int> path(n);
	for (int i = 0; i < n; i++) path[i] = i;
	
	random_device rd;
	mt19937 gen(rd());
	shuffle(path.begin(), path.end(), gen);

	return path;
}

// algorytm prima
pair<double, vector<pair<pair<double,double>, pair<double,double>>>> CountryData::minimalSpanningTree() {
	if (n <= 0) return {0.0, {}};

	vector<double> minDist(n, numeric_limits<double>::infinity());
	vector<int> parent(n, -1);
	vector<char> used(n, false);
	minDist[0] = 0.0;

	for (int i = 0; i < n; i++) {
		int v = -1;
		for (int j = 0; j < n; j++) {
			if (!used[j] && (v == -1 || minDist[j] < minDist[v])) v = j;
		}

		if (v == -1) break;
		used[v] = true;
		
		for (int to = 0; to < n; to++) {
			if (used[to]) continue;

			double dx = P[v].first - P[to].first;
			double dy = P[v].second - P[to].second;
			double d = sqrt(dx*dx + dy*dy);

			if (d < minDist[to]) {
				minDist[to] = d;
				parent[to] = v;
			}
		}
	}

	double total = 0.0;
	vector<pair<pair<double,double>, pair<double,double>>> edges;
	for (int i = 1; i < n; i++) {
		if (parent[i] != -1) {
			edges.emplace_back(P[parent[i]], P[i]);

			double dx = P[parent[i]].first - P[i].first;
			double dy = P[parent[i]].second - P[i].second;
			total += sqrt(dx*dx + dy*dy);
		}
	}
	return {total, edges};
}

pair<double, vector<pair<double,double>>> CountryData::tspFromMSTCoordinates() {
    auto mst = minimalSpanningTree();
    vector<vector<int>> adj(n);

    for (auto &e : mst.second) {
        int u = -1, v = -1;

        for (int i = 0; i < n; i++) {
            if (P[i] == e.first) u = i;
            if (P[i] == e.second) v = i;
        }

        if (u != -1 && v != -1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    vector<int> pathIndices;
    vector<char> visited(n, false);
	
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        pathIndices.push_back(u);
        for (int v : adj[u]) if (!visited[v]) dfs(v);
    };
    dfs(0);

    double total = 0.0;
    vector<pair<double,double>> pathCoords;
    for (int i = 0; i < n; i++) {
        int u = pathIndices[i];
        int v = pathIndices[(i+1)%n];
        double dx = P[u].first - P[v].first;
        double dy = P[u].second - P[v].second;
        total += sqrt(dx*dx + dy*dy);
        pathCoords.push_back(P[u]);
    }
    pathCoords.push_back(P[pathIndices[0]]);

    return {total, pathCoords};
}

// lista 1
pair<int, vector<pair<double,double>>> CountryData::localSearch(vector<int> &in, int &steps) {
	bool improved = true;
	while (improved) {
		improved = false;
		
		pair<int,int> bestInv;
		int bestDelta = 0;
		
		for (int i = 0 ; i < n; i++) {
			int a = in[i], b = in[(i+1) % n];
			for (int j = i+2; j < n; j++) {
				if (i == 0 && j == n-1) continue;
				int c = in[j], d = in[(j+1) % n];
				int delta = D[a][c] + D[b][d] - D[a][b] - D[c][d];
				if (delta < bestDelta) {
					bestDelta = delta;
					bestInv = {i,j};
				}
			}
		}

		if (bestDelta < 0) {
			steps++;
			invert(in, bestInv.first+1, bestInv.second);
			improved = true;
		}
	}
	
	pair<int, vector<pair<double,double>>> result;
	result.first = pathLength(in);
	result.second = vector<pair<double,double>>(n);
	for (int i = 0; i < n; i++) result.second[i] = P[in[i]];
	return result;
}

pair<int, vector<pair<double,double>>> CountryData::localSearch2(vector<int> &in, int &steps) {
	bool improved = true;
	while (improved) {
		improved = false;
		
		pair<int,int> bestInv;
		int bestDelta = 0;

		auto neighbors = randomNeighbors();
		for (auto [u,v] : neighbors) {
			int a = in[u], b = in[(u+1) % n];
			int c = in[v], d = in[(v+1) % n];
			int delta = D[a][c] + D[b][d] - D[a][b] - D[c][d];
			if (delta < bestDelta) {
				bestDelta = delta;
				bestInv = {u,v};
			}
		}

		if (bestDelta < 0) {
			steps++;
			invert(in, bestInv.first+1, bestInv.second);
			improved = true;
		}
	}
	
	pair<int, vector<pair<double,double>>> result;
	result.first = pathLength(in);
	result.second = vector<pair<double,double>>(n);
	for (int i = 0; i < n; i++) result.second[i] = P[in[i]];
	return result;
}

pair<int, vector<pair<double,double>>> CountryData::localSearchMST(vector<pair<pair<double,double>, pair<double,double>>> &mst, int &steps) {
	vector<vector<int>> adj(n);
    for (auto &e : mst) {
        int u = -1, v = -1;

        for (int i = 0; i < n; i++) {
            if (P[i] == e.first) u = i;
            if (P[i] == e.second) v = i;
        }

        if (u != -1 && v != -1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    vector<int> path;
    vector<char> visited(n, false);
	
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        path.push_back(u);
        for (int v : adj[u]) if (!visited[v]) dfs(v);
    };

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, n-1);
    dfs(dist(gen));
	return localSearch(path, steps);
}

int CountryData::pathLength(vector<int> &p) {
	int total = 0;
	for (int i = 0; i < n; i++) {
		total += D[p[i]][p[(i+1) % n]];
	}
	return total;
}

void CountryData::invert(vector<int> &p, int u, int v) {
	reverse(p.begin() + u, p.begin() + v + 1);
}

set<pair<int,int>> CountryData::randomNeighbors() {
	set<pair<int,int>> result;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, n-1);

	while (result.size() < n) {
		int a = dist(gen), b = dist(gen);
		if (a != b) result.insert({a,b});
	}

	return result;
}

// lista 2

pair<int, vector<pair<double,double>>> CountryData::simulatedAnnealing(
		vector<int> &in, double T, double alpha, int epochLen, int stopEpochs) {
	vector<int> current = in;
	vector<int> best = in;
	int currentLen = pathLength(current);
	int bestLen = currentLen;
 
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> randIdx(0, n - 1);
	uniform_real_distribution<> randProb(0.0, 1.0);
 
	int noImproveEpochs = 0;
	while (noImproveEpochs < stopEpochs) {
		bool improved = false;
		for (int k = 0; k < epochLen; k++) {
			int i = randIdx(gen), j = randIdx(gen);
			if (i > j) swap(i, j);
			if (i == j || (i == 0 && j == n - 1)) continue;
 
			int a = current[i], b = current[(i + 1) % n];
			int c = current[j], d = current[(j + 1) % n];
			int delta = D[a][c] + D[b][d] - D[a][b] - D[c][d];
 
			if (delta < 0 || randProb(gen) < exp((double)-delta / T)) {
				invert(current, i + 1, j);
				currentLen += delta;
				if (currentLen < bestLen) {
					best = current;
					bestLen = currentLen;
					improved = true;
				}
			}
		}
		T *= alpha;
		if (improved) noImproveEpochs = 0;
		else noImproveEpochs++;
	}
 
	pair<int, vector<pair<double,double>>> result;
	result.first = bestLen;
	result.second = vector<pair<double,double>>(n);
	for (int i = 0; i < n; i++) result.second[i] = P[best[i]];
	return result;
}

pair<int, vector<pair<double,double>>> CountryData::tabuSearch(
		vector<int> &in, int tabuLen, int maxIter) {
	vector<int> current = in;
	vector<int> best = in;
	int currentLen = pathLength(current);
	int bestLen = currentLen;
 
	// lista tabu przechowuje pary miast (niezależne od kolejności w trasie)
	deque<pair<int,int>> tabu;
	set<pair<int,int>> tabuSet;
 
	for (int iter = 0; iter < maxIter; iter++) {
		pair<int,int> bestMove = {-1, -1};
		pair<int,int> bestMoveKey = {-1, -1};
		int bestDelta = INT_MAX;
 
		for (int i = 0; i < n; i++) {
			int a = current[i], b = current[(i + 1) % n];
			for (int j = i + 2; j < n; j++) {
				if (i == 0 && j == n - 1) continue;
				int c = current[j], d = current[(j + 1) % n];
				int delta = D[a][c] + D[b][d] - D[a][b] - D[c][d];
 
				pair<int,int> key = {min(a, c), max(a, c)};
 
				// kryterium aspiracji: ruch tabu jest dozwolony jeśli daje nowe globalne optimum
				bool isTabu = tabuSet.count(key);
				if (isTabu && currentLen + delta >= bestLen) continue;
 
				if (delta < bestDelta) {
					bestDelta = delta;
					bestMove = {i, j};
					bestMoveKey = key;
				}
			}
		}
 
		if (bestMove.first == -1) break;
 
		invert(current, bestMove.first + 1, bestMove.second);
		currentLen += bestDelta;
 
		tabu.push_back(bestMoveKey);
		tabuSet.insert(bestMoveKey);
		if ((int)tabu.size() > tabuLen) {
			tabuSet.erase(tabu.front());
			tabu.pop_front();
		}
 
		if (currentLen < bestLen) {
			bestLen = currentLen;
			best = current;
		}
	}
 
	pair<int, vector<pair<double,double>>> result;
	result.first = bestLen;
	result.second = vector<pair<double,double>>(n);
	for (int i = 0; i < n; i++) result.second[i] = P[best[i]];
	return result;
}


// lista 3
#include <future>
#include <mutex>

pair<int, vector<pair<double,double>>> CountryData::geneticSearch(
    int popSize,
    int islandsCount,
    int generations,
    int migrationIntervalRate,
    int migrationSizeBest,
    int migrationSizeRandom,
    int k,
    double crossSizeMin,
    double crossSizeMax,
    double mutationProbability,
    double mutationSizeMin,
    double mutationSizeMax,
    int adolescenceLength,
    bool f
) {
    auto makeGen = []() {
        random_device rd;
        return mt19937(rd());
    };

    vector<mt19937> islandGens(islandsCount);
    for (auto& g : islandGens) g = makeGen();

    // wyznaczanie populacji początkowej — każda wyspa w osobnym wątku
    vector<vector<pair<vector<int>,int>>> islands(islandsCount, vector<pair<vector<int>,int>>(popSize / islandsCount));

    {
        vector<future<void>> initFutures;
        initFutures.reserve(islandsCount);
        for (int i = 0; i < islandsCount; i++) {
            initFutures.push_back(async(launch::async, [&, i]() {
                for (int j = 0; j < popSize / islandsCount; j++) {
                    islands[i][j].first = randomPath();
                    adolescence(islands[i][j].first, adolescenceLength);
                    islands[i][j].second = pathLength(islands[i][j].first);
                }
            }));
        }
        for (auto& fut : initFutures) fut.get();
    }

    for (int generation = 0; generation < generations; generation++) {

        // przetwarzanie wysp — każda w osobnym wątku
        {
            vector<future<void>> genFutures;
            genFutures.reserve(islandsCount);
            for (int i = 0; i < islandsCount; i++) {
                genFutures.push_back(async(launch::async, [&, i]() {
                    mt19937& gen = islandGens[i];

                    // selekcja
                    vector<pair<int,int>> parents(islands[i].size() / 2, {-1, -1});
                    for (int j = 0; j < (int)islands[i].size() / 2; j++) {
                        vector<int> candidates;
                        uniform_int_distribution<> dist(0, islands[i].size() - 1);

                        for (int l = 0; l < k; l++) {
                            candidates.push_back(dist(gen));
                        }
                        sort(candidates.begin(), candidates.end(),
                            [&](int a, int b) {
                                return islands[i][a].second < islands[i][b].second;
                            }
                        );
                        parents[j].first  = candidates[0];
                        parents[j].second = candidates[1];
                    }

                    vector<pair<vector<int>,int>> kids(islands[i].size());
                    for (int j = 0; j < (int)islands[i].size() / 2; j++) {
                        // krzyżowanie
                        uniform_int_distribution<> distSize((int)(crossSizeMin * n), (int)(crossSizeMax * n));
                        int crossSize = distSize(gen);

                        uniform_int_distribution<> distStart(0, n - 1);
                        int start = distStart(gen);

                        vector<bool> inK1(n, false), inK2(n, false);
                        for (int l = 0; l < crossSize; l++) {
                            kids[j * 2].first.push_back(islands[i][parents[j].first].first[(start + l) % n]);
                            inK1[islands[i][parents[j].first].first[(start + l) % n]] = true;
                            kids[j * 2 + 1].first.push_back(islands[i][parents[j].second].first[(start + l) % n]);
                            inK2[islands[i][parents[j].second].first[(start + l) % n]] = true;
                        }

                        if (f) {
                            kids[j * 2].first = ox(
                                islands[i][parents[j].first].first,
                                islands[i][parents[j].second].first,
                                n
                            );
                            kids[j * 2 + 1].first = ox(
                                islands[i][parents[j].second].first,
                                islands[i][parents[j].first].first,
                                n
                            );
                        }
                        else {
                            kids[j * 2].first = pmx(
                                islands[i][parents[j].first].first,
                                islands[i][parents[j].second].first,
                                n
                            );
                            kids[j * 2 + 1].first = pmx(
                                islands[i][parents[j].second].first,
                                islands[i][parents[j].first].first,
                                n
                            );
                        }

                        // mutacja
                        uniform_real_distribution<> distMut(0, 1);
                        double p1 = distMut(gen);
                        if (p1 < mutationProbability) {
                            uniform_int_distribution<> distLen((int)(mutationSizeMin * n), (int)(mutationSizeMax * n));
                            int mutationLength = distLen(gen);

                            uniform_int_distribution<> distMutStart(0, n - mutationLength - 1);
                            int mutationStart = distMutStart(gen);

                            invert(kids[j * 2].first, mutationStart, mutationStart + mutationLength);
                        }
                        double p2 = distMut(gen);
                        if (p2 < mutationProbability) {
                            uniform_int_distribution<> distLen((int)(mutationSizeMin * n), (int)(mutationSizeMax * n));
                            int mutationLength = distLen(gen);

                            uniform_int_distribution<> distMutStart(0, n - mutationLength - 1);
                            int mutationStart = distMutStart(gen);

                            invert(kids[j * 2 + 1].first, mutationStart, mutationStart + mutationLength);
                        }

                        // dorastanie
                        adolescence(kids[j * 2].first, adolescenceLength);
                        adolescence(kids[j * 2 + 1].first, adolescenceLength);

                        kids[j * 2].second = pathLength(kids[j * 2].first);
                        kids[j * 2 + 1].second = pathLength(kids[j * 2 + 1].first);
                    }

                    islands[i] = kids;
                }));
            }
            for (auto& fut : genFutures) fut.get();
        }

        // migracje między wyspami — sekwencyjnie (wymaga spójnego stanu wszystkich wysp)
        if (generation % (generations / migrationIntervalRate) == 0 && generation != 0) {
            vector<vector<pair<vector<int>, int>>> migrations(islandsCount);
            for (int i = 0; i < islandsCount; i++) {
                migrations[i] = selectElements(islands[i], migrationSizeBest, migrationSizeRandom);
            }

            for (int i = 0; i < islandsCount; i++) {
                for (auto& migrant : migrations[i]) {
                    auto it = find(islands[i].begin(), islands[i].end(), migrant);
                    if (it != islands[i].end()) islands[i].erase(it);
                }

                for (auto& migrant : migrations[i]) {
                    islands[(i + 1) % islandsCount].push_back(migrant);
                }
            }
        }
    }

    pair<vector<int>,int> best;
    best.second = INT_MAX;
    for (int i = 0; i < islandsCount; i++) {
        for (int j = 0; j < (int)islands[i].size(); j++) {
            if (islands[i][j].second < best.second) best = islands[i][j];
        }
    }
    pair<int, vector<pair<double,double>>> result;
    result.first = best.second;
    result.second = vector<pair<double,double>>(n);
    for (int i = 0; i < n; i++) result.second[i] = P[best.first[i]];
    return result;
}

void CountryData::adolescence(vector<int> &in, int length) {
    bool improved = true;
    int count = 0;
    while (improved && count < length) {
        improved = false;

        pair<int,int> bestInv;
        int bestDelta = 0;

        for (int i = 0 ; i < n; i++) {
            int a = in[i], b = in[(i+1) % n];
            for (int j = i+2; j < n; j++) {
                if (i == 0 && j == n-1) continue;
                int c = in[j], d = in[(j+1) % n];
                int delta = D[a][c] + D[b][d] - D[a][b] - D[c][d];
                if (delta < bestDelta) {
                    bestDelta = delta;
                    bestInv = {i,j};
                }
            }
        }

        if (bestDelta < 0) {
            invert(in, bestInv.first+1, bestInv.second);
            count++;
            improved = true;
        }
    }
}

vector<pair<vector<int>, int>> CountryData::selectElements(const vector<pair<vector<int>, int>>& v, int k, int l) {
    vector<pair<vector<int>, int>> sorted = v;

    sort(sorted.begin(), sorted.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
    });

    k = min(k, static_cast<int>(sorted.size()));

    vector<pair<vector<int>, int>> result;
    result.reserve(min(static_cast<int>(sorted.size()), k + l));

    result.insert(result.end(), sorted.begin(), sorted.begin() + k);

    int remaining = sorted.size() - k;
    l = min(l, remaining);

    vector<int> indices(remaining);
    iota(indices.begin(), indices.end(), 0);

    random_device rd;
    mt19937 gen(rd());

    shuffle(indices.begin(), indices.end(), gen);

    for (int i = 0; i < l; ++i) {
        result.push_back(sorted[k + indices[i]]);
    }

    return result;
}

vector<int> CountryData::ox(const vector<int>& p1, const vector<int>& p2, int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, n - 1);

    int a = dist(gen);
    int b = dist(gen);
    if (a > b) swap(a, b);

    vector<int> child(n, -1);
    vector<bool> used(n, false);

    for (int i = a; i <= b; i++) {
        child[i] = p1[i];
        used[p1[i]] = true;
    }

    int idx = (b + 1) % n;
    for (int i = 0; i < n; i++) {
        int gene = p2[(b + 1 + i) % n];
        if (!used[gene]) {
            child[idx] = gene;
            used[gene] = true;
            idx = (idx + 1) % n;
        }
    }

    return child;
}

vector<int> CountryData::pmx(const vector<int>& p1, const vector<int>& p2, int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, n - 1);

    int a = dist(gen);
    int b = dist(gen);
    if (a > b) swap(a, b);

    vector<int> child(n, -1);
    vector<int> mapping(n, -1);

    for (int i = a; i <= b; i++) {
        child[i] = p1[i];
        mapping[p2[i]] = p1[i];
    }

    for (int i = 0; i < n; i++) {
        if (i >= a && i <= b) continue;

        int gene = p2[i];

        while (mapping[gene] != -1) {
            gene = mapping[gene];
        }

        child[i] = gene;
    }

    return child;
}