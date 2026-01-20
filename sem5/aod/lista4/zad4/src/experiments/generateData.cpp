#include "../Graph.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>

using namespace std;
using namespace chrono;

int main() {
	const int k_min = 1;
	const int k_max = 16;
	const int runs_per_k = 10;

	error_code ec;
	if (!filesystem::exists("../output")) {
		if (!filesystem::create_directories("../output", ec)) {
			cerr << "Nie mogę utworzyć katalogu 'output': " << ec.message() << "\n";
			return 1;
		}
	}

	ofstream out("../output/raw-data.txt", ios::trunc);
	if (!out.is_open()) {
		cerr << "Nie mogę otworzyć pliku output/raw-data.txt do zapisu\n";
		return 2;
	}

	for (int k = k_min; k <= k_max; k++) {
		cout << "k = " << k << endl;
		for (int run = 1; run <= runs_per_k; run++) {
			cout << "  p = " << run << endl;

			HyperCube hc(k);

			// ================= Edmonds–Karp =================
			auto t0 = high_resolution_clock::now();

			hc.EdmondsKarp(0, (1 << k) - 1);

			auto t1 = high_resolution_clock::now();
			auto elapsed = duration_cast<milliseconds>(t1 - t0).count();

			int flow = hc.flowVal(0);

			out << k << " EK "
			    << fixed << setprecision(6)
			    << elapsed << " " << flow << "\n";

			// reset przepływu
			hc.resetFlow();

			// ================= Dinic =================
			t0 = high_resolution_clock::now();

			hc.Dinic(0, (1 << k) - 1);

			t1 = high_resolution_clock::now();
			elapsed = duration_cast<milliseconds>(t1 - t0).count();

			flow = hc.flowVal(0);

			out << k << " DINIC "
			    << fixed << setprecision(6)
			    << elapsed << " " << flow << "\n";
		}
	}

	out.close();
	cout << "Wyniki zapisano do output/raw-data.txt\n";
	return 0;
}