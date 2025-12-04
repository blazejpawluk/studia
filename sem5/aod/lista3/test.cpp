#include "lib/Graph.hpp"
#include "lib/Parser.hpp"

using namespace filesystem;
using namespace chrono;

/*
pliki zapisywane pod nazwa: <rodzina>.txt
w formacie: <graph-file-name> <min-v-dijkstra> <min-v-dial> <min-v-radixheap> <avg-v-dijkstra> <avg-v-dial> <avg-v-radixheap>

ponadto plik: paths.txt
w formacie: <rodzina> <min-max-dijkstra> <min-max-dial> <min-max-radixheap> <pair1-dijkstra> <pair1-dial> <pair1-radixheap>

pliki zapisywane w folderze output
*/

random_device rd;
mt19937 gen(rd());
ofstream ofp2p("output/paths.txt");

void writeResults(string family) {
try {
		int maxC = 0;
		Graph *maxG;

		ofstream ofss("output/" + family + ".txt");
		for(auto& entry : directory_iterator("inputs/" + family)) {
			string filename = entry.path().filename().string();
			cout << filename << endl;
			Graph G = parseGraphInput("inputs/" + family + "/" + filename);
			cout << "\tcreated graph" << endl;
			if(G.maxCost > maxC) {maxC = G.maxCost; maxG = &G;}
			cout << "\tchecked graph" << endl;
			uniform_int_distribution<> distr(1, G.n);
			ofss << filename.substr(0, filename.size()-3) << " ";
			
			// ss - wierzchołek o najniższym indeksie
			cout << "\tlowest index" << endl;
			auto start = high_resolution_clock::now();
			G.DijkstraFull(1);
			auto end = high_resolution_clock::now();
			duration<double, milli> duration = end - start;
			ofss << duration.count() << " ";
			
			start = high_resolution_clock::now();
			G.DialFull(1);
			end = high_resolution_clock::now();
			duration = end - start;
			ofss << duration.count() << " ";
			
			start = high_resolution_clock::now();
			G.RadixHeapFull(1);
			end = high_resolution_clock::now();
			duration = end - start;
			ofss << duration.count() << " ";
			
			// ss - srednia 5 wierzcholkow
			cout << "\taverages" << endl;
			vector<int> randomV(5);
			for(int i = 0; i < 5; i++) randomV[i] = distr(gen);
			vector<double> total(3, 0.0);
			for(int v : randomV) {
				start = high_resolution_clock::now();
				G.DijkstraFull(v);
				end = high_resolution_clock::now();
				duration = end - start;
				total[0] += duration.count();

				start = high_resolution_clock::now();
				G.DialFull(v);
				end = high_resolution_clock::now();
				duration = end - start;
				total[1] += duration.count();
				
				start = high_resolution_clock::now();
				G.RadixHeapFull(v);
				end = high_resolution_clock::now();
				duration = end - start;
				total[2] += duration.count();
			}
			total[0] /= 5.0; total[1] /= 5.0; total[2] /= 5.0; 
			ofss << total[0] << " " << total[1] << " " << total[2] << endl;
			cout << "\tdone" << endl;
		}

		ofp2p << family <<  " ";
		ofp2p << maxG->DijkstraTwo(1, maxG->n) << " ";
		ofp2p << maxG->DialTwo(1, maxG->n) << " ";
		ofp2p << maxG->RadixHeapTwo(1, maxG->n) << " ";

		uniform_int_distribution<> distr(1, maxG->n);
		for(int i = 0; i < 4; i++) {
			int u = distr(gen), v;
			do {v = distr(gen);} while(u == v);

			ofp2p << maxG->DijkstraTwo(u,v) << " ";
			ofp2p << maxG->DialTwo(u,v) << " ";
			ofp2p << maxG->RadixHeapTwo(u,v) << " ";
		}
		ofp2p << endl;
	} catch(const exception& e) {
		cerr << e.what() << endl;
	}
}

int main() {
	// 3.1 - Random4-n, Random4-C
	writeResults("Random4-n");
	writeResults("Random4-C");
	
	// 3.2 - Long-n, Square-n
	writeResults("Long-n");
	writeResults("Square-n");
	
	// 3.3 - Long-C, Square-C
	writeResults("Long-C");
	writeResults("Square-C");
	
	// 3.4 - USA-road-t
	writeResults("USA-road-t");
}