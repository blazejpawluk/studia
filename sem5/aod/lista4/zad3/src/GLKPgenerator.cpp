#include "Graph.hpp"
#include <fstream>

void HyperCube::generateCode(const string &filename) {
	ofstream ofs(filename);
	if (!ofs.is_open()) cerr << "Unable to open file: " << filename << ".\n";

	ofs << "using JuMP, GLPK\n";
	ofs << "model = Model(GLPK.Optimizer)\n";
	
	int m = k * (1 << (k-1));

	ofs << "@variable(model, x[1:" << m << "] >= 0, Int)\n";
	ofs << "@objective(model, Max, sum(x[i] for i in 1:" << E[0].size() << "))\n";

	ofs << "A = zeros(" << n << ", " << m << ")\n";

	int idx = 1;
	for (int j = 0; j < n; j++) {
		for (const auto &e : E[j]) if (e.capacity > 0) {
			ofs << "@constraint(model, x[" << idx << "] <= " << e.capacity << ")\n";
			ofs << "A[" << j+1 << ", " << idx << "] = 1\n";
			ofs << "A[" << e.to+1 << ", " << idx << "] = -1\n";
			idx++;
		}
	}

	ofs << "for i in 2:" << n-1 << "\n";
	ofs << "\t@constraint(model, sum(A[i,j] * x[j] for j in 1:" << m << ") == 0)\n";
	ofs << "end\n";

	ofs << "optimize!(model)\n";
	ofs << "println(objective_value(model))";

	cout << "Wygenerowano kod jezyka julia w pliku '" << filename << "'.\n";
}

void BiPartite::generateCode(const string &filename) {
	ofstream ofs(filename);
	if (!ofs.is_open()) cerr << "Unable to open file: " << filename << ".\n";
	
	ofs << "using JuMP, GLPK\n";
	ofs << "model = Model(GLPK.Optimizer)\n";
	
	int m = (1 << k) * (i+2);

	ofs << "@variable(model, x[1:" << m << "] >= 0, Int)\n";
	ofs << "@objective(model, Max, sum(x[i] for i in 1:" << E[0].size() << "))\n";

	ofs << "A = zeros(" << n << ", " << m << ")\n";

	int idx = 1;
	for (int j = 0; j < n; j++) {
		for (const auto &e : E[j]) if (e.capacity > 0) {
			ofs << "@constraint(model, x[" << idx << "] <= " << e.capacity << ")\n";
			ofs << "A[" << j+1 << ", " << idx << "] = 1\n";
			ofs << "A[" << e.to+1 << ", " << idx << "] = -1\n";
			idx++;
		}
	}

	ofs << "for i in 2:" << n-1 << "\n";
	ofs << "\t@constraint(model, sum(A[i,j] * x[j] for j in 1:" << m << ") == 0)\n";
	ofs << "end\n";

	ofs << "optimize!(model)\n";
	ofs << "println(objective_value(model))";

	cout << "Wygenerowano kod jezyka julia w pliku '" << filename << "'.\n";
}