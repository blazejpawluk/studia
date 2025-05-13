#ifndef PUZZLE
#define PUZZLE

#include <bits/stdc++.h>
using namespace std;

struct Node {
	uint64_t state;
	uint8_t emptyIndex;
	shared_ptr<Node> parent;

	int g; // koszt dojścia do węzła od początku
	int f; // g + wynik heurystyki
};

struct NodeCompare {
	bool operator()(shared_ptr<Node> const& a, shared_ptr<Node> const& b) const {
		return a->f > b->f;
	}
};

class Puzzle {
private:
	size_t width;
	size_t size;
	array<uint8_t, 16> board;
	int visited;

	bool isSolvable();
	uint64_t pack(array<uint8_t, 16> board);
	array<uint8_t, 16> unpack(uint64_t a);
public:
	Puzzle(int width);

	void generateBoard();
	void shuffleBoard(int moves);
	void setBoard(array<uint8_t, 16> board);

	void printBoard();

	int misplacedTiles(uint64_t a);
	int manhattan(uint64_t a);

	void solve();
};

#include "puzzle.cpp"

#endif