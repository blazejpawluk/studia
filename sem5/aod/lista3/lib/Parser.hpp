#pragma once
#include <bits/stdc++.h>
#include "Graph.hpp"
using namespace std;

// {algorithm, graph-file, problem, input-file, output-file}
vector<string> parseCommand(int argc, char* argv[], string algorithm);

Graph parseGraphInput(string filename);
vector<int> parseSSInput(string filename);
vector<pair<int,int>> parseP2PInput(string filename);