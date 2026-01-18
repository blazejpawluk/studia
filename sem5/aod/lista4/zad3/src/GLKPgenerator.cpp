#include "Graph.hpp"
#include <fstream>

void HyperCube::generateCode(const string &filename, bool pF) {
	ofstream ofs(filename);
	if (!ofs.is_open()) cerr << "Unable to open file: " << filename << ".\n";

	ofs << "using JuMP, GLPK\n\n";

	ofs << "time = @elapsed begin\n";

	ofs << "\t# creating glpk model\n";
	ofs << "\tmodel = Model(GLPK.Optimizer)\n";
	
	int m = k * (1 << (k-1));

	ofs << "\t# variable - flow on graph's edge\n";
	ofs << "\t@variable(model, x[1:" << m << "] >= 0, Int)\n\n";

	ofs << "\t# maximizing sum of flow coming out of starting vertix\n";
	ofs << "\t@objective(model, Max, sum(x[i] for i in 1:" << E[0].size() << "))\n\n";

	ofs << "\t# matrix for controlling flow (incoming flow - outcoming flow = 0 for every vertix apart from start and end)\n";
	ofs << "\tA = zeros(" << n << ", " << m << ")\n\n";

	ofs << "\t# creating constraints:\n";
	ofs << "\t#   constraint for max flow on edge\n";
	ofs << "\t#   filling matrix for controlling flow\n";
	int idx = 1;
	for (int j = 0; j < n; j++) {
		for (const auto &e : E[j]) if (e.capacity > 0) {
			ofs << "\t@constraint(model, x[" << idx << "] <= " << e.capacity << ")\n";
			ofs << "\tA[" << j+1 << ", " << idx << "] = 1\n";
			ofs << "\tA[" << e.to+1 << ", " << idx << "] = -1\n";
			idx++;
		}
	}

	ofs << "\tfor i in 2:" << n-1 << "\n";
	ofs << "\t\t@constraint(model, sum(A[i,j] * x[j] for j in 1:" << m << ") == 0)\n";
	ofs << "\tend\n\n";

	ofs << "\t# optimizing model\n";
	ofs << "\toptimize!(model)\n\n";

	ofs << "end\n\n";

	ofs << "println(\"max flow: \", convert(Int, objective_value(model)))\n";
	ofs << "println(\"    time: \", time)\n";
	
	if (pF) {
		ofs << "println(\"    flow:\")\n";
		int idx = 1;
		for (int j = 0; j < n; j++) {
			for (const auto &e : E[j]) if (e.capacity > 0) {
				ofs << "println(\"          (" << j << "," << e.to << ")=$(convert(Int, value(x[" << idx << "])))/" << e.capacity << "\")\n";
				idx++;
			}
		}
	}

	cout << "Wygenerowano kod jezyka julia w pliku '" << filename << "'.\n";
}

void BiPartite::generateCode(const string &filename, bool pM) {
	ofstream ofs(filename);
	if (!ofs.is_open()) cerr << "Unable to open file: " << filename << ".\n";
	
	ofs << "using JuMP, GLPK\n\n";
	
	ofs << "time = @elapsed begin\n";
	
	ofs << "\t# creating glpk model\n";
	ofs << "\tmodel = Model(GLPK.Optimizer)\n";
	
	int m = (1 << k) * (i+2);

	ofs << "\t# variable - flow on graph's edge\n";
	ofs << "\t@variable(model, x[1:" << m << "] >= 0, Int)\n\n";

	ofs << "\t# maximizing sum of flow coming out of starting vertix\n";
	ofs << "\t@objective(model, Max, sum(x[i] for i in 1:" << E[0].size() << "))\n\n";

	ofs << "\t# matrix for controlling flow (incoming flow - outcoming flow = 0 for every vertix apart from start and end)\n";
	ofs << "\tA = zeros(" << n << ", " << m << ")\n\n";

	ofs << "\t# creating constraints:\n";
	ofs << "\t#   constraint for max flow on edge\n";
	ofs << "\t#   filling matrix for controlling flow\n";
	int idx = 1;
	for (int j = 0; j < n; j++) {
		for (const auto &e : E[j]) if (e.capacity > 0) {
			ofs << "\t@constraint(model, x[" << idx << "] <= 1)\n";
			ofs << "\tA[" << j+1 << ", " << idx << "] = 1\n";
			ofs << "\tA[" << e.to+1 << ", " << idx << "] = -1\n";
			idx++;
		}
	}

	ofs << "\tfor i in 2:" << n-1 << "\n";
	ofs << "\t\t@constraint(model, sum(A[i,j] * x[j] for j in 1:" << m << ") == 0)\n";
	ofs << "\tend\n\n";

	ofs << "\t# optimizing model\n";
	ofs << "\toptimize!(model)\n\n";

	ofs << "end\n\n";

	ofs << "println(\"matching: \", convert(Int, objective_value(model)))\n";
	ofs << "println(\"    time: \", time)\n";
	
	if (pM) {
		ofs << "println(\"matching:\")\n";
		int idx = E[0].size()+1;
		for (int j = 1; j < n; j++) {
			for (const auto &e : E[j]) if (e.capacity > 0 && e.to != n-1) {
				ofs << "if value(x[" << idx << "]) == 1\n";
				ofs << "\tprintln(\"          (" << j << "," << e.to << ")\")\n";
				ofs << "end\n";
				idx++;
			}
		}
	}

	cout << "Wygenerowano kod jezyka julia w pliku '" << filename << "'.\n";
}