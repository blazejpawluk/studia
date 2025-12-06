#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Graph.hpp"

std::vector<std::string> parseCommand(int argc, char* argv[]);
Graph *parseGraph(std::string filename);
std::vector<int> parseSSFile(std::string filename);
std::vector<std::pair<int,int>> parseP2PFle(std::string filename);