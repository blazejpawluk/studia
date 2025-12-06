#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Graph.hpp"

void writeSSOutput(std::string alg, std::vector<std::string> input, Graph *G, double avg);
void writeP2POutput(std::string alg, std::vector<std::string> input, Graph *G, std::vector<std::pair<std::pair<int, int>, long long>> results);