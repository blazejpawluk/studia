#ifndef PUZZLE
#define PUZZLE

#include <bits/stdc++.h>
using namespace std;

int WIDTH;
int SIZE;

bool isSolvable(array<uint8_t, 16> board) {
	int inversions = 0;
	for (int i = 0; i < SIZE-1; i++) {
		for (int j = i+1; j < SIZE; j++) {
			if (board[i] > board[j]) inversions++;
		}
	}
	return inversions % 2 != WIDTH % 2;
}

void printBoard(array<uint8_t, 16> board) {
	for (int i = 0; i < WIDTH; i++) cout << "+----";
	cout << "+\n";

	for (int i = 0; i < SIZE; i++) {
		cout << "| " << ((int)board[i] < 10 ? "0" : "") << (int)board[i] << " ";

		if (i % WIDTH == WIDTH-1) {
			cout << "|\n";
			for (int j = 0; j < WIDTH; j++) cout << "+----";
			cout << "+\n";
		}
	}
}

uint64_t pack(array<uint8_t, 16> board) {
	uint64_t a = 0;
	for (int i = 0; i < SIZE; i++) a |= (uint64_t(board[i]) << i*4);
	return a;
}

array<uint8_t, 16> unpack(uint64_t a) {
	array<uint8_t, 16> board;
	for (int i = 0; i < SIZE; i++) board[i] = (a >> i*4) & 0xF;
	return board;
}

// heurystyka 1 - zliczanie zle ulozonych pol
int misplacedTiles(uint64_t a) {
	array<uint8_t, 16> board = unpack(a);
	int counter = 0;
	for (int i = 0; i < SIZE; i++) {
		if (board[i] != 0 && board[i] != i+1) counter++;
	}
	return counter;
}

// heurystyka 2 - Manhattan
int manhattan(uint64_t a) {
	array<uint8_t, 16> board = unpack(a);
	int distance = 0;
	for (int i = 0; i < SIZE; i++) {
		int value = board[i];
		if (value == 0) continue;
		int valRow = (value-1) / WIDTH, valColumn = (value-1) % WIDTH;
		int row = i/WIDTH, column = i%WIDTH;
		distance += abs(row-valRow) + abs(column-valColumn);
	}
	return distance;
}

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

vector<uint8_t> aStar(uint64_t startingState, uint8_t emptyIndex, int (*heur)(uint64_t), size_t& visited) {
	priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, NodeCompare> pq;
	unordered_set<uint64_t> checked;

	Node root {startingState, emptyIndex, nullptr, 0, heur(startingState)};
	shared_ptr<Node> rootPtr = make_shared<Node>(root);
	pq.push(rootPtr);

	visited = 0;

	// wspolczynniki ruchow (gora, dol, lewo, prawo)
	int dv[4] = {-1, 1, 0, 0};
	int dh[4] = {0, 0, -1, 1};

	while (!pq.empty()) {
		shared_ptr<Node> current = pq.top();
		pq.pop();

		if (checked.count(current->state)) continue;

		checked.insert(current->state);
		visited++;

		if (visited % 1000000 == 0) cout << "Odwiedzono juz " << visited << " stanow\n";

		if ((current->f) - (current->g) == 0) {
			vector<uint8_t> path;
			shared_ptr<Node> node = current;
			while (node) {
				path.push_back(node->emptyIndex);
				node = node->parent;
			}
			reverse(path.begin(), path.end());
			return path;
		}

		int row = (current->emptyIndex) / WIDTH;
		int column = (current->emptyIndex) % WIDTH;
		array<uint8_t, 16> board = unpack(current->state);

		for (int i = 0; i < 4; i++) {
			int newRow = row + dv[i], newColumn = column + dh[i];
			
			if (newRow < 0 || newRow >= WIDTH || newColumn < 0 || newColumn >= WIDTH) continue;

			int newEmptyIndex = newRow * WIDTH + newColumn;

			array<uint8_t, 16> newBoard = board;
			swap(newBoard[current->emptyIndex], newBoard[newEmptyIndex]);
			uint64_t newState = pack(newBoard);

			if (checked.count(newState)) continue;

			int newG = (current->g) + 1;
			int newH = heur(newState);

			Node nextNode {newState, (uint8_t)newEmptyIndex, current, newG, newG+newH};
			shared_ptr<Node> nextPtr = make_shared<Node>(nextNode);
			pq.push(nextPtr);
		}
	}

	return {};
}

#endif